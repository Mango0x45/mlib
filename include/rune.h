#ifndef MLIB_RUNE_H
#define MLIB_RUNE_H

#include <inttypes.h>

#include "__rune.h"

#define __MLIB_RUNE_PRIDEF(c) PRI##c##LEAST32
#define __MLIB_RUNE_SCNDEF(c) SCN##c##LEAST32

#ifdef PRIBLEAST32
#	define PRIBRUNE __MLIB_RUNE_PRIDEF(B)
#endif
#define PRIbRUNE __MLIB_RUNE_PRIDEF(b)
#define PRIdRUNE __MLIB_RUNE_PRIDEF(d)
#define PRIiRUNE __MLIB_RUNE_PRIDEF(i)
#define PRIoRUNE __MLIB_RUNE_PRIDEF(o)
#define PRIuRUNE __MLIB_RUNE_PRIDEF(u)
#define PRIxRUNE __MLIB_RUNE_PRIDEF(x)
#define PRIXRUNE __MLIB_RUNE_PRIDEF(X)

#define SCNbRUNE __MLIB_RUNE_SCNDEF(b)
#define SCNdRUNE __MLIB_RUNE_SCNDEF(d)
#define SCNiRUNE __MLIB_RUNE_SCNDEF(i)
#define SCNuRUNE __MLIB_RUNE_SCNDEF(u)
#define SCNoRUNE __MLIB_RUNE_SCNDEF(o)
#define SCNxRUNE __MLIB_RUNE_SCNDEF(x)

#define RUNE_C(x) UINT32_C(x)

constexpr rune RUNE_ERROR = 0x00FFFD;

constexpr rune ASCII_MAX = 0x00007F;
constexpr rune LATIN1_MAX = 0x0000FF;
constexpr rune RUNE_MAX = 0x10FFFF;

#endif /* !MLIB_RUNE_H */
