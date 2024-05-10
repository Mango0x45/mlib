#include <string.h>

#include "mbstring.h"

/* Technically you can’t pass nullptr to memcmp(), so we check for x.len and
   y.len both being 0 */

int
u8cmp(struct u8view x, struct u8view y)
{
	if (x.len != y.len)
		return x.len > y.len ? +1 : -1;
	return x.len == 0 && y.len == 0 ? 0 : memcmp(x.p, y.p, x.len);
}
