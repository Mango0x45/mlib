#include <errno.h>
#include <stdbit.h>
#include <stdint.h>
#include <string.h>

#include "dynarr.h"

void *
(dapush)(void *da, void *x, size_t sz, size_t align)
{
	dynarr(uint8_t) cpy;
	memcpy(&cpy, da, sizeof(cpy));

	if (++cpy.len > cpy.cap) {
		size_t ncap = stdc_bit_ceil(cpy.len);
		cpy.buf = cpy.alloc(cpy.ctx, cpy.buf, cpy.cap, ncap, sz, align);
		cpy.cap = ncap;
	}

	memcpy(cpy.buf + cpy.len * sz - sz, x, sz);
	return memcpy(da, &cpy, sizeof(cpy));
}
