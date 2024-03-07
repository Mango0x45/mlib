#ifndef MLIB_BITSET_H
#define MLIB_BITSET_H

#include <limits.h>

#define __MLIB_BITSLOT(x)         ((x) / CHAR_BIT)
#define __MLIB_BITMASK(x)         (1 << ((x) % CHAR_BIT))
#define __MLIB_BITIMPL(bs, x, op) ((bs)[__MLIB_BITSLOT(x)] op __MLIB_BITMASK(x))

#define bitset(name, n) unsigned char name[(n + CHAR_BIT - 1) / CHAR_BIT]

#define BITCLR(bs, x)  __MLIB_BITIMPL(bs, x, &= ~)
#define BITSET(bs, x)  __MLIB_BITIMPL(bs, x, |=)
#define BITTOGL(bs, x) __MLIB_BITIMPL(bs, x, ^=)
#define BITTEST(bs, x) (bool)__MLIB_BITIMPL(bs, x, &)

#endif /* !MLIB_BITSET_H */
