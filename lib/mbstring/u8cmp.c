#include <string.h>

#include "mbstring.h"

int
u8cmp(struct u8view x, struct u8view y)
{
	return x.len != y.len ? (x.len > y.len ? +1 : -1) : memcmp(x.p, y.p, x.len);
}
