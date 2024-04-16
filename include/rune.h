#ifndef MLIB_RUNE_H
#define MLIB_RUNE_H

#include <inttypes.h>

#include "_rune.h"

#define _MLIB_RUNE_PRIDEF(c) PRI##c##LEAST32
#define _MLIB_RUNE_SCNDEF(c) SCN##c##LEAST32

#ifdef PRIBLEAST32
#	define PRIBRUNE _MLIB_RUNE_PRIDEF(B)
#endif
#define PRIbRUNE _MLIB_RUNE_PRIDEF(b)
#define PRIdRUNE _MLIB_RUNE_PRIDEF(d)
#define PRIiRUNE _MLIB_RUNE_PRIDEF(i)
#define PRIoRUNE _MLIB_RUNE_PRIDEF(o)
#define PRIuRUNE _MLIB_RUNE_PRIDEF(u)
#define PRIxRUNE _MLIB_RUNE_PRIDEF(x)
#define PRIXRUNE _MLIB_RUNE_PRIDEF(X)

#define SCNbRUNE _MLIB_RUNE_SCNDEF(b)
#define SCNdRUNE _MLIB_RUNE_SCNDEF(d)
#define SCNiRUNE _MLIB_RUNE_SCNDEF(i)
#define SCNuRUNE _MLIB_RUNE_SCNDEF(u)
#define SCNoRUNE _MLIB_RUNE_SCNDEF(o)
#define SCNxRUNE _MLIB_RUNE_SCNDEF(x)

#define RUNE_C(x) UINT32_C(x)

constexpr rune RUNE_ERROR = 0x00FFFD;

constexpr rune ASCII_MAX = 0x00007F;
constexpr rune LATIN1_MAX = 0x0000FF;
constexpr rune RUNE_MAX = 0x10FFFF;

#endif /* !MLIB_RUNE_H */
