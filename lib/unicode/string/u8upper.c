#include <errno.h>
#include <stdckdint.h>

#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

char8_t *
u8upper(size_t *dstn, struct u8view sv, enum caseflags flags, alloc_fn alloc,
        void *alloc_ctx)
{
	ASSUME(dstn != nullptr);
	ASSUME(alloc != nullptr);

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

	char8_t *dst = alloc(alloc_ctx, nullptr, 0, bufsz, 1, alignof(char8_t));

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
	return alloc(alloc_ctx, dst, bufsz, n, 1, alignof(char8_t));
}
