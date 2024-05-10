#ifndef MLIB_DYNARR_H
#define MLIB_DYNARR_H

#include <string.h>

#include "_alloc_fn.h"
#include "alloc.h"

#define dynarr(T)                                                              \
	struct {                                                                   \
		T *buf;                                                                \
		size_t len, cap;                                                       \
		alloc_fn alloc;                                                        \
		void *ctx;                                                             \
	}

void *daextend(void *, void *, size_t, size_t, size_t);
void *dagrow(void *, size_t, size_t, size_t);

#define dapush(da, x)                                                          \
	((typeof((da)->buf))(daextend)((da), (typeof(x)[1]){(x)}, 1, sizeof(x),    \
	                               alignof(x)))

#define daextend(da, xs, n)                                                    \
	((typeof((da)->buf))daextend((da), (xs), (n), sizeof(*(xs)),               \
	                             alignof(*(xs))))

#define dagrow(da, n)                                                          \
	((typeof((da)->buf))dagrow((da), (n), sizeof(*(da)->buf),                  \
	                           alignof(*(da)->buf)))

#define DAEXTEND(da, xs, n)                                                    \
	do {                                                                       \
		if ((da)->len + (n) >= (da)->cap) {                                    \
			do                                                                 \
				(da)->cap = (da)->cap ? (da)->cap * 2 : 1;                     \
			while ((da)->len + (n) >= (da)->cap);                              \
			(da)->buf = bufalloc((da)->buf, (da)->cap, sizeof(*(da)->buf));    \
		}                                                                      \
		memcpy((da)->buf + (da)->len, (xs), (n));                              \
		(da)->len += (n);                                                      \
	} while (false)

#define DAPOP(da) ((da)->buf[--(da)->len])

#define DAREMOVE(da, i) DA_REMOVE_RANGE((da), (i), (i) + 1)

#define DA_REMOVE_RANGE(da, i, j)                                              \
	do {                                                                       \
		memmove((da)->buf + (i), (da)->buf + (j),                              \
		        ((da)->len - (j)) * sizeof(*(da)->buf));                       \
		(da)->len -= j - i;                                                    \
	} while (false)

#define da_foreach(da, p)                                                      \
	for (auto p = (da).buf; (size_t)(p - (da).buf) < (da).len; p++)

#endif /* !MLIB_DYNARR_H */
