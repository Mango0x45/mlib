#include "macros.h"
#include "unicode/prop.h"

#define M(...) ((struct rview)_(__VA_ARGS__))
#define _(...) \
	{(const rune[]){__VA_ARGS__}, lengthof(((const rune[]){__VA_ARGS__}))}

struct rview
uprop_get_lc(rune ch, struct lcctx ctx)
{
	if (ch == U'Σ')
		return ctx.eow ? M(U'ς') : M(U'σ');
	if (ch == U'İ')
		return ctx.az_or_tr ? M('i') : M('i', 0x307);

	if (ctx.lt_acc_after) {
		switch (ch) {
		case 'I':
			return M('i', 0x307);
		case 'J':
			return M('j', 0x307);
		case U'Į':
			return M(U'į', 0x307);
		}
	}

	if (ctx.lt) {
		switch (ch) {
		case U'Ì':
			return M('i', 0x307, 0x300);
		case U'Í':
			return M('i', 0x307, 0x301);
		case U'Ĩ':
			return M('i', 0x307, 0x303);
		}
	}

	if (ch == 0x307 && ctx.az_tr_after_I)
		return M();
	if (ch == 'I' && ctx.az_tr_not_before_dot)
		return M(U'ı');

	ch = uprop_get_slc(ch);
	return M(ch);
}
