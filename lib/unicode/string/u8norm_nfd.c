#include <string.h>

#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

#include <stdio.h>

static size_t quickchk_spn(struct u8view);
static void decomp(char8_t *, size_t *, size_t, rune);

/* Computed using a gen/scale-norm.c */
constexpr int NFD_SCALE = 3;

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
u8norm_nfd(size_t *dstn, struct u8view src, alloc_fn alloc, void *ctx)
{
	ASSUME(dstn != nullptr);
	ASSUME(alloc != nullptr);

	/* Pre-allocate a buffer with some initial capacity; there is no need to
	   check for overflow when computing bufsz because alloc() will handle the
	   overflow error for us. */
	size_t bufsz = src.len * NFD_SCALE;
	uint8_t *dst = alloc(ctx, nullptr, 0, src.len, NFD_SCALE, alignof(char8_t));

	/* Copy over the initial codepoints that are already in NFD; if the entire
	   string is in NFD then just return it immediately */
	size_t spn = quickchk_spn(src);
	memcpy(dst, src.p, spn);
	*dstn = spn;
	if (spn == src.len)
		return dst;
	VSHFT(&src, spn);

	rune ch;
	while (u8next(&ch, &src) != 0)
		decomp(dst, dstn, bufsz, ch);
	return alloc(ctx, dst, src.len, *dstn, 1, alignof(char8_t));
}

#define WRITE(ch) *dstn += rtou8(dst + *dstn, bufsz - *dstn, (ch))

void
decomp(char8_t *dst, size_t *dstn, size_t bufsz, rune ch)
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
	} else if (uprop_get_dt(ch) == DT_CAN) {
		struct rview rv = uprop_get_dm(ch);
		for (size_t i = 0; i < rv.len; i++)
			decomp(dst, dstn, bufsz, rv.p[i]);
	} else {
		enum uprop_ccc ccc = uprop_get_ccc(ch);
		if (ccc == CCC_NR) {
			WRITE(ch);
			return;
		}

		int w;
		rune hc;
		char8_t *p = dst + *dstn;
		while (w = u8prev(&hc, (const char8_t **)&p, dst)) {
			enum uprop_ccc ccc2 = uprop_get_ccc(hc);
			if (ccc2 == CCC_NR || ccc2 <= ccc) {
out:
				char8_t tmp[U8_LEN_MAX];
				int w2 = rtou8(tmp, sizeof(tmp), ch);
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

size_t
quickchk_spn(struct u8view src)
{
	rune ch;
	size_t spn = 0;
	enum uprop_ccc prv, cur;

	prv = cur = CCC_NR;

	for (int w; w = u8next(&ch, &src); spn += w) {
		if (uprop_get_nfd_qc(ch) == NFD_QC_N)
			break;
		if ((cur = uprop_get_ccc(ch)) < prv)
			break;
		prv = cur;
	}

	return spn;
}
