#include <errno.h>
#include <stdckdint.h>

#include "_attrs.h"
#include "alloc.h"
#include "macros.h"
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

char8_t *
u8lower(size_t *dstn, u8view_t sv, caseflags_t flags, allocator_t mem)
{
	ASSUME(dstn != nullptr);

	struct lcctx ctx = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
	};

	rune ch;
	size_t n, before_dot_cnt, more_above_cnt;
	struct {
		bool before;
		size_t after;
	} final_sigma = {
		.before = true,
	};

	n = before_dot_cnt = more_above_cnt = 0;

	size_t bufsz;
	/* TODO: Also use U8LOWER_SCALE */
	if (ckd_mul(&bufsz, sv.len, (size_t)U8LOWER_SCALE_LT)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	char8_t *dst = new(mem, typeof(*dst), bufsz);

	while (u8next(&ch, &sv)) {
		rune next = 0;
		if (sv.len > 0)
			u8tor(&next, sv.p);

		if (ctx.az_or_tr || ctx.lt) {
			if (before_dot_cnt == 0 || more_above_cnt == 0) {
				rune ch = 0;
				before_dot_cnt = more_above_cnt = 0;
				u8view_t cpy = sv;

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
			u8view_t cpy = sv;

			do
				final_sigma.after++;
			while (u8next(&ch, &cpy) && uprop_is_ci(ch));

			if (!uprop_is_cased(ch))
				final_sigma.after = 0;
		} else
			final_sigma.after--;

		ctx.before_dot = before_dot_cnt > 0;
		ctx.more_above = more_above_cnt > 0;
		ctx.final_sigma = final_sigma.before && final_sigma.after == 0;

		struct rview rv = uprop_get_lc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++)
			n += rtou8(dst + n, bufsz - n, rv.p[i]);

		ctx.after_I = (ch == 'I') || (ctx.after_I && !uprop_ccc_0_or_230(ch));
		if (uprop_is_cased(ch))
			final_sigma.before = true;
		else if (!uprop_is_ci(ch))
			final_sigma.before = false;
	}

	*dstn = n;
	return resz(mem, dst, bufsz, n);
}
