#include "mbstring.h"

size_t
u8cspn(u8view_t sv, const rune *p, size_t n)
{
	rune ch;
	size_t k, w;

	for (k = 0; w = u8next(&ch, &sv); k += w) {
		for (size_t i = 0; i < n; i++) {
			if (p[i] == ch)
				goto found;
		}
	}

found:
	return k;
}
