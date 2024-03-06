#include <errno.h>
#if __has_include(<stdckdint.h>)
#	include <stdckdint.h>
#	warning "stdckdint.h now available; remove manual ckd_*() implementations"
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
#include "errors.h"

void *
bufalloc(void *p, size_t n, size_t m)
{
	if (ckd_mul(&n, n, m)) {
		errno = EOVERFLOW;
		err(__func__);
	}

	if (!(p = realloc(p, n)))
		err(__func__);
	return p;
}
