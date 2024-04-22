#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8wnext_human(struct u8view *dst, const char8_t **s, size_t *n)
{
	ASSUME(n != nullptr);
	ASSUME(s != nullptr);
	ASSUME(*s != nullptr);

	struct u8view w;
	while (u8wnext(&w, s, n)) {
		rune ch;
		struct u8view cpy = w;
		while (u8next(&ch, U8_ARGSP(cpy))) {
			if (uprop_get_gc(ch) & (GC_L | GC_N)) {
				if (dst != nullptr)
					*dst = w;
				return w.len;
			}
		}
	}

	return 0;
}
