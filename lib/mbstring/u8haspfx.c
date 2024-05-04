#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8haspfx(struct u8view sv, struct u8view pfx)
{
	return sv.len >= pfx.len && memeq(sv.p, pfx.p, pfx.len);
}
