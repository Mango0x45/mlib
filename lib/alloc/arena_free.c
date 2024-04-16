#include <sys/mman.h>

#include <stdlib.h>

#include "alloc.h"
#include "macros.h"

void
arena_free(arena *a)
{
	ASSUME(a != nullptr);

	struct _region *cur, *next;
	for (cur = a->_head; cur != nullptr; cur = next) {
		next = cur->next;
		munmap(cur->data, cur->cap);
		free(cur);
	}
	a->_head = nullptr;
}
