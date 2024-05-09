#include <stdlib.h>

#include "alloc.h"

void *
alloc_arena(void *ctx, void *ptr, size_t old, size_t new, size_t align)
{
	return arena_realloc(ctx, ptr, old, new, 1, align);
}
