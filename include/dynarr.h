#ifndef MLIB_DYNARR_H
#define MLIB_DYNARR_H

#include <string.h>

#include "alloc.h"

#define DAGROW(da, n) \
	do { \
		if ((n) > (a)->cap) { \
			(a)->cap = (n); \
			(a)->buf = bufalloc((a)->buf, (a)->cap, sizeof(*(a)->buf)); \
		} \
	} while (false)

#define DAPUSH(da, x) \
	do { \
		if ((da)->len >= (da)->cap) { \
			(da)->cap = (da)->cap ? (da)->cap * 2 : 1; \
			(da)->buf = bufalloc((da)->buf, (da)->cap, sizeof(*(da)->buf)); \
		} \
		(da)->buf[(da)->len++] = (x); \
	} while (false)

#define DAEXTEND(da, xs, n) \
	do { \
		if ((da)->len + (n) >= (da)->cap) { \
			do \
				(da)->cap = (da)->cap ? (da)->cap * 2 : 1; \
			while ((da)->len + (n) >= (da)->cap); \
			(da)->buf = bufalloc((da)->buf, (da)->cap, sizeof(*(da)->buf)); \
		} \
		memcpy((da)->buf + (da)->len, (xs), (n)); \
		(a)->len += (n); \
	} while (false)

#define DAREMOVE(da, i) DA_REMOVE_RANGE((a), (i), (i) + 1)

#define DA_REMOVE_RANGE(da, i, j) \
	do { \
		memmove((da)->buf + (i), (da)->buf + (j), \
		        ((da)->len - (j)) * sizeof(*(da)->buf)); \
		(da)->len -= j - i; \
	} while (false)

#define da_foreach(da, p) \
	for (auto p = (da)->buf; (size_t)(p - (da)->buf) < (da)->len; p++)

#endif /* !MLIB_DYNARR_H */
