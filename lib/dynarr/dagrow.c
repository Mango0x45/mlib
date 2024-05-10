#include <stdint.h>

#include "dynarr.h"

void *
(dagrow)(void *da, size_t n, size_t elemsz, size_t align)
{
	dynarr(uint8_t) cpy;
	memcpy(&cpy, da, sizeof(cpy));

	if (n > cpy.cap) {
		cpy.buf = cpy.alloc(cpy.ctx, cpy.buf, cpy.cap, n, elemsz, align);
		cpy.cap = n;
	}

	return memcpy(da, &cpy, sizeof(cpy));
}
