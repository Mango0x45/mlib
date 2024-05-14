#ifndef MLIB_DYNARR_H
#define MLIB_DYNARR_H

#include <stdbit.h>
#include <string.h>

#include "_alloc_fn.h"
#include "alloc.h"

/* This is required because alignof() only portably works with types and not
   expressions… */
/* clang-format off */
#ifdef __GNUC__
#	define _mlib_da_alignof(expr) __extension__ alignof(expr)
#else
#	include <stddef.h>
#	define _mlib_da_alignof(expr) \
		((size_t) &((struct {char x; typeof(expr) y;} *)0)->y)
#endif
/* clang-format on */

#define dynarr(T)                                                              \
	struct {                                                                   \
		T *buf;                                                                \
		size_t len, cap;                                                       \
		alloc_fn alloc;                                                        \
		void *ctx;                                                             \
	}

#define DAPUSH(da, x)                                                          \
	do {                                                                       \
		if (++(da)->len > (da)->cap) {                                         \
			size_t ncap = stdc_bit_ceil((da)->len);                            \
			(da)->buf =                                                        \
				(da)->alloc((da)->ctx, (da)->buf, (da)->cap, ncap,             \
			                sizeof(*(da)->buf), _mlib_da_alignof(*(da)->buf)); \
			(da)->cap = ncap;                                                  \
		}                                                                      \
		(da)->buf[(da)->len - 1] = (x);                                        \
	} while (false)

#define DAEXTEND(da, xs, n)                                                    \
	do {                                                                       \
		if (((da)->len += (n)) > (da)->cap) {                                  \
			size_t ncap = stdc_bit_ceil((da)->len);                            \
			(da)->buf =                                                        \
				(da)->alloc((da)->ctx, (da)->buf, (da)->cap, ncap,             \
			                sizeof(*(da)->buf), _mlib_da_alignof(*(da)->buf)); \
			(da)->cap = ncap;                                                  \
		}                                                                      \
		memcpy((da)->buf + (da)->len - (n), (xs), (n) * sizeof(*(da)->buf));   \
	} while (false)

#define DAGROW(da, n)                                                          \
	do {                                                                       \
		if ((n) > (da)->cap) {                                                 \
			(da)->buf =                                                        \
				(da)->alloc((da)->ctx, (da)->buf, (da)->cap, (n),              \
			                sizeof(*(da)->buf), _mlib_da_alignof(*(da)->buf)); \
			(da)->cap = (n);                                                   \
		}                                                                      \
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
