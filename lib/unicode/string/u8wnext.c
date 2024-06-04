/* The approach of this implementation is heavily inspired by libgrapheme
   (written by Laslo Hunhold <dev@frign.de>), and my email-correspondance with
   Laslo. */

#include "macros.h"
#include "mbstring.h"
#include "unicode/_wbrk.h"
#include "unicode/string.h"

#define IS_MIDNUMLETQ(xp) ((xp) == WBRK_MB || (xp) == WBRK_SQ)
#define IS_AHLETTER(xp)                                                        \
	((xp) == WBRK_LE || (xp) == WBRK_EXTPICT_LE || (xp) == WBRK_HL)
#define IS_IGNORE(xp)                                                          \
	((xp) == WBRK_EXTEND || (xp) == WBRK_FO || (xp) == WBRK_ZWJ)

struct wbrk_state {
	struct {
		enum uprop_wbrk prev[2], next[2];
	} raw, skip;
	struct u8view raw_v, skip_v, mid_v;
	int ri_parity : 1;
};

static bool advance(struct wbrk_state *);
static size_t findwbrk(struct u8view);
static struct wbrk_state mkwbrkstate(struct u8view);

size_t
u8wnext(struct u8view *w, struct u8view *sv)
{
	ASSUME(sv != nullptr);
	ASSUME(sv->p != nullptr);

	if (sv->len == 0)
		return 0;

	size_t off = findwbrk(*sv);
	if (w != nullptr)
		*w = (struct u8view){sv->p, off};

	ASSUME(sv->len >= off);
	VSHFT(sv, off);
	return off;
}

size_t
findwbrk(struct u8view sv)
{
	ASSUME(sv.p != nullptr);

	struct wbrk_state ws = mkwbrkstate(sv);

	while (advance(&ws)) {
#define prev ws.raw.prev
#define next ws.raw.next
		/* WB3 */
		if (prev[0] == WBRK_CR && next[0] == WBRK_LF)
			continue;

		/* WB3a */
		if (prev[0] == WBRK_NL || prev[0] == WBRK_CR || prev[0] == WBRK_LF)
			break;

		/* WB3b */
		if (next[0] == WBRK_NL || next[0] == WBRK_CR || next[0] == WBRK_LF)
			break;

		/* WB3c */
		if (prev[0] == WBRK_ZWJ
		    && (next[0] == WBRK_EXTPICT || next[0] == WBRK_EXTPICT_LE))
		{
			continue;
		}

		/* WB3d */
		if (prev[0] == WBRK_WSEGSPACE && next[0] == WBRK_WSEGSPACE)
			continue;

		/* WB4 */
		if (next[0] == WBRK_EXTEND || next[0] == WBRK_FO || next[0] == WBRK_ZWJ)
			continue;

#undef prev
#undef next
#define prev ws.skip.prev
#define next ws.skip.next

		/* WB5 */
		if (IS_AHLETTER(prev[0]) && IS_AHLETTER(next[0]))
			continue;

		/* WB6 */
		if (IS_AHLETTER(prev[0])
		    && (next[0] == WBRK_ML || IS_MIDNUMLETQ(next[0]))
		    && IS_AHLETTER(next[1]))
		{
			continue;
		}

		/* WB7 */
		if (IS_AHLETTER(prev[1])
		    && (prev[0] == WBRK_ML || IS_MIDNUMLETQ(prev[0]))
		    && IS_AHLETTER(next[0]))
		{
			continue;
		}

		/* WB7a */
		if (prev[0] == WBRK_HL && next[0] == WBRK_SQ)
			continue;

		/* WB7b */
		if (prev[0] == WBRK_HL && next[0] == WBRK_DQ && next[1] == WBRK_HL)
			continue;

		/* WB7c */
		if (prev[1] == WBRK_HL && prev[0] == WBRK_DQ && next[0] == WBRK_HL)
			continue;

		/* WB8 */
		if (prev[0] == WBRK_NU && next[0] == WBRK_NU)
			continue;

		/* WB9 */
		if (IS_AHLETTER(prev[0]) && next[0] == WBRK_NU)
			continue;

		/* WB10 */
		if (prev[0] == WBRK_NU && IS_AHLETTER(next[0]))
			continue;

		/* WB11 */
		if (prev[1] == WBRK_NU && (prev[0] == WBRK_MN || IS_MIDNUMLETQ(prev[0]))
		    && next[0] == WBRK_NU)
		{
			continue;
		}

		/* WB12 */
		if (prev[0] == WBRK_NU && (next[0] == WBRK_MN || IS_MIDNUMLETQ(next[0]))
		    && next[1] == WBRK_NU)
		{
			continue;
		}

		/* WB13 */
		if (prev[0] == WBRK_KA && next[0] == WBRK_KA)
			continue;

		/* WB13a */
		if ((IS_AHLETTER(prev[0]) || prev[0] == WBRK_NU || prev[0] == WBRK_KA
		     || prev[0] == WBRK_EX)
		    && next[0] == WBRK_EX)
		{
			continue;
		}

		/* WB13b */
		if (prev[0] == WBRK_EX
		    && (IS_AHLETTER(next[0]) || next[0] == WBRK_NU
		        || next[0] == WBRK_KA))
		{
			continue;
		}

		/* WB15 & WB16 */
		if (next[0] == WBRK_RI && ws.ri_parity)
			continue;

		/* WB999 */
		break;
#undef prev
#undef next
	}

	return ws.mid_v.p - sv.p;
}

