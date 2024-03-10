#include <string.h>

#include "mbstring.h"

int
u8cmp(const char8_t *x, size_t n, const char8_t *y, size_t m)
{
	return n != m ? (n > m ? +1 : -1) : memcmp(x, y, n);
}
