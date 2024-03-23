#include "unicode/gbrk.h"

size_t
u8glen(const char8_t *s, size_t n)
{
	size_t m = 0;
	while (u8gnext(nullptr, &s, &n))
		m++;
	return m;
}
