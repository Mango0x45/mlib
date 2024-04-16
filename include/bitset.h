#ifndef MLIB_BITSET_H
#define MLIB_BITSET_H

#include <limits.h>

#define _MLIB_BITSLOT(x) ((x) / CHAR_BIT)
#define _MLIB_BITMASK(x) (1 << ((x) % CHAR_BIT))

#define bitset(name, n) unsigned char name[(n + CHAR_BIT - 1) / CHAR_BIT]

#define CLRBIT(bs, x)  ((bs)[_MLIB_BITSLOT(x)] &= ~_MLIB_BITMASK(x))
#define SETBIT(bs, x)  ((bs)[_MLIB_BITSLOT(x)] |= _MLIB_BITMASK(x))
#define TOGLBIT(bs, x) ((bs)[_MLIB_BITSLOT(x)] ^= _MLIB_BITMASK(x))
#define TESTBIT(bs, x) ((bool)((bs)[_MLIB_BITSLOT(x)] & _MLIB_BITMASK(x)))

#endif /* !MLIB_BITSET_H */
