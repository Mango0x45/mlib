#include <string.h>

#include "macros.h"
#include "mbstring.h"

bool
u8hassfx(struct u8view sv, struct u8view sfx)
{
	return sv.len >= sfx.len && memeq(sv.p + sv.len - sfx.len, sfx.p, sfx.len);
}
