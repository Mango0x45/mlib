#ifndef MLIB_MBSTRING_H
#define MLIB_MBSTRING_H

#include <stddef.h>

#include "_charN_t.h"
#include "_rune.h"
#include "_uNview.h"

#define U8(...)                                                                \
	((struct u8view){__VA_OPT__(u8##__VA_ARGS__, sizeof(u8##__VA_ARGS__) - 1)})
#define U16(...)                                                               \
	((struct u16view){__VA_OPT__(u##__VA_ARGS__, sizeof(u##__VA_ARGS__) - 1)})
#define U32(...)                                                               \
	((struct u32view){__VA_OPT__(U##__VA_ARGS__, sizeof(U##__VA_ARGS__) - 1)})

#define VSHFT(sv, n) ((sv)->p += (n), (sv)->len -= (n))

/* clang-format off */
#define u8byte1(x) (((x) & 0x80) == 0x00)
#define u8byte2(x) (((x) & 0xE0) == 0xC0)
#define u8byte3(x) (((x) & 0xF0) == 0xE0)
#define u8byte4(x) (((x) & 0xF8) == 0xF0)
#define u8bytec(x) (((x) & 0xC0) == 0x80)
/* clang-format on */

constexpr int U8_LEN_MAX = 4;
constexpr rune U8_1B_MAX = 0x00007F;
constexpr rune U8_2B_MAX = 0x0007FF;
constexpr rune U8_3B_MAX = 0x00FFFF;
constexpr rune U8_4B_MAX = 0x10FFFF;

constexpr rune MBEND = 0x110000;

#define PRIsSV          ".*s"
#define SV_PRI_ARGS(sv) ((int)(sv).len), ((sv).p)

int rtou8(char8_t *, size_t, rune);
int u8next(rune *, struct u8view *);
int u8prev(rune *, const char8_t **, const char8_t *);
int u8tor(rune *, const char8_t *);
[[nodiscard]] bool u8haspfx(struct u8view, struct u8view);
[[nodiscard]] bool u8hassfx(struct u8view, struct u8view);
[[nodiscard]] const char8_t *u8chk(struct u8view);
[[nodiscard]] const char8_t *u8chr(struct u8view, rune);
[[nodiscard]] const char8_t *u8rchr(struct u8view, rune);
[[nodiscard]] int u8cmp(struct u8view, struct u8view);
[[nodiscard]] size_t u8cspn(struct u8view, const rune *, size_t);
[[nodiscard]] size_t u8len(struct u8view);
[[nodiscard]] size_t u8spn(struct u8view, const rune *, size_t);
rune u8cut(struct u8view *restrict, struct u8view *restrict, const rune *,
           size_t);

/* Encoding-generic macros */
#define rtoucs(buf, bufsz, ch)                                                 \
	_Generic((buf), char8_t *: rtou8)((buf), (bufsz), (ch))
#define ucsnext(ch, sv) _Generic((sv), struct u8view: u8next)((ch), (sv))
#define ucsprev(ch, sv, start)                                                 \
	_Generic((sv), const char8_t **: u8prev)((ch), (sv), (start))
#define ucstor(ch, p)                                                          \
	_Generic((p), char8_t *: u8tor, const char8_t *: u8tor)((ch), (p))
#define ucshaspfx(sv, pfx) _Generic((sv), struct u8view: u8haspfx)((sv), (pfx))
#define ucshassfx(sv, sfx) _Generic((sv), struct u8view: u8hassfx)((sv), (sfx))
#define ucschk(sv)         _Generic((sv), struct u8view: u8chk)((sv))
#define ucschr(sv, ch)     _Generic((sv), struct u8view: u8chr)((sv), (ch))
#define ucsrchr(sv, ch)    _Generic((sv), struct u8view: u8rchr)((sv), (ch))
#define ucscmp(lhs, rhs)   _Generic((lhs), struct u8view: u8cmp)((lhs), (rhs))
#define ucscspn(sv, delims, ndelims)                                           \
	_Generic((sv), struct u8view: u8cspn)((sv), (delims), (ndelims))
#define ucslen(sv) _Generic((sv), struct u8view: u8len)((sv))
#define ucsspn(sv, delims, ndelims)                                            \
	_Generic((sv), struct u8view: u8spn)((sv), (delims), (ndelims))
#define ucscut(x, y, seps, nseps)                                              \
	_Generic((y), struct u8view *: u8cut)(x, y, seps, nseps)

#endif /* !MLIB_MBSTRING_H */
