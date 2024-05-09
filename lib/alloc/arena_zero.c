#include "alloc.h"
#include "macros.h"

void
arena_zero(arena *a)
{
	ASSUME(a != nullptr);

	struct _region *cur = a->_head;
	while (cur != nullptr) {
		cur->len = 0;
		cur->last = cur->data;
		cur = cur->next;
	}
}
