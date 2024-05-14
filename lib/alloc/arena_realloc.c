#include <errno.h>
#include <stdckdint.h>
#include <string.h>

#include "alloc.h"
#include "macros.h"

void *
arena_realloc(arena *a, void *ptr, size_t old, size_t new, size_t elemsz,
              size_t align)
{
	ASSUME(a != nullptr);

	if (ptr == nullptr)
		return arena_alloc(a, new, elemsz, align);

	if (old == new)
		return ptr;

	struct _region *cur = a->_head;
	while (cur != nullptr) {
		if (ptr >= cur->data && (char *)ptr < (char *)cur->data + cur->cap)
			break;
		cur = cur->next;
	}
	if (cur == nullptr)
		cur = a->_head;

	/* cur now points to the region containing ‘ptr’ */

	/* If we are shrinking the buffer, then we don’t need to move our allocation
	   and can just return it directly.  As a minor optimization if the
	   allocation we are shrinking is the last allocation in the current region,
	   we can decrease the region length to make space for more future
	   allocations. */
	if (old > new) {
		if (ptr == cur->last)
			cur->len -= (old - new) * elemsz;
		return ptr;
	}

	ASSUME(old < new);

	/* If we need to grow the given allocation, but it was the last allocation
	   made in a region, then we first see if we can just eat more trailing free
	   space in the region to avoid a memcpy(). */
	if (ptr == cur->last) {
		size_t need, free = cur->cap - cur->len;
		if (ckd_mul(&need, new - old, elemsz)) {
			errno = EOVERFLOW;
			return nullptr;
		}
		if (need <= free) {
			cur->len += need;
			return ptr;
		}
	}

	/* At this point we just make a new allocation and copy the data over */
	void *dst = arena_alloc(a, new, elemsz, align);
	return dst == nullptr ? nullptr : memcpy(dst, ptr, old * elemsz);
}
