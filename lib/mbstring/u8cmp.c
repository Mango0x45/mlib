#include <string.h>

#include "mbstring.h"

/* Technically you can’t pass nullptr to memcmp(), so we check for x.len and
   y.len both being 0 */

int
u8cmp(u8view_t x, u8view_t y)
{
	if (x.len != y.len)
		return x.len > y.len ? +1 : -1;
	return x.len == 0 && y.len == 0 ? 0 : memcmp(x.p, y.p, x.len);
}
