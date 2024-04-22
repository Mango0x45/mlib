#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

constexpr rune COMB_GRAVE     = 0x0300;
constexpr rune COMB_ACUTE     = 0x0301;
constexpr rune COMB_TILDE     = 0x0303;
constexpr rune COMB_DOT_ABOVE = 0x0307;

size_t
u8title(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
        enum caseflags flags)
{
	struct tcctx ctx_t = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
	};
	struct lcctx ctx_l = {
		.az_or_tr = ctx_t.az_or_tr,
		.lt = ctx_t.lt,
	};

	int w;
	rune ch;
	bool sow;
	size_t n = 0;
	struct u8view word = {}, cpy = {src, srcn};

	while (w = u8next(&ch, &src, &srcn)) {
		rune next = 0;
		if (srcn > 0)
			u8tor(&next, src);
		if (src > word.p + word.len)
			u8wnext(&word, U8_ARGSP(cpy));

		sow = src - w == word.p;
		ctx_l.eow = src == word.p + word.len;
		ctx_l.before_dot = next == COMB_DOT_ABOVE;
		ctx_l.before_acc = next == COMB_GRAVE
		                || next == COMB_ACUTE
		                || next == COMB_TILDE;

		struct rview rv = sow ? uprop_get_tc(ch, ctx_t)
		                      : uprop_get_lc(ch, ctx_l);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		ctx_t.after_i = ch == 'i';
		ctx_l.after_I = ch == 'I';
	}

	return n;
}
