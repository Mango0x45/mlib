#include <alloc.h>
#include <errno.h>
#include <stdckdint.h>

#include "macros.h"
#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

char8_t *
u8casefold(size_t *dstn, u8view_t sv, caseflags_t flags, allocator_t mem)
{
	ASSUME(dstn != nullptr);

	size_t bufsz;
	if (ckd_mul(&bufsz, sv.len, (size_t)U8CASEFOLD_SCALE)) {
		errno = EOVERFLOW;
		return nullptr;
	}

	char8_t *dst = new(mem, typeof(*dst), bufsz);

	rune ch;
	size_t n = 0;
	while (u8next(&ch, &sv)) {
		struct rview rv = uprop_get_cf(ch, flags & CF_LANG_AZ);
		for (size_t i = 0; i < rv.len; i++)
			n += rtou8(dst + n, bufsz - n, rv.p[i]);
	}

	*dstn = n;
	return resz(mem, dst, bufsz, n);
}
