#if 0
cd "${0%/*}/../.."
trap 'rm -f /tmp/scale-norm' EXIT
cc -Iinclude -std=c23 -Wno-attributes -fsanitize=address,undefined \
	-o /tmp/scale-norm gen/string/scale-norm.c libmlib.a
/tmp/scale-norm
exit 0
#endif

#include <stdio.h>

#include <macros.h>
#include <rune.h>
#include <unicode/prop.h>

static double scale(rune ch);
static int bcnt(rune ch);
static int hscnt(rune ch);
static int scale2(rune ch);

int
main(void)
{
	double maxscale = 1;
	for (rune ch = 0; ch <= RUNE_MAX; ch++) {
		double n = scale(ch);
		maxscale = MAX(n, maxscale);
	}
	printf("NFD\t%g\n", maxscale);
}

double
scale(rune ch)
{
	int old, new;
	old = bcnt(ch);
	new = scale2(ch);
	return (double)new / (double)old;
}

int
scale2(rune ch)
{
	if (uprop_get_hst(ch) != HST_NA)
		return hscnt(ch);
	if (uprop_get_dt(ch) != DT_CAN)
		return bcnt(ch);
	int acc = 0;
	struct rview rv = uprop_get_dm(ch);
	for (size_t i = 0; i < rv.len; i++)
		acc += scale2(rv.p[i]);
	return acc;
}

int
bcnt(rune ch)
{
	return ch < 0x80 ? 1 : ch < 0x800 ? 2 : ch < 0x10'000 ? 3 : 4;
}

int
hscnt(rune s)
{
	const rune sbase = 0xAC00, lbase = 0x1100, vbase = 0x1161, tbase = 0x11A7;
	const int lcnt = 19, vcnt = 21, tcnt = 28, ncnt = 588, scnt = 11172;

	int sidx = s - sbase;
	if (sidx < 0 || sidx > scnt)
		return bcnt(s);
	rune l = lbase + sidx / ncnt;
	rune v = vbase + (sidx % ncnt) / tcnt;
	rune t = tbase + sidx % tcnt;
	int acc = bcnt(l) + bcnt(v);
	if (t != tbase)
		acc += bcnt(t);
	return acc;
}
