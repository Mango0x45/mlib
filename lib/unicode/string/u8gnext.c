#include <stddef.h>

#include "mbstring.h"
#include "unicode/_gbrk.h"
#include "unicode/string.h"

struct gbrk_state {
	enum {
		GB9C_NONE,
		GB9C_CNSNT,
		GB9C_LNK,
	} gb9c;
	bool gb11 : 1;
	bool gb12 : 1;
};

static bool u8isgbrk(rune, rune, struct gbrk_state *);

size_t
u8gnext(u8view_t *g, u8view_t *sv)
{
	int m;
	rune ch1;
	const char8_t *p;
	struct gbrk_state gs = {0};

	if (sv->len == 0)
		return 0;

	p = sv->p;
	if (g)
		g->p = p;
	p += u8tor(&ch1, p);

	for (;;) {
		rune ch2;

		if ((size_t)(p - sv->p) >= sv->len)
			ch2 = 0;
		else
			m = u8tor(&ch2, p);
		if (u8isgbrk(ch1, ch2, &gs)) {
			ptrdiff_t d = p - sv->p;
			VSHFT(sv, d);
			if (g)
				g->len = d;
			return d;
		}

		ch1 = ch2;
		p += m;
	}
}

bool
u8isgbrk(rune a, rune b, struct gbrk_state *gs)
{
	enum uprop_gbrk ap, bp;
	enum uprop_gbrk_indc aip, bip;

	/* GB1 & GB2 */
	if (!a || !b)
		goto do_break;

	/* GB3 & ASCII fast-track */
	if ((a | b) < 0x300) {
		if (a == '\r' && b == '\n')
			return false;
		goto do_break;
	}

	/* GB4 */
	uprop_get_gbrk(&ap, &aip, a);
	if (a == '\r' || a == '\n' || ap == GBRK_CN)
		goto do_break;

	/* GB5 */
	uprop_get_gbrk(&bp, &bip, b);
	if (b == '\r' || b == '\n' || bp == GBRK_CN)
		goto do_break;

	/* Setting flags for GB9c */
	if (aip == GBRK_INDC_CNSNT)
		gs->gb9c = GB9C_CNSNT;
	else if (aip == GBRK_INDC_LNK && gs->gb9c == GB9C_CNSNT)
		gs->gb9c = GB9C_LNK;

	/* GB6 */
	if (ap == GBRK_HST_L
	    && (bp == GBRK_HST_L || bp == GBRK_HST_V || bp == GBRK_HST_LV
	        || bp == GBRK_HST_LVT))
	{
		return false;
	}

	/* GB7 */
	if ((ap == GBRK_HST_V || ap == GBRK_HST_LV)
	    && (bp == GBRK_HST_V || bp == GBRK_HST_T))
	{
		return false;
	}

	/* GB8 */
	if ((ap == GBRK_HST_LVT || ap == GBRK_HST_T) && bp == GBRK_HST_T)
		return false;

	/* GB9 */
	if (bp == GBRK_EX || bp == GBRK_ZWJ) {
		if (ap == GBRK_EXT_PICT)
			gs->gb11 = true;
		return false;
	}

	/* GB9a */
	if (bp == GBRK_SM)
		return false;

	/* GB9b */
	if (ap == GBRK_PP)
		return false;

	/* GB9c */
	if ((aip == GBRK_INDC_EXT || aip == GBRK_INDC_LNK) && bip == GBRK_INDC_CNSNT
	    && gs->gb9c == GB9C_LNK)
	{
		return false;
	}

	/* GB11 */
	if (gs->gb11
	    && ((ap == GBRK_EX && (bp == GBRK_EX || bp == GBRK_ZWJ))
	        || (ap == GBRK_ZWJ && bp == GBRK_EXT_PICT)))
	{
		return false;
	}

	/* GB12 & GB13 */
	if (ap == GBRK_RI) {
		if (gs->gb12 || bp != GBRK_RI)
			goto do_break;
		gs->gb12 = true;
		return false;
	}

	/* GB999 */
do_break:
	gs->gb9c = GB9C_NONE;
	gs->gb11 = gs->gb12 = false;
	return true;
}
