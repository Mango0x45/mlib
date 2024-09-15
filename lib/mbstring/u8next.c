#include "mbstring.h"

int
u8next(rune *ch, u8view_t *sv)
{
	int n = 0;

	if (sv->len) {
		rune _;
		n = u8tor(ch ? ch : &_, sv->p);
		VSHFT(sv, n);
	}

	return n;
}
