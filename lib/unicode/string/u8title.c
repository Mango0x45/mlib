#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

constexpr rune COMB_GRAVE = 0x0300;
constexpr rune COMB_ACUTE = 0x0301;
constexpr rune COMB_TILDE = 0x0303;
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
	size_t n = 0;
	bool lt_special, nl_special;
	struct u8view word = {}, cpy = {src, srcn};

	lt_special = nl_special = false;

	while (w = u8next(&ch, &src, &srcn)) {
		rune next = 0;
		if (srcn > 0)
			u8tor(&next, src);
		if (src > word.p + word.len)
			u8wnext(&word, U8_ARGSP(cpy));

		bool sow = src - w == word.p;
		ctx_l.eow = src == word.p + word.len;
		ctx_l.before_dot = next == COMB_DOT_ABOVE;
		ctx_l.before_acc =
			next == COMB_GRAVE || next == COMB_ACUTE || next == COMB_TILDE;

		struct rview rv;
		if (nl_special && (ch == 'j' || ch == 'J'))
			rv = (struct rview){.p = U"J", .len = 1};
		else
			rv = sow || lt_special ? uprop_get_tc(ch, ctx_t)
			                       : uprop_get_lc(ch, ctx_l);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		if (flags & CF_LANG_NL)
			nl_special = sow && (ch == 'i' || ch == 'I');
		if (ctx_t.lt) {
			/* If the rune at SOW is Soft_Dotted, then the next rune should be
			   titlecased if it is U+0307 or if does not have ccc=0 and ccc=230.
			   If the current rune was titlecased as a result of the above rule,
			   then the rule should be applied again to the next rune.  If the
			   current rune was titlecased and is U+0307, then lowercase until
			   the next word boundary. */
			enum uprop_ccc ccc;
			if (lt_special || uprop_is_sd(ch)) {
				ctx_t.after_soft_dotted = true;
				lt_special =
					(sow || lt_special) && ch != COMB_DOT_ABOVE
					&& (next == COMB_DOT_ABOVE
				        || ((ccc = uprop_get_ccc(next)) != 0 && ccc != 230));
			} else
				ctx_t.after_soft_dotted = false;
		}

		ctx_l.after_I = ch == 'I';
	}

	return n;
}
