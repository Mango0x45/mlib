#include "rune.h"
#include "mbstring.h"

const char8_t *
u8chk(struct u8view sv)
{
	int w;
	rune ch;

	while (w = u8next(&ch, &sv)) {
		if (ch == RUNE_ERROR)
			return sv.p - w;
	}

	return nullptr;
}
