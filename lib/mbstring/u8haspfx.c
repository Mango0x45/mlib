#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8haspfx(u8view_t sv, u8view_t pfx)
{
	return sv.len >= pfx.len && memeq(sv.p, pfx.p, pfx.len);
}
