#include "_attrs.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

constexpr rune COMB_DOT_ABOVE = 0x0307;

[[unsequenced, _mlib_inline]] static inline bool
uprop_ccc_0_or_230(rune ch)
{
	enum uprop_ccc x = uprop_get_ccc(ch);
	return x == 0 || x == 230;
}

size_t
u8lower(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
        enum caseflags flags)
{
	struct lcctx ctx = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
	};

	rune ch;
	size_t n, before_dot_cnt, more_above_cnt;
	struct {
		bool before;
		size_t after;
	} final_sigma = {};

	n = before_dot_cnt = more_above_cnt = 0;

	while (u8next(&ch, &src, &srcn)) {
		rune next = 0;
		if (srcn > 0)
			u8tor(&next, src);

		if (before_dot_cnt == 0 || more_above_cnt == 0) {
			rune ch = 0;
			before_dot_cnt = more_above_cnt = 0;
			struct u8view cpy = {src, srcn};

			do {
				before_dot_cnt++;
				more_above_cnt++;
			} while (u8next(&ch ,U8_ARGSP(cpy)) && !uprop_ccc_0_or_230(ch));

			if (ch != COMB_DOT_ABOVE)
				before_dot_cnt = 0;
			if (uprop_get_ccc(ch) != 230)
				more_above_cnt = 0;
		} else {
			before_dot_cnt--;
			more_above_cnt--;
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

		ctx.before_dot = before_dot_cnt > 0;
		ctx.more_above = more_above_cnt > 0;
		ctx.final_sigma = final_sigma.before && final_sigma.after == 0;

		struct rview rv = uprop_get_lc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		ctx.after_I = (ch == 'I') || (ctx.after_I && !uprop_ccc_0_or_230(ch));
		if (uprop_is_cased(ch))
			final_sigma.before = true;
		else if (!uprop_is_ci(ch))
			final_sigma.before = false;
	}

	return n;
}
