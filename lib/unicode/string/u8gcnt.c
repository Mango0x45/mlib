#include "unicode/string.h"

size_t
u8gcnt(struct u8view sv)
{
	size_t m = 0;
	while (u8gnext(nullptr, &sv))
		m++;
	return m;
}
