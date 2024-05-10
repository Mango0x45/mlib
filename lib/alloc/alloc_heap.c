#include <errno.h>
#include <setjmp.h>
#include <stdckdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "alloc.h"
#include "errors.h"

void *
alloc_heap(void *raw_ctx, void *ptr, size_t, size_t new, size_t elemsz, size_t)
{
	if (new == 0) {
		free(ptr);
		return nullptr;
	}

	if (!ckd_mul(&new, new, elemsz)) {
		void *p = realloc(ptr, new);
		if (p != nullptr)
			return p;
	} else
		errno = EOVERFLOW;

	struct heap_ctx *ctx = raw_ctx;
	if (ctx == nullptr || ctx->jmp == nullptr)
		err("realloc:");

	longjmp(*ctx->jmp, 1);
	unreachable();
}
