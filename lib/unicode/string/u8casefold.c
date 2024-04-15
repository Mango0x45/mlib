#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8casefold(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
           enum caseflags flags)
{
	rune ch;
	size_t n = 0;

	while (u8next(&ch, &src, &srcn)) {
		struct rview rv = uprop_get_cf(ch, flags & CF_LANG_AZ);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}
	}

	return n;
}
