#ifndef MLIB_MBSTRING_H
#define MLIB_MBSTRING_H

#include <stddef.h>

#include "__charN_t.h"
#include "__qmacros.h"
#include "__rune.h"
#include "__u8view.h"

#define U8V(s)      ((struct u8view){.p = (s), .len = sizeof(s) - 1})
#define U8_ARGS(s)  ((s).p), ((s).len)
#define U8_ARGSP(s) (&(s).p), (&(s).len)

/* clang-format off */
#define u8byte1(x) (((x) & 0x80) == 0x00)
#define u8byte2(x) (((x) & 0xE0) == 0xC0)
#define u8byte3(x) (((x) & 0xF0) == 0xE0)
#define u8byte4(x) (((x) & 0xF8) == 0xF0)
#define u8bytec(x) (((x) & 0xC0) == 0x80)
/* clang-format on */

constexpr rune U8_1B_MAX = 0x00007F;
constexpr rune U8_2B_MAX = 0x0007FF;
constexpr rune U8_3B_MAX = 0x00FFFF;
constexpr rune U8_4B_MAX = 0x10FFFF;

constexpr int U8_LEN_MAX = 4;

#define PRIsU8          ".*s"
#define U8_PRI_ARGS(sv) ((int)(sv).len), ((sv).p)

[[__nodiscard__]] bool u8haspfx(const char8_t *, size_t, const char8_t *,
                                size_t);
[[__nodiscard__]] bool u8hassfx(const char8_t *, size_t, const char8_t *,
                                size_t);

[[__nodiscard__]] char8_t *u8chk(const char8_t *, size_t);

[[__nodiscard__]] char8_t *u8chr(const char8_t *, size_t, rune);
[[__nodiscard__]] char8_t *u8rchr(const char8_t *, size_t, rune);

int rtou8(char8_t *, size_t, rune);
int u8tor(rune *, const char8_t *);

[[__nodiscard__]] int u8cmp(const char8_t *, size_t, const char8_t *, size_t);

int u8next(rune *, const char8_t **, size_t *);
int u8prev(rune *, const char8_t **, const char8_t *);

[[__nodiscard__]] size_t u8spn(const char8_t *, size_t, const rune *, size_t);
[[__nodiscard__]] size_t u8cspn(const char8_t *, size_t, const rune *, size_t);

[[__nodiscard__]] size_t u8len(const char8_t *, size_t);

#define u8chk(s, n)      __MLIB_Q_PTR(char8_t, u8chk, (s), (s), (n))
#define u8chr(s, n, ch)  __MLIB_Q_PTR(char8_t, u8chr, (s), (s), (n), (ch))
#define u8rchr(s, n, ch) __MLIB_Q_PTR(char8_t, u8rchr, (s), (s), (n), (ch))

#endif /* !MLIB_MBSTRING_H */
