#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "__charN_t.h"
#include "__u8view.h"

enum [[clang::__flag_enum__]] upper_flags {
	UF_LANG_AZ = 1 << 0,
	UF_LANG_TR = 1 << 0,
	UF_LANG_LT = 1 << 1,
	UF_ẞ       = 1 << 2,
};

size_t u8glen(const char8_t *, size_t);
size_t u8gnext(struct u8view *, const char8_t **, size_t *);

size_t u8upper(char8_t *, size_t, const char8_t *, size_t, enum upper_flags);

#endif /* !MLIB_UNICODE_STRING_H */
