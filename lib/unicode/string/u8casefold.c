#include <errno.h>
#include <stdckdint.h>

#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

char8_t *
u8casefold(size_t *dstn, struct u8view sv, enum caseflags flags, alloc_fn alloc,
           void *alloc_ctx)
{
	ASSUME(dstn != nullptr);
	ASSUME(alloc != nullptr);

	size_t bufsz;
	if (ckd_mul(&bufsz, sv.len, (size_t)U8CASEFOLD_SCALE)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	char8_t *dst = alloc(alloc_ctx, nullptr, 0, bufsz, alignof(char8_t));
	if (dst == nullptr)
		return nullptr;

	rune ch;
	size_t n = 0;
	while (u8next(&ch, &sv)) {
		struct rview rv = uprop_get_cf(ch, flags & CF_LANG_AZ);
		for (size_t i = 0; i < rv.len; i++)
			n += rtou8(dst + n, bufsz - n, rv.p[i]);
	}

	*dstn = n;
	return alloc(alloc_ctx, dst, bufsz, n, alignof(char8_t));
}
