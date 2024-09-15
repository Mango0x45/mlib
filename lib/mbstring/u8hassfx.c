#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8hassfx(u8view_t sv, u8view_t sfx)
{
	return sv.len >= sfx.len && memeq(sv.p + sv.len - sfx.len, sfx.p, sfx.len);
}
