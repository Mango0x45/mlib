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

#define TESTFILE "gnext.in"

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

	typedef dynarr(char8_t) graph;
	dynarr(graph) graphs = {};

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
			DAPUSH(&graphs, (graph){});
		DAEXTEND(&graphs.buf[graphs.len - 1], buf, w);
	} while (n > 0);

	size_t off = 0;
	char8_t *buf = bufalloc(nullptr, 1, total);
	da_foreach (&graphs, g) {
		memcpy(buf + off, g->buf, g->len);
		off += g->len;
	}

	/* Assert the grapheme count is correct */
	size_t graphs_got = u8gcnt(buf, total);
	if (graphs_got != graphs.len) {
		warn("case %d: expected %zu grapheme(s) but got %zu: ‘%s’", id,
		     graphs.len, graphs_got, line);
		return false;
	}

	/* Assert the individual graphemes are correct */
	struct u8view g;
	const char8_t *buf_cpy = buf;
	for (size_t i = 0; u8gnext(&g, &buf_cpy, &total); i++) {
		graph g2 = graphs.buf[i];
		if (!u8eq(g.p, g.len, g2.buf, g2.len)) {
			warn("case %d: expected grapheme ‘%.*s’ but got ‘%.*s’", id,
			     (int)g2.len, g2.buf, (int)g.len, g.p);
			return false;
		}
	}

	da_foreach (&graphs, wd)
		free(wd->buf);
	free(graphs.buf);
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
