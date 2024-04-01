#include "__bsearch.h"
#include "rune.h"
#include "unicode/__gc.h"
#include "unicode/prop.h"

__MLIB_DEFINE_BSEARCH(enum uprop_gc, __mlib_gc_lt, GC_CN)

enum uprop_gc
uprop_get_gc(rune ch)
{
	return ch <= LATIN1_MAX ? __mlib_gc_lat1_lt[ch] : mlib_lookup(ch);
}
