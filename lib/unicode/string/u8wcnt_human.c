#include "unicode/string.h"

size_t
u8wcnt_human(u8view_t sv)
{
	size_t m = 0;
	while (u8wnext_human(nullptr, &sv))
		m++;
	return m;
}
