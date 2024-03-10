#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8hassfx(const char8_t *s, size_t n, const char8_t *sfx, size_t m)
{
	return n >= m && memeq(s + n - m, sfx, m);
}
