#include <stdlib.h>

#include "bob.h"

static size_t nextpow2(size_t);

struct u8str *
u8strgrow(struct u8str *b, size_t n)
{
	if (n > b->cap) {
		b->cap = nextpow2(n);
		if (!(b->p = realloc(b->p, b->cap)))
			return nullptr;
	}
	return b;
}

size_t
nextpow2(size_t x)
{
#if defined(__has_builtin) && __has_builtin(__builtin_clzl)
	x = x <= 1 ? 1 : 1 << (64 - __builtin_clzl(x - 1));
#else
	if (x) {
		x--;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		if (sizeof(size_t) >= 4)
			x |= x >> 16;
		if (sizeof(size_t) >= 8)
			x |= x >> 32;
	}
	x++;
#endif

	return x;
}
