#include <errno.h>
#include <stdckdint.h>

#include "alloc.h"
#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

char8_t *
u8upper(size_t *dstn, u8view_t sv, caseflags_t flags, allocator_t mem)
{
	ASSUME(dstn != nullptr);

	struct ucctx ctx = {
		.az_or_tr = flags & CF_LANG_AZ,
		.lt = flags & CF_LANG_LT,
		.ẞ = flags & CF_ẞ,
	};

	size_t bufsz;
	if (ckd_mul(&bufsz, sv.len, (size_t)U8UPPER_SCALE)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	char8_t *dst = new(mem, typeof(*dst), bufsz);

	rune ch;
	size_t n = 0;
	while (u8next(&ch, &sv)) {
		struct rview rv = uprop_get_uc(ch, ctx);
		for (size_t i = 0; i < rv.len; i++)
			n += rtou8(dst + n, bufsz - n, rv.p[i]);
		if (ctx.lt) {
			enum uprop_ccc ccc;
			if (uprop_is_sd(ch))
				ctx.after_soft_dotted = true;
			else if ((ccc = uprop_get_ccc(ch)) == CCC_NR || ccc == CCC_L)
				ctx.after_soft_dotted = false;
		}
	}

	*dstn = n;
	return resz(mem, dst, bufsz, n);
}
