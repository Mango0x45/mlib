#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

#define IS_AHLETTER(cp)   ((cp) == WB_LE || (cp) == WB_HL)
#define IS_MIDNUMLETQ(cp) ((cp) == WB_MB || (cp) == WB_SQ)

#define RET(x) \
	do { \
		ws->prev_ap = ap; \
		return (x); \
	} while (false)

struct wbrk_state {
	int ri_parity;
	enum uprop_wb prev_ap;
};

static bool u8iswbrk(const char8_t **, size_t *, struct wbrk_state *);

size_t
u8wnext(struct u8view *w, const char8_t **s, size_t *n)
{
	ASSUME(s != nullptr);
	ASSUME(n != nullptr);

	if (*n == 0)
		return 0;

	const char8_t *p = *s;
	if (w != nullptr)
		w->p = p;

	size_t m = *n;
	struct wbrk_state ws = {};
	while (!u8iswbrk(&p, &m, &ws))
		;

	ptrdiff_t d = p - *s;
	*n -= d;
	*s = p;
	if (w)
		w->len = d;
	return d;
}

bool
u8iswbrk(const char8_t **s, size_t *n, struct wbrk_state *ws)
{
	ASSUME(s != nullptr);
	ASSUME(n != nullptr);
	ASSUME(ws != nullptr);

	rune a, b, c;
	enum uprop_wb ap, bp, cp;
	a = b = c = ap = bp = cp = 0;

	u8next(&a, s, n);

	{
		const char8_t *s_cpy = *s;
		size_t n_cpy = *n;
		u8next(&b, &s_cpy, &n_cpy);
		u8next(&c, &s_cpy, &n_cpy);
	}

	ws->ri_parity = ws->ri_parity == 0 && uprop_is_ri(a);

	/* WB1 & WB2 */
	if (!a || !b)
		RET(true);

	/* WB3 */
	if (a == '\r' && b == '\n')
		RET(false);

	/* WB3a */
	if (a == '\r' || a == '\n' || (ap = uprop_get_wb(a)) == WB_NL)
		RET(true);

	/* WB3b */
	if (b == '\r' || b == '\n' || (bp = uprop_get_wb(b)) == WB_NL)
		RET(true);

	/* WB3c */
	if (ap == WB_ZWJ && uprop_is_extpict(b))
		RET(false);

	/* WB3d */
	if (ap == WB_WSEGSPACE && bp == WB_WSEGSPACE)
		RET(false);

	/* WB4 */
	if (bp == WB_FO || bp == WB_EXTEND || bp == WB_ZWJ)
		RET(false);

	/* WB5 */
	if (IS_AHLETTER(ap) && IS_AHLETTER(bp))
		RET(false);

	/* WB6 */
	cp = uprop_get_wb(c);
	if (IS_AHLETTER(ap) && (bp == WB_ML || IS_MIDNUMLETQ(bp))
	    && IS_AHLETTER(cp))
	{
		RET(false);
	}

	/* WB7 */
	if (IS_AHLETTER(ws->prev_ap) && (ap == WB_ML || IS_MIDNUMLETQ(ap))
	    && IS_AHLETTER(bp))
	{
		RET(false);
	}

	/* WB7a & WB7b */
	if (ap == WB_HL && (bp == WB_SQ || (bp == WB_DQ && cp == WB_HL)))
		RET(false);

	/* WB7c */
	if (ws->prev_ap == WB_HL && ap == WB_DQ && bp == WB_HL)
		RET(false);

	/* WB8, WB9, & WB10 */
	if ((ap == WB_NU || IS_AHLETTER(ap)) && (bp == WB_NU || IS_AHLETTER(bp)))
		RET(false);

	/* WB11 */
	if (ws->prev_ap == WB_NU && (ap == WB_MN || IS_MIDNUMLETQ(ap))
	    && bp == WB_NU)
	{
		RET(false);
	}

	/* WB12 */
	if (ap == WB_NU && (bp == WB_MN || IS_MIDNUMLETQ(bp)) && cp == WB_NU)
		RET(false);

	/* WB13 */
	if (ap == WB_KA && bp == WB_KA)
		RET(false);

	/* WB13a */
	if ((IS_AHLETTER(ap) || ap == WB_NU || ap == WB_KA || ap == WB_EX)
	    && bp == WB_EX)
	{
		RET(false);
	}

	/* WB13b */
	if (ap == WB_EX && (IS_AHLETTER(bp) || bp == WB_NU || bp == WB_KA))
		RET(false);

	/* WB15 & WB16 */
	if (ap == WB_RI && bp == WB_RI && ws->ri_parity == 1)
		RET(false);

	/* WB999 */
	RET(true);
}
