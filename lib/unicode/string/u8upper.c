#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8upper(char8_t *restrict dst, size_t dstn, const char8_t *src, size_t srcn,
        enum caseflags flags)
{
	struct ucctx ctx = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
		.ẞ = flags & CF_ẞ,
	};

	rune ch;
	size_t n = 0;

	while (u8next(&ch, &src, &srcn)) {
		struct rview rv = uprop_get_uc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++) {
			if (n >= dstn) {
				char8_t buf[U8_LEN_MAX];
				n += rtou8(buf, sizeof(buf), rv.p[i]);
			} else
				n += rtou8(dst + n, dstn - n, rv.p[i]);
		}

		if (ctx.lt) {
			enum uprop_ccc ccc;
			if (uprop_is_sd(ch))
				ctx.after_soft_dotted = true;
			else if ((ccc = uprop_get_ccc(ch)) == CCC_NR || ccc == CCC_L)
				ctx.after_soft_dotted = false;
		}
	}

	return n;
}
