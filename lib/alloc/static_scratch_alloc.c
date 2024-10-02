#include <errno.h>
#include <setjmp.h>
#include <stdckdint.h>
#include <stdint.h>

#include "alloc.h"
#include "errors.h"

[[noreturn]] static void oom(jmp_buf *env);

void *
static_scratch_alloc(allocator_t mem, alloc_mode_t mode, void *,
					 ptrdiff_t, ptrdiff_t newnmemb, ptrdiff_t elemsz,
					 ptrdiff_t align) 
{
	st_buf_t *ctx = mem.ctx;
	
	switch (mode) {
	case ALLOC_NEW:
	case ALLOC_RESIZE:
		ptrdiff_t pad, avail, total;
		if (ckd_mul(&total, newnmemb, elemsz))
			oom(mem.err);
		pad = -(uintptr_t)ctx->buf & (align - 1);
		avail = ctx->len - pad;
		if (avail < 0 || total > avail)
			oom(mem.err);
		return (char *)ctx->buf + pad;
	case ALLOC_FREE:
	case ALLOC_FREEALL:
		return nullptr;
	default:
		unreachable();
	}
}

void
oom(jmp_buf *env)
{
	errno = ENOMEM;
	if (env != nullptr)
		longjmp(*env, 1);
	err("static_scratch_alloc:");
}
