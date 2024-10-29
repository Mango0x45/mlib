#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

ptrdiff_t
u8wdth(u8view_t sv, ptrdiff_t n, int ts)
{
	rune ch;

	while (ucsnext(&ch, &sv) != 0) {
		if (ch == '\t')
			n += ts - n % ts;
		else {
			int w = uprop_get_wdth(ch);
			if (w > 0)
				n += w;
		}
	}

	return n;
}
