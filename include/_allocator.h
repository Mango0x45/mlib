#ifndef MLIB__ALLOCATOR_H
#define MLIB__ALLOCATOR_H

#include <setjmp.h>
#include <stddef.h>

typedef enum {
	ALLOC_NEW,
	ALLOC_RESIZE,
	ALLOC_FREE,
	ALLOC_FREEALL,
} alloc_mode_t;

typedef struct allocator {
	void *(*alloc)(struct allocator mem, alloc_mode_t mode, void *ptr,
		ptrdiff_t oldnmemb, ptrdiff_t newnmemb, ptrdiff_t elemsz,
		ptrdiff_t align);
	jmp_buf *err;
	void    *ctx;
} allocator_t;

#endif /* !MLIB__ALLOCATOR_H */
