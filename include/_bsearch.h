#include <stddef.h>

#include "macros.h"

#define _MLIB_DEFINE_BSEARCH(TYPE, TABLE, DEFAULT) \
	static TYPE mlib_lookup(rune ch) \
	{ \
		ptrdiff_t i, lo, hi; \
		lo = 0; \
		hi = lengthof(TABLE) - 1; \
		i = (lo + hi) / 2; \
		do { \
			if (ch < TABLE[i].lo) \
				hi = i - 1; \
			else if (ch > TABLE[i].hi) \
				lo = i + 1; \
			else \
				return TABLE[i].val; \
			i = (lo + hi) / 2; \
		} while (lo <= hi); \
		return DEFAULT; \
	}

#define _MLIB_DEFINE_BSEARCH_CONTAINS(TABLE) \
	static bool mlib_lookup_contains(rune ch) \
	{ \
		ptrdiff_t i, lo, hi; \
		lo = 0; \
		hi = lengthof(TABLE) - 1; \
		i = (lo + hi) / 2; \
		do { \
			if (ch < TABLE[i].lo) \
				hi = i - 1; \
			else if (ch > TABLE[i].hi) \
				lo = i + 1; \
			else \
				return true; \
			i = (lo + hi) / 2; \
		} while (lo <= hi); \
		return false; \
	}

#define _MLIB_DEFINE_BSEARCH_KV(TYPE, TABLE, DEFAULT) \
	static TYPE mlib_lookup_kv(rune ch) \
	{ \
		ptrdiff_t i, lo, hi; \
		lo = 0; \
		hi = lengthof(TABLE) - 1; \
		i = (lo + hi) / 2; \
		do { \
			if (ch < TABLE[i].k) \
				hi = i - 1; \
			else if (ch > TABLE[i].k) \
				lo = i + 1; \
			else \
				return TABLE[i].v; \
			i = (lo + hi) / 2; \
		} while (lo <= hi); \
		return DEFAULT; \
	}
