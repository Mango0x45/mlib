#include <errno.h>
#include <stdckdint.h>
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
