#include <errno.h>
#if __has_include(<stdckdint.h>)
#	include <stdckdint.h>
#	ifdef __APPLE__
#		warning "stdckdint.h now available on Mac; remove manual ckd_*() code"
#	endif
#elifdef __GNUC__
#	define ckd_add(r, a, b) ((bool)__builtin_add_overflow(a, b, r))
#	define ckd_mul(r, a, b) ((bool)__builtin_mul_overflow(a, b, r))
#else
#	define ckd_add(r, a, b) (*(r) = (a) + (b))
#	define ckd_mul(r, a, b) (*(r) = (a) * (b))
#	warning "ckd_*() not supported on the current platform"
#endif
#include <stdlib.h>

#include "alloc.h"

void *
bufalloc_noterm(void *p, size_t n, size_t m)
{
	if (ckd_mul(&n, n, m)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	return realloc(p, n);
}
