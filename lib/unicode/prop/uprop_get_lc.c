#include "macros.h"
#include "unicode/prop.h"

struct rview
uprop_get_lc(rune ch, struct lcctx ctx)
{
	constexpr rune COMB_GRAVE = 0x300;
	constexpr rune COMB_ACUTE = 0x301;
	constexpr rune COMB_TILDE = 0x303;
	constexpr rune COMB_DOT_ABOVE = 0x307;
	static thread_local rune hack[3];

	if (ch == U'Σ') {
		hack[0] = ctx.final_sigma ? U'ς' : U'σ';
		return (struct rview){hack, 1};
	}
	if (ch == U'İ') {
		hack[0] = 'i';
		hack[1] = COMB_DOT_ABOVE;
		return (struct rview){hack, ctx.az_or_tr ? 1 : 2};
	}

	if (ctx.lt) {
		if (ctx.more_above) {
			switch (ch) {
			case 'I':
				hack[0] = 'i';
				hack[1] = COMB_DOT_ABOVE;
				return (struct rview){hack, 2};
			case 'J':
				hack[0] = 'j';
				hack[1] = COMB_DOT_ABOVE;
				return (struct rview){hack, 2};
			case U'Į':
				hack[0] = U'į';
				hack[1] = COMB_DOT_ABOVE;
				return (struct rview){hack, 2};
			}
		}

		switch (ch) {
		case U'Ì':
		case U'Í':
		case U'Ĩ':
			hack[0] = 'i';
			hack[1] = COMB_DOT_ABOVE;

			/* TODO: Use ternary when GCC stops being bad */
			if (ch == U'Ì')
				hack[2] = COMB_GRAVE;
			else if (ch == U'Í')
				hack[2] = COMB_ACUTE;
			else
				hack[2] = COMB_TILDE;

			return (struct rview){hack, 3};
		}
	}

	if (ctx.az_or_tr) {
		if (ch == COMB_DOT_ABOVE && ctx.after_I)
			return (struct rview){};
		if (ch == 'I' && !ctx.before_dot) {
			hack[0] = U'ı';
			return (struct rview){hack, 1};
		}
	}

	hack[0] = uprop_get_slc(ch);
	return (struct rview){hack, 1};
}
