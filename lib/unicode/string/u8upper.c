#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8upper(char8_t *dst, size_t dstn, const char8_t *src, size_t srcn,
        enum upper_flags flags)
{
	struct ucctx ctx = {
		.az_or_tr = flags & UF_LANG_AZ,
		.cap_eszett = flags & UF_ẞ,
	};

	rune ch;
	size_t n = 0;
	bool prev_was_i = false;

	while (u8next(&ch, &src, &srcn)) {
		if (ch == 0x307 && prev_was_i && (flags & UF_LANG_LT))
			ctx.lt_after_i = true;

		struct rview rv = uprop_get_uc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		prev_was_i = ch == 'i';
		ctx.lt_after_i = false;
	}

	return n;
}
