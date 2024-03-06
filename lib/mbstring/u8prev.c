#include <stddef.h>

#include "mbstring.h"
#include "rune.h"

int
u8prev(rune *ch, const char8_t **p, const char8_t *start)
{
	int off;
	const char8_t *s = *p;
	ptrdiff_t d = s - start;

	if (d <= 0) {
		return 0;
	} else if (U8_BYTE_1(s[-1])) {
		if (ch)
			*ch = s[-1];
		off = 1;
	} else if (d > 1 && U8_BYTE_C(s[-1]) && U8_BYTE_2(s[-2])) {
		if (ch)
			*ch = ((s[-2] & 0x1F) << 6) | (s[-1] & 0x3F);
		off = 2;
	} else if (d > 2 && U8_BYTE_C(s[-1]) && U8_BYTE_C(s[-2])
			&& U8_BYTE_3(s[-3])) {
		if (ch) {
			*ch =
				((s[-3] & 0x0F) << 12) | ((s[-2] & 0x3F) << 6) | (s[-1] & 0x3F);
		}
		off = 3;
	} else if (d > 3 && U8_BYTE_C(s[-1]) && U8_BYTE_C(s[-2]) && U8_BYTE_C(s[-3])
			&& U8_BYTE_4(s[-4])) {
		if (ch) {
			*ch = ((s[-4] & 0x07) << 18) | ((s[-3] & 0x3F) << 12)
			    | ((s[-2] & 0x3F) << 6) | (s[-1] & 0x3F);
		}
		off = 4;
	} else {
		if (ch)
			*ch = RUNE_ERROR;
		off = 1;
	}

	*p -= off;
	return off;
}
