#include "macros.h"
#include "mbstring.h"

rune
u8cut(u8view_t *restrict x, u8view_t *restrict y, const rune *seps,
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
