#include <sys/mman.h>

#include <errno.h>
#include <stdckdint.h>
#include <stdlib.h>

#include "_attrs.h"
#include "alloc.h"
#include "macros.h"

#define IS_POW_2(n) ((n) != 0 && ((n) & ((n) - 1)) == 0)

[[_mlib_pure, _mlib_inline]] static size_t pad(size_t, size_t);
static struct _region *mkregion(size_t);

size_t
pad(size_t len, size_t align)
{
	return (len + align - 1) & ~(align - 1);
}

struct _region *
mkregion(size_t cap)
{
	struct _region *r = malloc(sizeof(struct _region));
	if (r == nullptr)
		return nullptr;
	*r = (struct _region){
		.cap = cap,
		.data = mmap(nullptr, cap, PROT_READ | PROT_WRITE,
	                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0),
	};
	if (r->data == MAP_FAILED) {
		free(r);
		return nullptr;
	}
	return r;
}

void *
arena_alloc(arena *a, size_t sz, size_t n, size_t align)
{
	ASSUME(a != nullptr);
	ASSUME(IS_POW_2(align));

	if (ckd_mul(&sz, sz, n)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	for (struct _region *r = a->_head; r != nullptr; r = r->next) {
		size_t nlen, off = pad(r->len, align);

		/* Technically there are other ways to solve this… but at this point you
		   might as well just fail */
		if (ckd_add(&nlen, off, sz)) {
			errno = EOVERFLOW;
			return nullptr;
		}

		if (nlen <= r->cap) {
			void *ret = (char *)r->data + off;
			r->len = nlen;
			return ret;
		}
	}

	/* No page exists with enough space */
	struct _region *r = mkregion(MAX(sz, a->_init));
	if (r == nullptr)
		return nullptr;
	r->next = a->_head;
	r->len = sz;
	a->_head = r;
	return r->data;
}
