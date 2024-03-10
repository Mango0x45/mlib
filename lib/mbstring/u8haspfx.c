#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8haspfx(const char8_t *s, size_t n, const char8_t *pfx, size_t m)
{
	return n >= m && memeq(s, pfx, m);
}
