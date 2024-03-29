#ifndef MLIB_ALLOC_H
#define MLIB_ALLOC_H

#include <stddef.h>

[[gnu::__returns_nonnull__]] void *bufalloc(void *, size_t, size_t);
void *bufalloc_noterm(void *, size_t, size_t);

#endif /* !MLIB_ALLOC_H */
