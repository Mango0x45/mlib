#include <errno.h>
#include <stdckdint.h>

#include "_attrs.h"
#include "macros.h"
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

char8_t *
u8title(size_t *dstn, struct u8view sv, enum caseflags flags, alloc_fn alloc,
        void *alloc_ctx)
{
	ASSUME(dstn != nullptr);
	ASSUME(alloc != nullptr);

	struct tcctx ctx_t;
	struct lcctx ctx_l;

	ctx_t.az_or_tr = ctx_l.az_or_tr = flags & CF_LANG_AZ;
	ctx_t.lt = ctx_l.lt = flags & CF_LANG_LT;

	rune ch;
	bool nl_IJ = false;
	size_t n, before_dot_cnt, more_above_cnt;
	struct u8view word = {}, wcpy = sv;
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

	size_t bufsz;
	if (ckd_mul(&bufsz, sv.len, (size_t)U8TITLE_SCALE)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	char8_t *dst = alloc(alloc_ctx, nullptr, 0, bufsz, alignof(char8_t));

	while (u8next(&ch, &sv)) {
		if (sv.p > word.p + word.len) {
			u8wnext(&word, &wcpy);
			ctx_t.after_soft_dotted = false;
			state = TITLE;
		}

		if (ctx_l.az_or_tr || ctx_l.lt) {
			if (before_dot_cnt == 0 || more_above_cnt == 0) {
				rune ch = 0;
				before_dot_cnt = more_above_cnt = 0;
				struct u8view cpy = sv;

				do {
					before_dot_cnt++;
					more_above_cnt++;
				} while (u8next(&ch, &cpy) && !uprop_ccc_0_or_230(ch));

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
			rune ch = 0;
			struct u8view cpy = sv;

			do
				final_sigma.after++;
			while (u8next(&ch, &cpy) && uprop_is_ci(ch));

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
				if (sv.len > 0)
					u8tor(&next, sv.p);
				nl_IJ =
					(ch == 'i' || ch == 'I') && (next == 'j' || next == 'J');
			}
		}

		for (size_t i = 0; i < rv.len; i++)
			n += rtou8(dst + n, bufsz - n, rv.p[i]);

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

	*dstn = n;
	return alloc(alloc_ctx, dst, bufsz, n, alignof(char8_t));
}
