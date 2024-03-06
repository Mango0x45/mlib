#include "mbstring.h"

size_t
u8spn(const char8_t *s, size_t n, const rune *p, size_t m)
{
	rune ch;
	size_t k = 0, l;

	while ((l = u8next(&ch, &s, &n))) {
		for (size_t i = 0; i < m; i++) {
			if (p[i] == ch) {
				k += l;
				goto found;
			}
		}

		break;
found:;
	}

	return k;
}
