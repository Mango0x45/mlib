#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "mbio.h"
#include "mbstring.h"
#include "rune.h"

/* Width in bytes of U+FFFD REPLACEMENT CHARACTER */
constexpr int ERR_WIDTH = 3;

int
u8fgetr(rune *ch, FILE *stream)
{
	int c, n = 0;
	char8_t buf[U8_LEN_MAX];

	if ((c = fgetc(stream)) == EOF)
		goto eof;

	n = u8byte1(c) ? 0 : u8byte2(c) ? 1 : u8byte3(c) ? 2 : u8byte4(c) ? 3 : -1;
	if (n == -1)
		goto err;

	buf[0] = (char8_t)c;
	for (int i = 0; i < n; i++) {
		/* If fgetc() returns EOF we must have malformed UTF-8 unless the EOF
		   was the result of a reading error. */
		if ((c = fgetc(stream)) == EOF || !u8bytec(c)) {
			if (ferror(stream))
				goto eof;
			goto err;
		}
		buf[i + 1] = c;
	}

	return u8tor(ch, buf);
eof:
	*ch = MBEOF;
	return 0;
err:
	*ch = RUNE_ERROR;
	return ERR_WIDTH;
}
