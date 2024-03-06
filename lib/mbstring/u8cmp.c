#include <string.h>

#include "mbstring.h"

int
u8cmp(struct u8view x, struct u8view y)
{
	if (x.len != y.len)
		return x.len > y.len ? +1 : -1;
	return memcmp(x.p, y.p, x.len);
}
