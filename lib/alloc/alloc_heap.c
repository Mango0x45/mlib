#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

#include "alloc.h"
#include "errors.h"

void *
alloc_heap(void *raw_ctx, void *ptr, size_t, size_t new, size_t)
{
	if (new == 0) {
		free(ptr);
		return nullptr;
	}

	void *p = realloc(ptr, new);
	if (p != nullptr)
		return p;

	struct heap_ctx *ctx = raw_ctx;
	if (ctx == nullptr || ctx->jmp == nullptr)
		err("realloc:");

	longjmp(*ctx->jmp, 1);
	unreachable();
}
