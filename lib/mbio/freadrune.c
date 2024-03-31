#include <macros.h>
#include <stdio.h>
#include <string.h>

#include "mbio.h"
#include "mbstring.h"

int
freadrune(rune *ch, u8_io_state *st, FILE *stream)
{
	size_t n, need;
	need = lengthof(st->_buf) - st->_fill;
	st->_fill += n = fread(st->_buf + st->_fill, 1, need, stream);
	if (n < need && ferror(stream))
		return -1;
	if (st->_fill == 0)
		return 0;

	int w = u8tor(ch, st->_buf);
	memmove(st->_buf, st->_buf + w, lengthof(st->_buf) - w);
	st->_fill -= w;
	return w;
}
