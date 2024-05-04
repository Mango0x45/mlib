#include "mbstring.h"

size_t
u8spn(struct u8view sv, const rune *p, size_t n)
{
	rune ch;
	size_t k = 0, w;

	while (w = u8next(&ch, &sv)) {
		for (size_t i = 0; i < n; i++) {
			if (p[i] == ch) {
				k += w;
				goto found;
			}
		}

		break;
found:;
	}

	return k;
}
