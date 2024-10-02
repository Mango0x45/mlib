#include <stdbit.h>
#include <stdlib.h>

#include <array.h>
#include <alloc.h>
#include <errors.h>

typedef struct {
	allocator_t inner;
	ptrdiff_t num_allocs, last_alloc_size;
	bool didfree;
} dbg_ctx_t;

static void *dbg_alloc(allocator_t, alloc_mode_t, void *, ptrdiff_t, ptrdiff_t,
	ptrdiff_t, ptrdiff_t);

int
main(int, char **argv)
{
	mlib_setprogname(argv[0]);

	dbg_ctx_t ctx = {.inner = init_heap_allocator(nullptr)};
	allocator_t mem = {
		.alloc = dbg_alloc,
		.ctx = &ctx,
	};

	int *xs = array_new(mem, int, 4);
	if (ctx.num_allocs != 1)
		err("ctx.num_allocs == %td\n", ctx.num_allocs);
	/* Integers don’t need padding.  It simplifies the test */
	if (ctx.last_alloc_size != sizeof(_mlib_arr_hdr_t) + sizeof(int) * 4)
		err("ctx.last_alloc_size == %td\n", ctx.last_alloc_size);
	
	xs[0] = 1; xs[1] = 2;
	xs[2] = 3; xs[3] = 4;
	array_hdr(xs)->len = 4;

	for (int i = 4; i < 69; i++) {
		array_push(&xs, i + 1);
		if (stdc_count_ones((unsigned)i) == 1) {
			/* Integers don’t need padding.  It simplifies the test */
			if ((size_t)ctx.last_alloc_size
			    != sizeof(_mlib_arr_hdr_t) + sizeof(int) * i * 2)
			{
				err("ctx.last_alloc_size == %td\n", ctx.last_alloc_size);
			}
		}
	}
	for (int i = 0; i < 69; i++) {
		if (xs[i] != i + 1)
			err("xs[%d] == %d", i, xs[i]);
	}

	if (array_len(xs) != 69)
		err("array_len(xs) == %td", array_len(xs));

	array_free(xs);
	if (!ctx.didfree)
		err("ctx.did_free == false");
	
	return EXIT_SUCCESS;
}

void *
dbg_alloc(allocator_t mem, alloc_mode_t mode, void *ptr, ptrdiff_t oldnmemb,
	ptrdiff_t newnmemb, ptrdiff_t elemsz, ptrdiff_t align)
{
	dbg_ctx_t *p = mem.ctx;
	switch (mode) {
	case ALLOC_NEW:
	case ALLOC_RESIZE:
		p->didfree = false;
		p->num_allocs++;
		p->last_alloc_size = newnmemb * elemsz;
		break;
	case ALLOC_FREE:
	case ALLOC_FREEALL:
		p->didfree = true;
	}
	return p->inner.alloc(p->inner, mode, ptr, oldnmemb, newnmemb, elemsz, align);
}
