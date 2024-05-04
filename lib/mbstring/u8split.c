#include "mbstring.h"

struct u8view
u8split(const char8_t **p, size_t *n, rune ch)
{
	struct u8view lhs = {.p = *p};
	if ((*p = u8chr(*p, *n, ch)) == nullptr) {
		lhs.len = *n;
		*n = 0;
	} else {
		lhs.len = *p - lhs.p;
		*n -= lhs.len;
		u8next(nullptr, p, n);
	}
	return lhs;
}
