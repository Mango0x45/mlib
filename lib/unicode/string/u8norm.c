#include <string.h>

#include "macros.h"
#include "mbstring.h"
#include "unicode/_cm.h"
#include "unicode/prop.h"
#include "unicode/string.h"

#define BETWEEN(x, y, z) ((x) <= (y) && (y) <= (z))

static void decomp(char8_t *, size_t *, size_t, rune, enum normtype);
static void compbuf(char8_t *, size_t *);

/* Computed using a gen/scale-norm.c */
constexpr int NFD_SCALE = 3;
constexpr int NFKD_SCALE = 11;

/* For Hangul syllable decomposition */
constexpr rune SBASE = 0xAC00;
constexpr rune LBASE = 0x1100;
constexpr rune VBASE = 0x1161;
constexpr rune TBASE = 0x11A7;
constexpr int LCNT = 19;
constexpr int VCNT = 21;
constexpr int TCNT = 28;
constexpr int NCNT = VCNT * TCNT;
constexpr int SCNT = LCNT * NCNT;

char8_t *
u8norm(size_t *dstn, struct u8view src, alloc_fn alloc, void *ctx,
       enum normtype nt)
{
	ASSUME(dstn != nullptr);
	ASSUME(alloc != nullptr);
	ASSUME(BETWEEN(0, nt, 4));

	/* Pre-allocate a buffer with some initial capacity; there is no need to
	   check for overflow when computing bufsz because alloc() will handle the
	   overflow error for us. */
	int scale = (nt & 0b10) ? NFKD_SCALE : NFD_SCALE;
	size_t bufsz = src.len * scale;
	char8_t *dst = alloc(ctx, nullptr, 0, src.len, scale, alignof(char8_t));

	*dstn = 0;
	for (rune ch; ucsnext(&ch, &src) != 0; decomp(dst, dstn, bufsz, ch, nt))
		;
	if (nt & 0b01)
		compbuf(dst, dstn);
	return alloc(ctx, dst, src.len, *dstn, 1, alignof(char8_t));
}

#define WRITE(ch) *dstn += rtoucs(dst + *dstn, bufsz - *dstn, (ch))

void
decomp(char8_t *dst, size_t *dstn, size_t bufsz, rune ch, enum normtype nt)
{
	if (uprop_get_hst(ch) != HST_NA) {
		int si = ch - SBASE;
		if (si < 0 || si > SCNT) {
			WRITE(ch);
			return;
		}
		rune l, v, t;
		l = LBASE + si / NCNT;
		v = VBASE + (si % NCNT) / TCNT;
		t = TBASE + si % TCNT;
		WRITE(l);
		WRITE(v);
		if (t != TBASE)
			WRITE(t);
	} else if (((nt & 0b10) && uprop_get_dt(ch) != DT_NONE)
	           || ((nt & 0b10) == 0 && uprop_get_dt(ch) == DT_CAN))
	{
		struct rview rv = uprop_get_dm(ch);
		for (size_t i = 0; i < rv.len; i++)
			decomp(dst, dstn, bufsz, rv.p[i], nt);
	} else {
		enum uprop_ccc ccc = uprop_get_ccc(ch);
		if (ccc == CCC_NR) {
			WRITE(ch);
			return;
		}

		int w;
		rune hc;
		char8_t *p = dst + *dstn;
		while (w = ucsprev(&hc, (const char8_t **)&p, dst)) {
			enum uprop_ccc ccc2 = uprop_get_ccc(hc);
			if (ccc2 == CCC_NR || ccc2 <= ccc) {
out:
				char8_t tmp[U8_LEN_MAX];
				int w2 = rtoucs(tmp, sizeof(tmp), ch);
				p += w;
				memmove(p + w2, p, dst + *dstn - p);
				memcpy(p, tmp, w2);
				*dstn += w2;
				return;
			}
		}

		/* Loop didn’t early-return; append to the start */
		goto out;
	}
}

#undef WRITE

/* The following implements the canonical composition algorithm, and it may be
   useful to read it to understand what’s going on.  It can be found under
   §3.11 Normalization Forms of the Unicode standard, subsection ‘Canonical
   Composition Algorithm’. */

void
compbuf(char8_t *dst, size_t *dstn)
{
	int wC, wL;
	rune C, L;
	struct u8view sv = {dst, *dstn};

	while ((wL = ucsnext(&L, &sv)) != 0) {
		if (uprop_get_ccc(L) != CCC_NR)
			continue;
		char8_t *after_L = (char8_t *)sv.p;

		enum uprop_ccc prevcc = 0;
		struct u8view sv_ = sv;

		while ((wC = ucsnext(&C, &sv_)) != 0) {
			enum uprop_ccc curcc = uprop_get_ccc(C);
			bool blocked = curcc <= prevcc;

			if (blocked) {
				if (curcc != CCC_NR)
					continue;
				if (curcc != prevcc)
					break;
			}

			prevcc = curcc;
			rune comp = uprop_get_cm(L, C);

			/* Try Hangul composition */
			if (comp == 0) {
				if (BETWEEN(LBASE, L, LBASE + LCNT - 1)
				    && BETWEEN(VBASE, C, VBASE + VCNT - 1))
				{
					comp = SBASE + ((L - LBASE) * NCNT + (C - VBASE) * TCNT);
				} else if (BETWEEN(TBASE, C, TBASE + TCNT - 1)
				           && BETWEEN(SBASE, L, SBASE + SCNT - 1)
				           && ((L - SBASE) % TCNT) == 0)
				{
					comp = L + (C - TBASE);
				}
			}

			if (comp != 0) {
				char8_t *after_C = (char8_t *)sv_.p;

				/* Shift bytes between L & C so that they’re contiguous with the
				   bytes after C */
				memmove(after_L + wC, after_L, after_C - wC - after_L);

				/* Write the composition into where L was */
				int w = rtoucs(after_L - wL, wL + wC, comp);

				/* Shift the bytes after L & C to be right after the new
				   composition */
				memmove(after_L - wL + w, after_L + wC,
				        *dstn - (after_L + wC - dst));

				/* Correct *dstn */
				int shift = wL + wC - w;
				*dstn -= shift;

				/* Fix the inner string view */
				sv_.p = after_C - shift;
				sv_.len = *dstn - (sv_.p - dst);

				/* Fix outer string view */
				sv.p = sv.p - wL + w;
				sv.len = *dstn - (sv.p - dst);
				after_L = (char8_t *)sv.p;

				/* Update the value of L */
				L = comp;
				wL = w;
				prevcc = CCC_NR;
			} else if (blocked)
				break;
		}
	}
}
