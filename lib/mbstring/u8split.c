#include "mbstring.h"

struct u8view
u8split(struct u8view *rhs, rune ch)
{
	struct u8view lhs = {.p = rhs->p};
	if ((rhs->p = u8chr(*rhs, ch)) == nullptr) {
		lhs.len = rhs->len;
		rhs->len = 0;
	} else {
		lhs.len = rhs->p - lhs.p;
		rhs->len -= lhs.len;
		u8next(nullptr, rhs);
	}
	return lhs;
}
