#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "_charN_t.h"
#include "_u8view.h"

#define mlib_warn_trunc nodiscard("don’t forget to check for truncation")

/* clang-format off */

enum [[clang::flag_enum]] caseflags {
	CF_LANG_AZ = 1 << 0, /* Azeri; alias for CF_LANG_TR */
	CF_LANG_TR = 1 << 0, /* Turkish; alias for CF_LANG_AZ */
	CF_LANG_LT = 1 << 1, /* Lithuanian */
	CF_LANG_NL = 1 << 2, /* Dutch */
	CF_SS      = 1 << 3, /* Use ‘ẞ’ as the uppercase of ‘ß’; alias for CF_ẞ */
	CF_ẞ       = 1 << 3, /* Use ‘ẞ’ as the uppercase of ‘ß’; alias for CF_SS */
};

/* clang-format on */

[[nodiscard]] size_t u8gcnt(struct u8view);
[[nodiscard]] size_t u8wcnt(struct u8view);
[[nodiscard]] size_t u8wcnt_human(struct u8view);

size_t u8gnext(struct u8view *, struct u8view *);
size_t u8wnext(struct u8view *, struct u8view *);
size_t u8wnext_human(struct u8view *, struct u8view *);

[[mlib_warn_trunc]] size_t u8lower(char8_t *restrict, size_t, struct u8view,
                                   enum caseflags);
[[mlib_warn_trunc]] size_t u8title(char8_t *restrict, size_t, struct u8view,
                                   enum caseflags);
[[mlib_warn_trunc]] size_t u8upper(char8_t *restrict, size_t, struct u8view,
                                   enum caseflags);
[[mlib_warn_trunc]] size_t u8casefold(char8_t *restrict, size_t, struct u8view,
                                      enum caseflags);

constexpr double U8LOWER_SCALE = 1.5;
constexpr double U8LOWER_SCALE_LT = 3;
constexpr double U8TITLE_SCALE = 3;
constexpr double U8UPPER_SCALE = 3;

#undef mlib_warn_trunc

#endif /* !MLIB_UNICODE_STRING_H */
