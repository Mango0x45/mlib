#include <stdlib.h>

#include "bob.h"

struct u8str *
u8strinit(struct u8str *b, size_t n)
{
	if (n) {
		if (!(b->p = malloc(n)))
			return nullptr;
	} else
		b->p = nullptr;
	b->len = 0;
	b->cap = n;
	return b;
}
