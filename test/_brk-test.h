#if !defined(BRKTYPE) || !defined(BRKTYPE_LONG)
#	error "BRKTYPE and BRKTYPE_LONG must be defined"
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

	rune op;
	struct u8view sv_cpy = sv;
	while ((op = u8cut(nullptr, &sv_cpy, U"×÷", 2)) != MBEND) {
		rune ch;
		sscanf(sv_cpy.p, "%" SCNxRUNE, &ch);

		char8_t buf[U8_LEN_MAX];
		int w = rtou8(buf, sizeof(buf), ch);
		total += w;

		if (op == U'÷')
			DAPUSH(&items, (item){});
		DAEXTEND(&items.buf[items.len - 1], buf, w);
	}

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
		warn("case %d: expected %zu %s(s) but got %zu: ‘%s’", id, items.len,
		     STR(BRKTYPE_LONG), items_got, sv.p);
		return false;
	}

	/* Assert the individual items are correct */
	struct u8view it1, buf_cpy = buf;
	for (size_t i = 0; ITERFUNC(&it1, &buf_cpy); i++) {
		item it2 = items.buf[i];
		if (!u8eq(it1, ((struct u8view){it2.buf, it2.len}))) {
			warn("case %d: expected %s ‘%.*s’ but got ‘%.*s’", id,
			     STR(BRKTYPE_LONG), (int)it2.len, it2.buf, SV_PRI_ARGS(it1));
			return false;
		}
	}

	da_foreach (&items, wd)
		free(wd->buf);
	free(items.buf);
	free(p);

	return true;
}
