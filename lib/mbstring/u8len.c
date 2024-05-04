#include "mbstring.h"

size_t
u8len(struct u8view sv)
{
	size_t m = 0;
	while (u8next(nullptr, &sv))
		m++;
	return m;
}
