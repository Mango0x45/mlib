#include "macros.h"
#include "unicode/prop.h"

#define M(...) ((struct rview)_(__VA_ARGS__))
#define _(...) \
	{(const rune[]){__VA_ARGS__}, lengthof(((const rune[]){__VA_ARGS__}))}

struct rview
uprop_get_lc(rune ch, struct lcctx ctx)
{
	constexpr rune COMB_GRAVE     = 0x300;
	constexpr rune COMB_ACUTE     = 0x301;
	constexpr rune COMB_TILDE     = 0x303;
	constexpr rune COMB_DOT_ABOVE = 0x307;

	if (ch == U'Σ')
		return ctx.final_sigma ? M(U'ς') : M(U'σ');
	if (ch == U'İ')
		return ctx.az_or_tr ? M('i') : M('i', COMB_DOT_ABOVE);

	if (ctx.lt) {
		if (ctx.more_above) {
			switch (ch) {
			case 'I':
				return M('i', COMB_DOT_ABOVE);
			case 'J':
				return M('j', COMB_DOT_ABOVE);
			case U'Į':
				return M(U'į', COMB_DOT_ABOVE);
			}
		}

		switch (ch) {
		case U'Ì':
			return M('i', COMB_DOT_ABOVE, COMB_GRAVE);
		case U'Í':
			return M('i', COMB_DOT_ABOVE, COMB_ACUTE);
		case U'Ĩ':
			return M('i', COMB_DOT_ABOVE, COMB_TILDE);
		}
	}

	if (ctx.az_or_tr) {
		if (ch == COMB_DOT_ABOVE && ctx.after_I)
			return M();
		if (ch == 'I' && !ctx.before_dot)
			return M(U'ı');
	}

	ch = uprop_get_slc(ch);
	return M(ch);
}
