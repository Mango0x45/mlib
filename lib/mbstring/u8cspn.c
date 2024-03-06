#include "mbstring.h"

size_t
u8cspn(const char8_t *s, size_t n, const rune *p, size_t m)
{
	rune ch;
	size_t k, l;

	for (k = 0; (l = u8next(&ch, &s, &n)); k += l) {
		for (size_t i = 0; i < m; i++) {
			if (p[i] == ch)
				goto found;
		}
	}

found:
	return k;
}
