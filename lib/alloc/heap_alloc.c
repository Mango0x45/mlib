#include <assert.h>
#include <stdckdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"
#include "errors.h"

[[noreturn]] static void oom(jmp_buf *env);

void *
heap_alloc(allocator_t mem, alloc_mode_t mode, void *ptr, ptrdiff_t oldnmemb,
		   ptrdiff_t newnmemb, ptrdiff_t elemsz, ptrdiff_t align) 
{
	void *p;
	ptrdiff_t oldsz, newsz;
	
	switch (mode) {
	case ALLOC_NEW:
		if (ckd_mul(&newsz, newnmemb, elemsz))
			oom(mem.err);
		/* Malloc is guaranteed to return a pointer aligned to an
		   alignment that is suitable for all fundamental types.  For
		   larger alignments we need to use specialized functionality. */
		if ((size_t)align <= alignof(max_align_t)) {
			if ((p = malloc(newsz)) == nullptr)
				oom(mem.err);
		} else {
			if ((p = aligned_alloc(align, newsz)) == nullptr)
				oom(mem.err);
		}
		return p;
	case ALLOC_RESIZE:
		if (ckd_mul(&newsz, newnmemb, elemsz))
			oom(mem.err);
		if (ckd_mul(&oldsz, oldnmemb, elemsz))
			oom(mem.err);
		if ((size_t)align <= alignof(max_align_t)) {
			if ((p = realloc(ptr, newsz)) == nullptr)
				oom(mem.err);
		} else {
			/* We were allocated using aligned_alloc().  Unfortunately
		       there is no way to reallocate a buffer aligned via
		       aligned_alloc() so we need to allocate a new buffer and do
		       a manual copy… */
			if ((p = aligned_alloc(align, newsz)) == nullptr)
				oom(mem.err);
			memcpy(p, ptr, oldsz);
#if 0
			/* We would rather use free_aligned_size(), but it isn’t
			   available yet on most systems. */
			free_aligned_sized(ptr, align, oldsz);
#else
			free(ptr);
#endif
		}
		return p;
	case ALLOC_FREE:
		free(ptr);
		return nullptr;
	case ALLOC_FREEALL:
		assert(!"Not implemented");
		return nullptr;
	default:
		unreachable();
	}
}

void
oom(jmp_buf *env)
{
	if (env != nullptr)
		longjmp(*env, 1);
	err("heap_alloc:");
}
