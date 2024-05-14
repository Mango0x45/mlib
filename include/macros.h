#ifndef MLIB_MACROS_H
#define MLIB_MACROS_H

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define MIN(x, y)          ((x) < (y) ? (x) : (y))
#define MAX(x, y)          ((x) > (y) ? (x) : (y))

#define lengthof(a) (sizeof(a) / sizeof(*(a)))

#define memeq(x, y, n) (!memcmp((x), (y), (n)))
#define streq(x, y)    (!strcmp((x), (y)))
#define u8eq(x, y)     (!u8cmp((x), (y)))

#define ucseq(lhs, rhs) (!_Generic((lhs), struct u8view: u8cmp)((lhs), (rhs)))

#define _MLIB_STR(s)       #s
#define _MLIB_CONCAT(x, y) x##y

#define STR(s)       _MLIB_STR(s)
#define CONCAT(x, y) _MLIB_CONCAT(x, y)

#ifdef NDEBUG
#	include <stddef.h>
#	define ASSUME(p) ((p) ? (void)0 : unreachable())
#else
#	include "errors.h"
#	define ASSUME(p) \
		((p) ? (void)0 \
		     : err("%s:%s:%d: assumption ‘%s’ failed", __FILE__, __func__, \
		           __LINE__, #p))
#endif

#endif /* !MLIB_MACROS_H */
