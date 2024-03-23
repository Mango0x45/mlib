#include "macros.h"

#define __MLIB_DEFINE_BSEARCH(TYPE, TABLE, DEFAULT) \
	static TYPE mlib_lookup(rune ch) \
	{ \
		ptrdiff_t i, lo, hi; \
		if (ch >= lengthof(TABLE)) \
			return DEFAULT; \
		lo = 0; \
		hi = lengthof(TABLE) - 1; \
		i = (lo + hi) / 2; \
		do { \
			if (ch < TABLE[i].lo) \
				hi = i - 1; \
			else if (ch >= TABLE[i].hi) \
				lo = i + 1; \
			else \
				return TABLE[i].val; \
		} while (lo <= hi); \
		return DEFAULT; \
	}

// [[gnu::always_inline]] static TYPE
// lookup(rune ch)
// {
// 	ptrdiff_t i, lo, hi;
//
// #ifdef LATIN1_TABLE
// 	if (ch <= LATIN1_MAX)
// 		return LATIN1_TABLE[ch];
// #endif
// 	if (ch >= lengthof(TABLE))
// 		return DEFAULT;
//
// 	lo = 0;
// 	hi = lengthof(TABLE) - 1;
//
// #ifdef INITIAL_INDEX
// 	i = INITIAL_INDEX;
// #else
// 	i = (lo + hi) / 2;
// #endif
//
// 	do {
// 		if (ch < TABLE[i].LO)
// 			hi = i - 1;
// 		else if (ch > TABLE[i].HI)
// 			lo = i + 1;
// 		else
// #if HAS_VALUE
// 			return TABLE[i].val;
// #else
// 			return true;
// #endif
// 		i = (lo + hi) / 2;
// 	} while (lo <= hi);
//
// 	return DEFAULT;
// }
