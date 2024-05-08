#include <stdlib.h>

#include "alloc.h"

void *
heapalloc(void *, void *ptr, size_t, size_t new)
{
	if (new > 0)
		return realloc(ptr, new);
	free(ptr);
	return nullptr;
}
