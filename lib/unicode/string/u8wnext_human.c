#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8wnext_human(struct u8view *dst, struct u8view *sv)
{
	ASSUME(sv != nullptr);
	ASSUME(sv->p != nullptr);

	struct u8view w;
	while (u8wnext(&w, sv)) {
		rune ch;
		struct u8view cpy = w;
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
