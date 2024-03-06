#include "mbstring.h"
#include "rune.h"

int
u8tor(rune *ch, const char8_t *s)
{
	if (U8_BYTE_1(s[0])) {
		*ch = s[0];
		return 1;
	} else if (U8_BYTE_2(s[0]) && U8_BYTE_C(s[1])) {
		*ch = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		return 2;
	} else if (U8_BYTE_3(s[0]) && U8_BYTE_C(s[1]) && U8_BYTE_C(s[2])) {
		*ch = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
		return 3;
	} else if (U8_BYTE_4(s[0]) && U8_BYTE_C(s[1]) && U8_BYTE_C(s[2])
				&& U8_BYTE_C(s[3])) {
		*ch = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12)
		    | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
		return 4;
	}

	*ch = RUNE_ERROR;
	return 1;
}
