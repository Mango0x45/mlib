#ifndef MLIB__ALLOC_FN_H
#define MLIB__ALLOC_FN_H

typedef void *(*alloc_fn)(void *ctx, void *ptr, size_t old, size_t new,
                          size_t align);

#endif /* !MLIB__ALLOC_FN_H */
