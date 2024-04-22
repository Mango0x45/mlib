#ifndef MLIB_MACROS_H
#define MLIB_MACROS_H

#define CLAMP(x, min, max) ((x) < (min) ? (min) : (x) > (max) ? (max) : (x))
#define MIN(x, y)          ((x) < (y) ? (x) : (y))
#define MAX(x, y)          ((x) > (y) ? (x) : (y))

#define lengthof(a) (sizeof(a) / sizeof(*(a)))

#define memeq(...) (!memcmp(__VA_ARGS__))
#define streq(...) (!strcmp(__VA_ARGS__))
#define u8eq(...)  (!u8cmp(__VA_ARGS__))

#define TODO(s) err("%s:%s:%d: todo: %s", __FILE__, __func__, __LINE__, s)

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
