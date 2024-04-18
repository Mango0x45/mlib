#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "_charN_t.h"
#include "_u8view.h"

/* clang-format off */

enum [[clang::flag_enum]] caseflags {
	CF_LANG_AZ = 1 << 0, /* Azeri; alias for CF_LANG_TR */
	CF_LANG_TR = 1 << 0, /* Turkish; alias for CF_LANG_AZ */
	CF_LANG_LT = 1 << 1, /* Lithuanian */
	CF_ẞ       = 1 << 2, /* Use ‘ẞ’ as the uppercase of ‘ß’ */
};

/* clang-format on */

[[nodiscard]] size_t u8glen(const char8_t *, size_t);
size_t u8gnext(struct u8view *, const char8_t **, size_t *);

#define mlib_warn_trunc nodiscard("don’t forget to check for truncation")
[[mlib_warn_trunc]] size_t u8casefold(char8_t *restrict, size_t,
                                      const char8_t *, size_t, enum caseflags);
[[mlib_warn_trunc]] size_t u8lower(char8_t *restrict, size_t, const char8_t *,
                                   size_t, enum caseflags);
[[mlib_warn_trunc]] size_t u8upper(char8_t *restrict, size_t, const char8_t *,
                                   size_t, enum caseflags);
#undef mlib_warn_trunc

constexpr double U8LOWER_SCALE    = 1.5;
constexpr double U8LOWER_SCALE_LT = 3;
constexpr double U8TITLE_SCALE    = 3;
constexpr double U8UPPER_SCALE    = 3;

#endif /* !MLIB_UNICODE_STRING_H */
