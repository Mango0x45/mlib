#ifndef MLIB_MACROS_H
#define MLIB_MACROS_H

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define MIN(x, y)          ((x) < (y) ? (x) : (y))
#define MAX(x, y)          ((x) > (y) ? (x) : (y))

#define lengthof(a) (sizeof(a) / sizeof(*(a)))

#define memeq(x, y, n)   (!memcmp(x, y, n))
#define streq(x, y)      (!strcmp(x, y))
#define u8eq(x, n, y, m) (!u8cmp(x, n, y, m))

#ifdef NDEBUG
#	include <stddef.h>
#	define ASSUME(p) ((p) ? (void)0 : unreachable())
#else
#	include "errors.h"
#	define ASSUME(p) \
		((p) ? (void)0 \
		     : warnx("%s:%s:%d: assumption ‘%s’ failed", __FILE__, __func__, \
		             __LINE__, #p))
#endif

#endif /* !MLIB_MACROS_H */
