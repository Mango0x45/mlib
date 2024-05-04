#include "unicode/string.h"

size_t
u8wcnt_human(struct u8view sv)
{
	size_t m = 0;
	while (u8wnext_human(nullptr, &sv))
		m++;
	return m;
}
