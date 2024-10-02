#ifndef MLIB_ALLOC_H
#define MLIB_ALLOC_H

#include "_allocator.h"
#include "_attrs.h"

typedef enum {
	ALLOC_OOM,
} alloc_err_t;

typedef struct arena_blk arena_blk_t;

typedef struct {
	ptrdiff_t blksz;
	struct arena_blk *_head;
} arena_ctx_t;

typedef struct {
	void     *buf;
	ptrdiff_t len;
} st_buf_t;

#define new(mem, T, n)                                                          \
	((typeof(T) *)((mem).alloc((mem),                                           \
		ALLOC_NEW,                                                              \
		nullptr,                                                                \
		0,                                                                      \
		(n),                                                                    \
		sizeof(T),                                                              \
		alignof(T))))
#define resz(mem, p, o, n)                                                      \
	((typeof(p))((mem).alloc((mem),                                             \
		ALLOC_RESIZE,                                                           \
		(p),                                                                    \
		(o),                                                                    \
		(n),                                                                    \
		sizeof(*(p)),                                                           \
		alignof(typeof(*(p))))))
#define delete(mem, p, sz)                                                      \
	(mem).alloc((mem),                                                          \
		ALLOC_FREE,                                                             \
		(p),                                                                    \
		(sz),                                                                   \
		0,                                                                      \
		sizeof(*(p)),                                                           \
		alignof(typeof(*p)))
#define deleteall(mem)                                                          \
	((mem).alloc((mem),                                                         \
		ALLOC_FREEALL,                                                          \
		nullptr,                                                                \
		0,                                                                      \
		0,                                                                      \
		0,                                                                      \
		0))

void *arena_alloc(allocator_t mem, alloc_mode_t mode, void *ptr,
				  ptrdiff_t oldnmemb, ptrdiff_t newnmemb, ptrdiff_t elemsz,
				  ptrdiff_t align);
void *heap_alloc(allocator_t mem, alloc_mode_t mode, void *ptr,
				 ptrdiff_t oldnmemb, ptrdiff_t newnmemb, ptrdiff_t elemsz,
				 ptrdiff_t align);
void *static_scratch_alloc(allocator_t mem, alloc_mode_t mode, void *ptr,
						   ptrdiff_t oldnmemb, ptrdiff_t newnmemb, ptrdiff_t elemsz,
						   ptrdiff_t align);

[[_mlib_inline]] static inline allocator_t
init_arena_allocator(arena_ctx_t *ctx, jmp_buf *jmp)
{
	return (allocator_t){
		.alloc = arena_alloc,	
		.err = jmp,
		.ctx = ctx,
	};
}

[[_mlib_inline]] static inline allocator_t
init_heap_allocator(jmp_buf *jmp)
{
	return (allocator_t){
		.alloc = heap_alloc,
		.err = jmp,
	};
}

[[_mlib_inline]] static inline allocator_t
init_static_scratch_allocator(st_buf_t *ctx, jmp_buf *jmp)
{
	return (allocator_t){
		.alloc = static_scratch_alloc,
		.err = jmp,
		.ctx = ctx,
	};
}

#endif /* !MLIB_ALLOC_H */
