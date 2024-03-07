#ifndef MLIB_MBSTRING_H
#define MLIB_MBSTRING_H

#include <stddef.h>

#include "__charN_t.h"
#include "__qmacros.h"
#include "__rune.h"

#if !__MLIB_HAS_U8VIEW
#	define __MLIB_HAS_U8VIEW 1

struct u8view {
	const char8_t *p;
	size_t len;
};
#endif

#define U8_BYTE_1(x) (((x) & 0x80) == 0x00)
#define U8_BYTE_2(x) (((x) & 0xE0) == 0xC0)
#define U8_BYTE_3(x) (((x) & 0xF0) == 0xE0)
#define U8_BYTE_4(x) (((x) & 0xF8) == 0xF0)
#define U8_BYTE_C(x) (((x) & 0xC0) == 0x80)

static const rune U8_1B_MAX = 0x00007FL;
static const rune U8_2B_MAX = 0x0007FFL;
static const rune U8_3B_MAX = 0x00FFFFL;
static const rune U8_4B_MAX = 0x10FFFFL;

#define PRIsU8          ".*s"
#define U8_PRI_ARGS(sv) ((int)(sv).len), ((sv).p)

char8_t *u8chk(const char8_t *, size_t);
char8_t *u8chr(const char8_t *, rune, size_t);
char8_t *u8rchr(const char8_t *, rune, size_t);
int rtou8(char8_t *, rune, size_t);
int u8cmp(struct u8view, struct u8view);
int u8next(rune *, const char8_t **, size_t *);
int u8prev(rune *, const char8_t **, const char8_t *);
int u8tor(rune *, const char8_t *);
size_t u8cspn(const char8_t *, size_t, const rune *, size_t);
size_t u8len(const char8_t *, size_t);
size_t u8spn(const char8_t *, size_t, const rune *, size_t);

#if !__MLIB_NO_MACRO_WRAPPER
#	define u8chk(s, n)      __MLIB_Q_PTR(char8_t, u8chk, (s), (s), (n))
#	define u8chr(s, ch, n)  __MLIB_Q_PTR(char8_t, u8chr, (s), (s), (ch), (n))
#	define u8rchr(s, ch, n) __MLIB_Q_PTR(char8_t, u8rchr, (s), (s), (ch), (n))
#endif

static const int U8_LEN_MAX = 4;

#endif /* !MLIB_MBSTRING_H */
