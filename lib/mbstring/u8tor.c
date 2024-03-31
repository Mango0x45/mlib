#include "mbstring.h"
#include "rune.h"

int
u8tor(rune *ch, const char8_t *s)
{
	if (u8byte1(s[0])) {
		*ch = s[0];
		return 1;
	} else if (u8byte2(s[0]) && u8bytec(s[1])) {
		*ch = ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		return 2;
	} else if (u8byte3(s[0]) && u8bytec(s[1]) && u8bytec(s[2])) {
		*ch = ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
		return 3;
	} else if (u8byte4(s[0]) && u8bytec(s[1]) && u8bytec(s[2])
			&& u8bytec(s[3])) {
		*ch = ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12)
		    | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
		return 4;
	}

	*ch = RUNE_ERROR;
	return 1;
}
