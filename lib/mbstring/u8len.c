#include "mbstring.h"

size_t
u8len(const char8_t *s, size_t n)
{
	size_t m = 0;
	while (u8next(nullptr, &s, &n))
		m++;
	return m;
}
