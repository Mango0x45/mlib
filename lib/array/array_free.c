#include <stdint.h>

#include "array.h"
#include "alloc.h"

void
(array_free)(void *vptr, ptrdiff_t elemsz, ptrdiff_t align)
{
	ptrdiff_t pad = -sizeof(_mlib_arr_hdr_t) & (align - 1);
	_mlib_arr_hdr_t *hdr = _mlib_array_hdr(vptr, align);
	delete(hdr->mem, (uint8_t *)hdr, sizeof(*hdr) + pad + hdr->cap*elemsz);
}
