#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8wnext_human(u8view_t *dst, u8view_t *sv)
{
	ASSUME(sv != nullptr);
	ASSUME(sv->p != nullptr);

	u8view_t w;
	while (u8wnext(&w, sv)) {
		rune ch;
		u8view_t cpy = w;
		while (u8next(&ch, &cpy)) {
			if (uprop_get_gc(ch) & (GC_L | GC_N)) {
				if (dst != nullptr)
					*dst = w;
				return w.len;
			}
		}
	}

	return 0;
}
