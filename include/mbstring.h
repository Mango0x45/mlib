#ifndef MLIB_MBSTRING_H
#define MLIB_MBSTRING_H

#include <stddef.h>

#include "_charN_t.h"
#include "_rune.h"
#include "_uNview.h"

#define U8(...) \
	((u8view_t){__VA_OPT__(u8##__VA_ARGS__, sizeof(u8##__VA_ARGS__) - 1)})
#define U16(...) \
	((u16view_t){__VA_OPT__(u##__VA_ARGS__, sizeof(u##__VA_ARGS__) - 1)})
#define U32(...) \
	((u32view_t){__VA_OPT__(U##__VA_ARGS__, sizeof(U##__VA_ARGS__) - 1)})

#define U8C(s)  {u8##s, sizeof(u8##s) - 1}
#define U16C(s) { u##s, sizeof (u##s) - 1}
#define U32C(s) { U##s, sizeof (U##s) - 1}

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
int u8next(rune *, u8view_t *);
int u8prev(rune *, const char8_t **, const char8_t *);
int u8tor(rune *, const char8_t *);
[[nodiscard]] bool u8haspfx(u8view_t, u8view_t);
[[nodiscard]] bool u8hassfx(u8view_t, u8view_t);
[[nodiscard]] const char8_t *u8chk(u8view_t);
[[nodiscard]] const char8_t *u8chr(u8view_t, rune);
[[nodiscard]] const char8_t *u8rchr(u8view_t, rune);
[[nodiscard]] int u8cmp(u8view_t, u8view_t);
[[nodiscard]] size_t u8cspn(u8view_t, const rune *, size_t);
[[nodiscard]] size_t u8len(u8view_t);
[[nodiscard]] size_t u8spn(u8view_t, const rune *, size_t);
rune u8cut(u8view_t *restrict, u8view_t *restrict, const rune *,
           size_t);

/* Encoding-generic macros */
#define rtoucs(buf, bufsz, ch)                                                 \
	_Generic((buf), char8_t *: rtou8)((buf), (bufsz), (ch))
#define ucsnext(ch, sv) _Generic((sv), u8view_t *: u8next)((ch), (sv))
#define ucsprev(ch, p, start)                                                  \
	_Generic((p), const char8_t **: u8prev)((ch), (p), (start))
#define ucstor(ch, p)                                                          \
	_Generic((p), char8_t *: u8tor, const char8_t *: u8tor)((ch), (p))
#define ucshaspfx(sv, pfx) _Generic((sv), u8view_t: u8haspfx)((sv), (pfx))
#define ucshassfx(sv, sfx) _Generic((sv), u8view_t: u8hassfx)((sv), (sfx))
#define ucschk(sv)         _Generic((sv), u8view_t: u8chk)((sv))
#define ucschr(sv, ch)     _Generic((sv), u8view_t: u8chr)((sv), (ch))
#define ucsrchr(sv, ch)    _Generic((sv), u8view_t: u8rchr)((sv), (ch))
#define ucscmp(lhs, rhs)   _Generic((lhs), u8view_t: u8cmp)((lhs), (rhs))
#define ucscspn(sv, delims, ndelims)                                           \
	_Generic((sv), u8view_t: u8cspn)((sv), (delims), (ndelims))
#define ucslen(sv) _Generic((sv), u8view_t: u8len)((sv))
#define ucsspn(sv, delims, ndelims)                                            \
	_Generic((sv), u8view_t: u8spn)((sv), (delims), (ndelims))
#define ucscut(x, y, seps, nseps)                                              \
	_Generic((y), u8view_t *: u8cut)(x, y, seps, nseps)

#endif /* !MLIB_MBSTRING_H */
