#include "_attrs.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

constexpr rune COMB_DOT_ABOVE = 0x0307;

[[unsequenced, _mlib_inline]]
static inline bool
uprop_ccc_0_or_230(rune ch)
{
	enum uprop_ccc x = uprop_get_ccc(ch);
	return x == 0 || x == 230;
}

size_t
u8title(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
        enum caseflags flags)
{
	struct tcctx ctx_t;
	struct lcctx ctx_l;

	ctx_t.az_or_tr = ctx_l.az_or_tr = flags & CF_LANG_AZ;
	ctx_t.lt = ctx_l.lt = flags & CF_LANG_LT;

	rune ch;
	bool nl_IJ = false;
	size_t n, before_dot_cnt, more_above_cnt;
	struct u8view word = {}, wcpy = {src, srcn};
	struct {
		bool before;
		size_t after;
	} final_sigma = {};
	enum {
		TITLE,
		BETWEEN,
		LOWER,
	} state = 0;

	n = before_dot_cnt = more_above_cnt = 0;

	while (u8next(&ch, &src, &srcn)) {
		if (src > word.p + word.len) {
			u8wnext(&word, U8_ARGSP(wcpy));
			ctx_t.after_soft_dotted = false;
			state = TITLE;
		}

		if (ctx_l.az_or_tr || ctx_l.lt) {
			if (before_dot_cnt == 0 || more_above_cnt == 0) {
				rune ch = 0;
				before_dot_cnt = more_above_cnt = 0;
				struct u8view cpy = {src, srcn};

				do {
					before_dot_cnt++;
					more_above_cnt++;
				} while (u8next(&ch, U8_ARGSP(cpy)) && !uprop_ccc_0_or_230(ch));

				if (ch != COMB_DOT_ABOVE)
					before_dot_cnt = 0;
				if (uprop_get_ccc(ch) != 230)
					more_above_cnt = 0;
			} else {
				before_dot_cnt--;
				more_above_cnt--;
			}
		}

		if (final_sigma.after == 0) {
			rune ch;
			struct u8view cpy = {src, srcn};

			do
				final_sigma.after++;
			while (u8next(&ch, U8_ARGSP(cpy)) && uprop_is_ci(ch));

			if (!uprop_is_cased(ch))
				final_sigma.after = 0;
		} else
			final_sigma.after--;

		ctx_l.before_dot = before_dot_cnt > 0;
		ctx_l.more_above = more_above_cnt > 0;
		ctx_l.final_sigma = final_sigma.before && final_sigma.after == 0;

		if (state == BETWEEN && uprop_is_cased(ch))
			state = LOWER;
		struct rview rv = state == LOWER && !nl_IJ ? uprop_get_lc(ch, ctx_l)
		                                           : uprop_get_tc(ch, ctx_t);
		if (nl_IJ)
			nl_IJ = false;
		if (state == TITLE && uprop_is_cased(ch)) {
			state = BETWEEN;

			if (flags & CF_LANG_NL) {
				rune next = 0;
				if (srcn > 0)
					u8tor(&next, src);
				nl_IJ =
					(ch == 'i' || ch == 'I') && (next == 'j' || next == 'J');
			}
		}

		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		ctx_l.after_I =
			(ch == 'I') || (ctx_l.after_I && !uprop_ccc_0_or_230(ch));
		if (uprop_is_cased(ch))
			final_sigma.before = true;
		else if (!uprop_is_ci(ch))
			final_sigma.before = false;

		if (uprop_is_sd(ch))
			ctx_t.after_soft_dotted = true;
		else if (uprop_ccc_0_or_230(ch))
			ctx_t.after_soft_dotted = false;
	}

	return n;
}