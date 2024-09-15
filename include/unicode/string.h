#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "_alloc_fn.h"
#include "_charN_t.h"
#include "_uNview.h"

/* clang-format off */

enum [[clang::flag_enum]] caseflags {
	CF_LANG_AZ = 1 << 0, /* Azeri; alias for CF_LANG_TR */
	CF_LANG_TR = 1 << 0, /* Turkish; alias for CF_LANG_AZ */
	CF_LANG_LT = 1 << 1, /* Lithuanian */
	CF_LANG_NL = 1 << 2, /* Dutch */
	CF_SS      = 1 << 3, /* Use ‘ẞ’ as the uppercase of ‘ß’; alias for CF_ẞ */
	CF_ẞ       = 1 << 3, /* Use ‘ẞ’ as the uppercase of ‘ß’; alias for CF_SS */
};

enum normform {
	/* If bit 0 is set, then composition is performed after decomposition.  If
	   bit-1 is set then compatibility (de)composition is used as opposed to
	   canonical (de)composition. */
	NF_NFD  = 0b00,
	NF_NFC  = 0b01,
	NF_NFKD = 0b10,
	NF_NFKC = 0b11,
};

/* clang-format on */

[[nodiscard]] size_t u8wdth(u8view_t, int);
[[nodiscard]] size_t u8gcnt(u8view_t);
[[nodiscard]] size_t u8wcnt(u8view_t);
[[nodiscard]] size_t u8wcnt_human(u8view_t);
size_t u8gnext(u8view_t *, u8view_t *);
size_t u8wnext(u8view_t *, u8view_t *);
size_t u8wnext_human(u8view_t *, u8view_t *);
[[nodiscard]] char8_t *u8casefold(size_t *, u8view_t, enum caseflags,
                                  alloc_fn, void *);
[[nodiscard]] char8_t *u8lower(size_t *, u8view_t, enum caseflags,
                               alloc_fn, void *);
[[nodiscard]] char8_t *u8title(size_t *, u8view_t, enum caseflags,
                               alloc_fn, void *);
[[nodiscard]] char8_t *u8upper(size_t *, u8view_t, enum caseflags,
                               alloc_fn, void *);
[[nodiscard]] char8_t *u8norm(size_t *, u8view_t, alloc_fn, void *,
                              enum normform);

/* Encoding-generic macros */
#define ucswdth(sv, ts)   _Generic((sv), u8view_t: u8wdth)((sv), (ts))
#define ucsgcnt(sv)       _Generic((sv), u8view_t: u8gcnt)((sv))
#define ucswcnt(sv)       _Generic((sv), u8view_t: u8wcnt)((sv))
#define ucswcnt_human(sv) _Generic((sv), u8view_t: u8wcnt_human)((sv))
#define ucsgnext(g, sv)   _Generic((sv), u8view_t *: u8gnext)((g), (sv))
#define ucswnext(g, sv)   _Generic((sv), u8view_t *: u8wnext)((g), (sv))
#define ucswnext_human(g, sv)                                                  \
	_Generic((sv), u8view_t *: u8wnext_human)((g), (sv))
#define ucscasefold(dstn, sv, flags, alloc, ctx)                               \
	_Generic((sv), u8view_t: u8casefold)((dstn), (sv), (flags), (alloc),  \
	                                          (ctx))
#define ucslower(dstn, sv, flags, alloc, ctx)                                  \
	_Generic((sv), u8view_t: u8lower)((dstn), (sv), (flags), (alloc),     \
	                                       (ctx))
#define ucstitle(dstn, sv, flags, alloc, ctx)                                  \
	_Generic((sv), u8view_t: u8title)((dstn), (sv), (flags), (alloc),     \
	                                       (ctx))
#define ucsupper(dstn, sv, flags, alloc, ctx)                                  \
	_Generic((sv), u8view_t: u8upper)((dstn), (sv), (flags), (alloc),     \
	                                       (ctx))
#define ucsnorm(dstn, sv, alloc, ctx, nf)                                      \
	_Generic((sv), u8view_t: u8norm)((dstn), (sv), (alloc), (ctx), (nf))

constexpr double U8CASEFOLD_SCALE = 3;
constexpr double U8LOWER_SCALE = 1.5;
constexpr double U8LOWER_SCALE_LT = 3;
constexpr double U8TITLE_SCALE = 3;
constexpr double U8UPPER_SCALE = 3;

#endif /* !MLIB_UNICODE_STRING_H */
