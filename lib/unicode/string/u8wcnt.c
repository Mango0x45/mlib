#include "unicode/string.h"

size_t
u8wcnt(u8view_t sv)
{
	size_t m = 0;
	while (u8wnext(nullptr, &sv))
		m++;
	return m;
}
