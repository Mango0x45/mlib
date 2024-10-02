#include <errno.h>
#include <inttypes.h>
#include <stdckdint.h>
#include <stddef.h>
#include <string.h>

#include "alloc.h"
#include "macros.h"
#include "mbstring.h"
#include "unicode/_cm.h"
#include "unicode/prop.h"
#include "unicode/string.h"

#define BETWEEN(x, y, z) ((x) <= (y) && (y) <= (z))

typedef uint_least8_t (*qcfn)(rune);

constexpr uint_least8_t YES = 1;

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

static void decomp(char8_t *, size_t *, size_t, rune, normform_t);
static void compbuf(char8_t *, size_t *);

static const qcfn qc_lookup[] = {
	[NF_NFC]  = (qcfn)uprop_get_nfc_qc,
	[NF_NFD]  = (qcfn)uprop_get_nfd_qc,
	[NF_NFKC] = (qcfn)uprop_get_nfkc_qc,
	[NF_NFKD] = (qcfn)uprop_get_nfkd_qc,
};

char8_t *
u8norm(size_t *dstn, u8view_t src, allocator_t mem, normform_t nf)
{
	ASSUME(dstn != nullptr);
	ASSUME(BETWEEN(0, nf, 4));

	{
		qcfn f = qc_lookup[nf];
		u8view_t sv = src;
		enum uprop_ccc prvcc = 0, curcc;
		for (rune ch; ucsnext(&ch, &sv) != 0; prvcc = curcc) {
			curcc = uprop_get_ccc(ch);
			if ((prvcc > curcc && curcc != CCC_NR) || (f(ch) != YES))
				goto no;
		}

		*dstn = src.len;
		char8_t *dst = new(mem, typeof(*dst), src.len);
		return memcpy(dst, src.p, src.len);
	}

no:
	int scale = (nf & 0b10) ? NFKD_SCALE : NFD_SCALE;
	ptrdiff_t bufsz;
	if (ckd_mul(&bufsz, src.len, scale)) {
		errno = EOVERFLOW;
		return nullptr;
	}
	char8_t *dst = new(mem, typeof(*dst), bufsz);

	*dstn = 0;
	for (rune ch; ucsnext(&ch, &src) != 0; decomp(dst, dstn, bufsz, ch, nf))
		;
	if (nf & 0b01)
		compbuf(dst, dstn);
	return resz(mem, dst, bufsz, *dstn);
}

#define WRITE(ch) *dstn += rtoucs(dst + *dstn, bufsz - *dstn, (ch))

void
decomp(char8_t *dst, size_t *dstn, size_t bufsz, rune ch, normform_t nf)
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
	} else if (((nf & 0b10) != 0 && uprop_get_dt(ch) != DT_NONE)
	        || ((nf & 0b10) == 0 && uprop_get_dt(ch) == DT_CAN))
	{
		struct rview rv = uprop_get_dm(ch);
		for (size_t i = 0; i < rv.len; i++)
			decomp(dst, dstn, bufsz, rv.p[i], nf);
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
	u8view_t sv = {dst, *dstn};

	while ((wL = ucsnext(&L, &sv)) != 0) {
		if (uprop_get_ccc(L) != CCC_NR)
			continue;
		char8_t *after_L = (char8_t *)sv.p;

		enum uprop_ccc prevcc = 0;
		u8view_t sv_ = sv;

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
