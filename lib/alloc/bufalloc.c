#include "alloc.h"
#include "errors.h"

void *
bufalloc(void *p, size_t n, size_t m)
{
	if ((p = bufalloc_noterm(p, n, m)) == nullptr)
		err("%s:", __func__);
	return p;
}
