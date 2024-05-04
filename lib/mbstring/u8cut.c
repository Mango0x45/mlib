#include "macros.h"
#include "mbstring.h"

rune
u8cut(struct u8view *restrict x, struct u8view *restrict y, const rune *seps,
      size_t n)
{
	ASSUME(y != nullptr);
	ASSUME(seps != nullptr);
	size_t off = u8cspn(*y, seps, n);
	if (x != nullptr) {
		x->p = y->p;
		x->len = off;
	}
	VSHFT(y, off);
	rune ch = MBEND;
	u8next(&ch, y);
	return ch;
}
