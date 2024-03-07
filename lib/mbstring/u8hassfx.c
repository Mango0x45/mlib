#include <string.h>

#include "mbstring.h"

bool
u8hassfx(const char8_t *s, size_t n, const char8_t *sfx, size_t m)
{
	return n >= m && memcmp(s + n - m, sfx, m);
}
