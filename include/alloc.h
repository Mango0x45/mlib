#ifndef MLIB_ALLOC_H
#define MLIB_ALLOC_H

#include <stddef.h>

[[gnu::returns_nonnull]] void *bufalloc(void *, size_t, size_t);
void *bufalloc_noterm(void *, size_t, size_t);

#endif /* !MLIB_ALLOC_H */