struct wbrk_state
mkwbrkstate(struct u8view sv)
{
	struct wbrk_state ws = {
		.raw = {{WBRK_EOT, WBRK_EOT}, {WBRK_EOT, WBRK_EOT}},
		.skip = {{WBRK_EOT, WBRK_EOT}, {WBRK_EOT, WBRK_EOT}},
		.mid_v = sv,
		.raw_v = sv,
		.skip_v = sv,
	};

	static_assert(sizeof(ws.skip.next) == sizeof(ws.raw.next));

	rune ch;
	for (size_t i = 0; i < lengthof(ws.raw.next) && u8next(&ch, &ws.raw_v) != 0;
	     i++)
	{
		ws.raw.next[i] = uprop_get_wbrk(ch);
	}

	for (size_t i = 0;
	     i < lengthof(ws.raw.next) && u8next(&ch, &ws.skip_v) != 0;)
	{
		ws.skip.next[i] = uprop_get_wbrk(ch);
		if (!IS_IGNORE(ws.skip.next[i]))
			i++;
	}

	return ws;
}

bool
advance(struct wbrk_state *ws)
{
	if (ws->raw.next[0] == WBRK_EOT)
		return false;

	/* Shift the prop window over by 1 */
	rune ch;
	ws->raw.prev[1] = ws->raw.prev[0];
	ws->raw.prev[0] = ws->raw.next[0];
	ws->raw.next[0] = ws->raw.next[1];
	ws->raw.next[1] = u8next(&ch, &ws->raw_v) != 0 ? uprop_get_wbrk(ch)
	                                               : WBRK_EOT;

	/* Increment the midpoint */
	u8next(nullptr, &ws->mid_v);

	/* Ignore ignorable properties */
	if (!IS_IGNORE(ws->raw.prev[0])) {
		ws->skip.prev[1] = ws->skip.prev[0];
		ws->skip.prev[0] = ws->skip.next[0];
		ws->skip.next[0] = ws->skip.next[1];
		ws->ri_parity = ws->ri_parity == 0 && ws->skip.prev[0] == WBRK_RI;

		do {
			if (u8next(&ch, &ws->skip_v) == 0) {
				ws->skip.next[1] = WBRK_EOT;
				break;
			}
			ws->skip.next[1] = uprop_get_wbrk(ch);
		} while (IS_IGNORE(ws->skip.next[1]));
	}

	return true;
}
