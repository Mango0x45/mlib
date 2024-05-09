#include <stdlib.h>

#include "alloc.h"

void *
alloc_heap(void *, void *ptr, size_t, size_t new, size_t)
{
	if (new > 0)
		return realloc(ptr, new);
	free(ptr);
	return nullptr;
}
