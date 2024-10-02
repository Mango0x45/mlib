#include <stdckdint.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "array.h"
#include "alloc.h"

void *
(array_new)(allocator_t mem, ptrdiff_t nmemb, ptrdiff_t elemsz, ptrdiff_t align)
{
	ptrdiff_t total, pad = -sizeof(_mlib_arr_hdr_t) & (align - 1);

	/* Overflow; just call the allocator with the maximum size to force
	   proper error handling */
	if (ckd_mul(&total, nmemb, elemsz)
		|| ckd_add(&total, total, pad)
	    || ckd_add(&total, total, sizeof(_mlib_arr_hdr_t)))
	{
		mem.alloc(mem, ALLOC_NEW, nullptr, 0,
			PTRDIFF_MAX, PTRDIFF_MAX, PTRDIFF_MAX);
		unreachable();
	}

	uint8_t *buf = new(mem, uint8_t, total);
	_mlib_arr_hdr_t hdr = {0, nmemb, mem};
	memcpy(buf, &hdr, sizeof(hdr));
	return buf + sizeof(_mlib_arr_hdr_t) + pad;
}
