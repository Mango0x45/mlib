/* TODO: Support malloc() backend for systems without MAP_ANONYMOUS */

#include <sys/mman.h>

#include <errno.h>
#include <setjmp.h>
#include <stdckdint.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "_attrs.h"
#include "alloc.h"
#include "error.h"
#include "macros.h"

#define PAD(len, align) (((len) + (align) - 1) & ~((align) - 1))

struct arena_blk {
	uint8_t *head, *tail, *fngr;
	struct arena_blk *next;
};

static void *alloc(allocator_t mem, ptrdiff_t nmemb, ptrdiff_t elemsz,
				   ptrdiff_t align);
static void freeall(allocator_t mem);
static arena_blk_t *mkblk(ptrdiff_t blksz);
[[noreturn]] static void errjmp(jmp_buf *env);

void *
arena_alloc(allocator_t mem, alloc_mode_t mode, void *ptr, ptrdiff_t oldnmemb,
			ptrdiff_t newnmemb, ptrdiff_t elemsz, ptrdiff_t align)
{
	(void)ptr;
	(void)oldnmemb;
	switch (mode) {
	case ALLOC_NEW:
		return alloc(mem, newnmemb, elemsz, align);
	case ALLOC_RESIZE:
		/* TODO: Make this more efficient */
		void *p = alloc(mem, newnmemb, elemsz, align);
		memcpy(p, ptr, MIN(oldnmemb, newnmemb) * elemsz);
		return p;
	case ALLOC_FREE:
		/* TODO: Allow freeing the very last allocation */
		return nullptr;
	case ALLOC_FREEALL:
		freeall(mem);
		return nullptr;
	default:
		unreachable();
	}
}

void *
alloc(allocator_t mem, ptrdiff_t nmemb, ptrdiff_t elemsz, ptrdiff_t align)
{
	arena_ctx_t *ctx = mem.ctx;
	if (ctx->blksz == 0) {
		long blksz = sysconf(_SC_PAGESIZE);
		ctx->blksz = blksz == -1 ? 4096 : blksz;
	}

	ptrdiff_t bufsz;
	if (ckd_mul(&bufsz, nmemb, elemsz)) {
		errno = EOVERFLOW;
		errjmp(mem.err);
	}

	for (arena_blk_t *blk = ctx->_head; blk != nullptr; blk = blk->next) {
		ptrdiff_t nbufsz, off = PAD((uintptr_t)blk->fngr, align);
		if (ckd_add(&nbufsz, bufsz, off))
			continue;

		if (blk->tail - blk->fngr >= nbufsz) {
			void *p = blk->fngr + off;
			blk->fngr += nbufsz;
			return p;
		}
	}

	/* No page exists that is large enough for our allocation */
	ptrdiff_t padding = PAD(sizeof(arena_blk_t), align);

	if (ckd_add(&bufsz, bufsz, sizeof(arena_blk_t))
	 || ckd_add(&bufsz, bufsz, padding))
	{
		errno = EOVERFLOW;
		errjmp(mem.err);
	}
	
	arena_blk_t *blk = mkblk(MAX(bufsz, ctx->blksz));
	if (blk == nullptr)
		errjmp(mem.err);
	blk->next = ctx->_head;
	blk->fngr = blk->head + bufsz;
	ctx->_head = blk;
	return blk->head + sizeof(arena_blk_t) + padding;
}

void
freeall(allocator_t mem)
{
	arena_ctx_t *ctx = mem.ctx;
	arena_blk_t *blk = ctx->_head;
	while (blk != nullptr) {
		arena_blk_t *next = blk->next;
		(void)munmap(blk, blk->tail - blk->head);
		blk = next;
	}
	ctx->_head = nullptr;
}

static arena_blk_t *
mkblk(ptrdiff_t blksz)
{
	arena_blk_t blk;
	/* blk.next and blk.fngr get set by the caller */
	blk.head = mmap(nullptr, blksz, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANON, -1, 0);
	if (blk.head == MAP_FAILED)
		return nullptr;
	blk.tail = blk.head + blksz;
	return memcpy(blk.head, &blk, sizeof blk);
}	

void
errjmp(jmp_buf *env)
{
	if (env != nullptr)
		longjmp(*env, 1);
	err("arena_alloc:");
}
