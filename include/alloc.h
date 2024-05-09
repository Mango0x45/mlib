#ifndef MLIB_ALLOC_H
#define MLIB_ALLOC_H

#include <stddef.h>

#include "_attrs.h"

#ifndef MLIB_ARENA_BLKSIZE
#	define MLIB_ARENA_BLKSIZE (8 * 1024)
#endif

struct _region {
	size_t len, cap;
	void *data, *last;
	struct _region *next;
};

typedef struct {
	struct _region *_head;
	size_t _init;
} arena;

/* Heap allocation functions */
[[nodiscard, gnu::returns_nonnull]] void *bufalloc(void *, size_t, size_t);
[[nodiscard]] void *bufalloc_noterm(void *, size_t, size_t);

[[_mlib_pure, _mlib_inline]]
static inline arena
mkarena(size_t n)
{
	return (arena){._init = n ? n : MLIB_ARENA_BLKSIZE};
}

/* Arena allocation functions */
[[nodiscard, gnu::malloc, gnu::alloc_size(2, 3), gnu::alloc_align(4)]]
void *arena_alloc(arena *, size_t, size_t, size_t);
[[nodiscard]]
void *arena_realloc(arena *, void *, size_t, size_t, size_t, size_t);
void arena_zero(arena *);
void arena_free(arena *);

/* Arena allocation macro wrappers */
#define arena_new(a, T, n) ((T *)arena_alloc((a), (n), sizeof(T), alignof(T)))
#define arena_resz(a, T, p, n)                                                 \
	((T *)arena_realloc((a), (p), (n), sizeof(T), alignof(T)))

[[nodiscard]] void *alloc_arena(void *, void *, size_t, size_t, size_t);
[[nodiscard]] void *alloc_heap(void *, void *, size_t, size_t, size_t);

#endif /* !MLIB_ALLOC_H */
