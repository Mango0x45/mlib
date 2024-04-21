#include "unicode/string.h"

size_t
u8wcnt(const char8_t *s, size_t n)
{
	size_t m = 0;
	while (u8wnext(nullptr, &s, &n))
		m++;
	return m;
}
