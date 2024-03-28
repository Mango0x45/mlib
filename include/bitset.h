#ifndef MLIB_BITSET_H
#define MLIB_BITSET_H

#include <limits.h>

#define __MLIB_BITSLOT(x) ((x) / CHAR_BIT)
#define __MLIB_BITMASK(x) (1 << ((x) % CHAR_BIT))

#define bitset(name, n) unsigned char name[(n + CHAR_BIT - 1) / CHAR_BIT]

#define CLRBIT(bs, x)  ((bs)[__MLIB_BITSLOT(x)] &= ~__MLIB_BITMASK(x))
#define SETBIT(bs, x)  ((bs)[__MLIB_BITSLOT(x)] |= __MLIB_BITMASK(x))
#define TOGLBIT(bs, x) ((bs)[__MLIB_BITSLOT(x)] ^= __MLIB_BITMASK(x))
#define TESTBIT(bs, x) ((bool)((bs)[__MLIB_BITSLOT(x)] & __MLIB_BITMASK(x)))

#endif /* !MLIB_BITSET_H */
