#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "mbio.h"
#include "mbstring.h"
#include "rune.h"

#define RETURN_INVAL \
	do { \
		*ch = RUNE_ERROR; \
		return 3; \
	} while (false)

int
freadrune(rune *ch, FILE *stream)
{
	int c, n = 0;
	char8_t buf[U8_LEN_MAX];

	if ((c = fgetc(stream)) == EOF)
		goto eof_or_err;

	buf[0] = (char8_t)c;
	n = u8byte1(c) ? 0 : u8byte2(c) ? 1 : u8byte3(c) ? 2 : u8byte4(c) ? 3 : 4;

	if (n == 0) {
		*ch = buf[0];
		return 1;
	} else if (n == 4)
		RETURN_INVAL;

	for (int i = 0; i < n; i++) {
		if ((c = fgetc(stream)) == EOF)
			goto eof_or_err;
		if (!u8bytec(c))
			RETURN_INVAL;
		buf[i + 1] = c;
	}

	return u8tor(ch, buf);

eof_or_err:
	if (ferror(stream))
		return MBERR;
	if (n == 0)
		return MBEOF;
	RETURN_INVAL;
}
