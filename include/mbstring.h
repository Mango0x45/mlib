#ifndef MLIB_MBSTRING_H
#define MLIB_MBSTRING_H

#include <stddef.h>

#include "_charN_t.h"
#include "_rune.h"
#include "_u8view.h"

#define U8(...) \
	((struct u8view){__VA_OPT__(u8##__VA_ARGS__, sizeof(u8##__VA_ARGS__) - 1)})

#define VSHFT(sv, n) ((sv)->p += (n), (sv)->len -= (n))

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
struct u8view u8split(struct u8view *, rune);

#endif /* !MLIB_MBSTRING_H */
