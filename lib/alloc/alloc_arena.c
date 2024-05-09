#include <stdlib.h>

#include "alloc.h"
#include "errors.h"
#include "macros.h"

void *
alloc_arena(void *raw_ctx, void *ptr, size_t old, size_t new, size_t align)
{
	struct arena_ctx *ctx = raw_ctx;
	ASSUME(ctx != nullptr);
	ASSUME(ctx->a != nullptr);

	void *p = arena_realloc(ctx->a, ptr, old, new, 1, align);
	if (new == 0 || p != nullptr)
		return p;

	if (ctx->jmp != nullptr)
		longjmp(*ctx->jmp, 1);
	err("arena_realloc:");
}
