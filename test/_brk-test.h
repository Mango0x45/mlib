#ifndef BRKTYPE
#	error "BRKTYPE is not defined!"
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <alloc.h>
#include <dynarr.h>
#include <errors.h>
#include <macros.h>
#include <mbstring.h>
#include <rune.h>
#include <unicode/string.h>

#define TESTFILE STR(BRKTYPE) "brk.in"
#define ITERFUNC CONCAT(CONCAT(u8, BRKTYPE), next)
#define CNTFUNC  CONCAT(CONCAT(u8, BRKTYPE), cnt)

static bool test(struct u8view, int);
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

		if (!test((struct u8view){line, (size_t)nr}, id))
			rv = EXIT_FAILURE;
	}
	if (ferror(fp))
		err("getline: %s:", TESTFILE);

	free(line);
	fclose(fp);
	return rv;
}

bool
test(struct u8view sv, int id)
{
	size_t total = 0;

	typedef dynarr(char8_t) item;
	dynarr(item) items = {};
	struct u8view sv_cpy = sv;

	do {
		rune op, ch;

		u8next(&op, &sv_cpy);
		sscanf(sv_cpy.p, "%" SCNxRUNE, &ch);
		int off = hexdigits(ch);
		off = MAX(4, off);
		VSHFT(&sv_cpy, off);

		char8_t buf[U8_LEN_MAX] = {};
		int w = rtou8(buf, sizeof(buf), ch);
		total += w;

		if (op == U'÷')
			DAPUSH(&items, (item){});
		DAEXTEND(&items.buf[items.len - 1], buf, w);
	} while (sv_cpy.len > 0);

	size_t off = 0;
	char8_t *p = bufalloc(nullptr, 1, total);
	da_foreach (&items, g) {
		memcpy(p + off, g->buf, g->len);
		off += g->len;
	}

	struct u8view buf = {p, total};

	/* Assert the item count is correct */
	size_t items_got = CNTFUNC(buf);
	if (items_got != items.len) {
		warn("case %d: expected %zu items(s) but got %zu: ‘%s’", id, items.len,
		     items_got, sv.p);
		return false;
	}

	/* Assert the individual items are correct */
	struct u8view it1, buf_cpy = buf;
	for (size_t i = 0; ITERFUNC(&it1, &buf_cpy); i++) {
		item it2 = items.buf[i];
		if (!u8eq(it1, ((struct u8view){it2.buf, it2.len}))) {
			warn("case %d: expected item ‘%.*s’ but got ‘%.*s’", id,
			     (int)it2.len, it2.buf, SV_PRI_ARGS(it1));
			return false;
		}
	}

	da_foreach (&items, wd)
		free(wd->buf);
	free(items.buf);
	free(p);

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
