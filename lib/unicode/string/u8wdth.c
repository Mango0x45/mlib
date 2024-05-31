#include "mbstring.h"
#include "unicode/prop.h"
#include "unicode/string.h"

size_t
u8wdth(struct u8view sv, int ts)
{
	rune ch;
	size_t n = 0;

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
