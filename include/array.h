#ifndef MLIB_ARRAY_H
#define MLIB_ARRAY_H

#include <stddef.h>
#include <string.h>

#include "_allocator.h"
#include "_attrs.h"

typedef struct {
	ptrdiff_t len, cap;
	allocator_t mem;
} _mlib_arr_hdr_t;

[[_mlib_inline]]
static inline _mlib_arr_hdr_t *
_mlib_array_hdr(void *p, ptrdiff_t align)
{
	ptrdiff_t pad = -sizeof(_mlib_arr_hdr_t) & (align - 1);
	return (_mlib_arr_hdr_t *)((char *)p - pad - sizeof(_mlib_arr_hdr_t));
}

#define array_hdr(p) (_mlib_array_hdr(p, alignof(typeof(*(p)))))
#define array_len(p) (_mlib_array_hdr(p, alignof(typeof(*(p))))->len)
#define array_cap(p) (_mlib_array_hdr(p, alignof(typeof(*(p))))->cap)

#define array_new(mem, T, n)                                                    \
	((T *)array_new((mem), (n), sizeof(T), alignof(T)))
#define array_resz(p, cap)                                                      \
	((typeof(p))array_resz((p), (cap), sizeof(*(p)), alignof(typeof(*(p)))))
#define array_free(p)                                                           \
	array_free((p), sizeof(*(p)), alignof(typeof(*(p))))

#define array_push(p, x)                                                        \
	do {                                                                        \
		_mlib_arr_hdr_t *hdr = _mlib_array_hdr(*(p), alignof(typeof(**(p))));   \
		if (hdr->len == hdr->cap) {                                             \
			*(p) = array_resz(*(p), hdr->len * 2);                              \
			hdr = _mlib_array_hdr(*(p), alignof(typeof(**(p))));                \
		}                                                                       \
		(*(p))[hdr->len++] = (x);                                               \
	} while (false)

/* TODO: Make the resizing not bad */
#define array_extend(p, xs, n)                                                  \
	do {                                                                        \
		_mlib_arr_hdr_t *hdr = _mlib_array_hdr((p), alignof(typeof(*(p))));     \
		if (hdr->len + (n) <= hdr->cap) {                                       \
			(p) = array_resz((p), hdr->len * 2 + (n));                          \
			hdr = _mlib_array_hdr((p), alignof(typeof(*(p))));                  \
		}                                                                       \
		memcpy(&(p)[hdr->len], (xs), (n) * sizeof(*xs));                        \
		hdr->len += (n);                                                        \
	} while (false)

#define array_foreach(p, i) for (typeof(p) i = (p); i < (p) + array_len(p); i++)
	
void *(array_new)(allocator_t mem, ptrdiff_t nmemb, ptrdiff_t elemsz,
	ptrdiff_t align);
void *(array_resz)(void *ptr, ptrdiff_t ncap, ptrdiff_t elemsz, ptrdiff_t align);
void (array_free)(void *ptr, ptrdiff_t elemsz, ptrdiff_t align);

#endif /* !MLIB_ARRAY_H */
