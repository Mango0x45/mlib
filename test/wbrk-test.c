#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"
#include "dynarr.h"
#include "errors.h"
#include "macros.h"
#include "mbstring.h"
#include "rune.h"
#include "unicode/string.h"

#define TESTFILE "wnext.in"

static bool test(const char8_t *, size_t, int);
static int hexdigits(rune);

int
main(int, char **argv)
{
	int rv;
	size_t n;
	ssize_t nr;
	char *line;
	FILE *fp;

	rv = EXIT_SUCCESS;
	line = nullptr;
	mlib_setprogname(argv[0]);

	if ((fp = fopen(TESTFILE, "r")) == nullptr)
		err("fopen: %s:", TESTFILE);

	for (int id = 1; (nr = getline(&line, &n, fp)) > 0; id++) {
		if (line[nr - 1] == '\n')
			line[--nr] = '\0';

		if (!test(line, (size_t)nr, id)) {
			rv = EXIT_FAILURE;
			break;
		}
	}
	if (ferror(fp))
		err("getline: %s:", TESTFILE);

	free(line);
	fclose(fp);
	return rv;
}

bool
test(const char8_t *line, size_t n, int id)
{
	size_t total = 0;
	const char8_t *line2 = line;

	typedef dynarr(char8_t) word;
	dynarr(word) words = {};

	do {
		rune op, ch;

		u8next(&op, &line2, &n);
		sscanf(line2, "%" SCNxRUNE, &ch);
		int off = hexdigits(ch);
		off = MAX(4, off);
		line2 += off, n -= off;

		char8_t buf[U8_LEN_MAX] = {};
		int w = rtou8(buf, sizeof(buf), ch);
		total += w;

		if (op == U'÷')
			DAPUSH(&words, (word){});
		DAEXTEND(&words.buf[words.len - 1], buf, w);
	} while (n > 0);

	size_t off = 0;
	char8_t *buf = bufalloc(nullptr, 1, total);
	da_foreach (&words, wd) {
		memcpy(buf + off, wd->buf, wd->len);
		off += wd->len;
	}

	/* Assert the word count is correct */
	size_t words_got = u8wcnt(buf, total);
	if (words_got != words.len) {
		warn("case %d: expected %zu word(s) but got %zu: ‘%s’", id, words.len,
		     words_got, line);
		return false;
	}

	/* Assert the individual words are correct */
	struct u8view wd;
	const char8_t *buf_cpy = buf;
	for (size_t i = 0; u8wnext(&wd, &buf_cpy, &total); i++) {
		word wd2 = words.buf[i];
		if (!u8eq(wd.p, wd.len, wd2.buf, wd2.len)) {
			warn("case %d: expected word ‘%.*s’ but got ‘%.*s’", id,
			     (int)wd2.len, wd2.buf, (int)wd.len, wd.p);
			return false;
		}
	}

	da_foreach (&words, wd)
		free(wd->buf);
	free(words.buf);
	free(buf);

	return true;
}

int
hexdigits(rune ch)
{
	int n = 0;
	do {
		ch /= 16;
		n++;
	} while (ch != 0);
	return n;
}
