#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

constexpr rune COMB_GRAVE     = 0x0300;
constexpr rune COMB_ACUTE     = 0x0301;
constexpr rune COMB_TILDE     = 0x0303;
constexpr rune COMB_DOT_ABOVE = 0x0307;

size_t
u8lower(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
        enum caseflags flags)
{
	struct lcctx ctx = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
	};

	rune ch;
	size_t n = 0;

	while (u8next(&ch, &src, &srcn)) {
		/* TODO: Set ‘eow’ once word-segmentation is implemented */

		rune next = 0;
		if (srcn > 0)
			u8tor(&next, src);
		ctx.before_dot = next == COMB_DOT_ABOVE;
		ctx.before_acc = next == COMB_GRAVE
		              || next == COMB_ACUTE
		              || next == COMB_TILDE;

		struct rview rv = uprop_get_lc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		ctx.after_I = ch == 'I';
	}

	return n;
}
