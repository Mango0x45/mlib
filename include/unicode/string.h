#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "__charN_t.h"
#include "__u8view.h"

/* clang-format off */

enum [[clang::__flag_enum__]] caseflags {
	CF_LANG_AZ = 1 << 0, /* Azeri; alias for UF_LANG_TR */
	CF_LANG_TR = 1 << 0, /* Turkish; alias for UF_LANG_AZ */
	CF_LANG_LT = 1 << 1, /* Lithuanian */
	CF_ẞ       = 1 << 2, /* Use ‘ẞ’ as the uppercase of ‘ß’ */
};

/* clang-format on */

size_t u8glen(const char8_t *, size_t);
size_t u8gnext(struct u8view *, const char8_t **, size_t *);

size_t u8casefold(char8_t *restrict, size_t, const char8_t *, size_t,
                  enum caseflags);
size_t u8lower(char8_t *restrict, size_t, const char8_t *, size_t,
               enum caseflags);
size_t u8upper(char8_t *restrict, size_t, const char8_t *, size_t,
               enum caseflags);

#endif /* !MLIB_UNICODE_STRING_H */
