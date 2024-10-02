#include <stdckdint.h>
#include <stddef.h>
#include <stdint.h>

#include "array.h"
#include "alloc.h"

void *
(array_resz)(void *ptr, ptrdiff_t ncap, ptrdiff_t elemsz, ptrdiff_t align)
{
	ptrdiff_t newsz, pad = -sizeof(_mlib_arr_hdr_t) & (align - 1);
	_mlib_arr_hdr_t *hdr = _mlib_array_hdr(ptr, align);
	/* Overflow; just call the allocator with the maximum size to force
	   proper error handling */
	if (ckd_mul(&newsz, ncap, elemsz)
	 || ckd_add(&newsz, newsz, pad)
	 || ckd_add(&newsz, newsz, sizeof(_mlib_arr_hdr_t)))
	{
		hdr->mem.alloc(hdr->mem, ALLOC_NEW, nullptr, 0,
			PTRDIFF_MAX, PTRDIFF_MAX, PTRDIFF_MAX);
		unreachable();
	}

	ptrdiff_t oldsz = sizeof(_mlib_arr_hdr_t) + pad + hdr->cap*elemsz;
	hdr = (_mlib_arr_hdr_t *)resz(hdr->mem, (uint8_t *)hdr, oldsz, newsz);
	hdr->cap = ncap;
	return (uint8_t *)hdr + sizeof(*hdr) + pad;
}
