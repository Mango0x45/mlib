#include <stdlib.h>

#include "bob.h"

struct u8str *
u8strfit(struct u8str *b)
{
	return (b->p = realloc(b->p, b->len)) ? b : nullptr;
}
