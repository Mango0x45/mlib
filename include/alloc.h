#ifndef MLIB_ALLOC_H
#define MLIB_ALLOC_H

#include <stddef.h>

#include "_attrs.h"

#ifndef MLIB_ARENA_BLKSIZE
#	define MLIB_ARENA_BLKSIZE (8 * 1024)
#endif

struct _region {
	size_t len, cap;
	void *data;
	struct _region *next;
};

typedef struct {
	struct _region *_head;
	size_t _init;
} arena;

[[nodiscard, gnu::returns_nonnull]] void *bufalloc(void *, size_t, size_t);
[[nodiscard]] void *bufalloc_noterm(void *, size_t, size_t);

[[_mlib_pure, _mlib_inline]]
static inline arena
mkarena(size_t n)
{
	return (arena){._init = n ? n : MLIB_ARENA_BLKSIZE};
}

[[nodiscard, gnu::malloc, gnu::alloc_size(2, 3), gnu::alloc_align(4)]]
void *arena_alloc(arena *, size_t, size_t, size_t);

void arena_zero(arena *);
void arena_free(arena *);

#define arena_new(a, T, n) ((T *)arena_alloc((a), sizeof(T), (n), alignof(T)))

#endif /* !MLIB_ALLOC_H */
