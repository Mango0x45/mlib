#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "_alloc_fn.h"
#include "_charN_t.h"
#include "_u8view.h"

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

[[nodiscard]] char8_t *u8casefold(size_t *, struct u8view, enum caseflags,
                                  alloc_fn, void *);
[[nodiscard]] char8_t *u8lower(size_t *, struct u8view, enum caseflags,
                               alloc_fn, void *);
[[nodiscard]] char8_t *u8title(size_t *, struct u8view, enum caseflags,
                               alloc_fn, void *);
[[nodiscard]] char8_t *u8upper(size_t *, struct u8view, enum caseflags,
                               alloc_fn, void *);

[[nodiscard]] char8_t *u8norm_nfd(size_t *, struct u8view, alloc_fn, void *);

constexpr double U8CASEFOLD_SCALE = 3;
constexpr double U8LOWER_SCALE = 1.5;
constexpr double U8LOWER_SCALE_LT = 3;
constexpr double U8TITLE_SCALE = 3;
constexpr double U8UPPER_SCALE = 3;

#endif /* !MLIB_UNICODE_STRING_H */
