#if !defined(BRKTYPE) || !defined(BRKTYPE_LONG)
#	error "BRKTYPE and BRKTYPE_LONG must be defined"
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <alloc.h>
#include <array.h>
#include <errors.h>
#include <macros.h>
#include <mbstring.h>
#include <rune.h>
#include <unicode/string.h>

#define TESTFILE STR(BRKTYPE) "brk.in"
#define ITERFUNC CONCAT(CONCAT(ucs, BRKTYPE), next)
#define CNTFUNC  CONCAT(CONCAT(ucs, BRKTYPE), cnt)

static bool test(u8view_t, int);

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

		if (!test((u8view_t){line, (size_t)nr}, id))
			rv = EXIT_FAILURE;
	}
	if (ferror(fp))
		err("getline: %s:", TESTFILE);

	free(line);
	fclose(fp);
	return rv;
}

bool
test(u8view_t sv, int id)
{
	bool rv = true;
	size_t total = 0;

	arena_ctx_t ctx = {};
	allocator_t mem = init_arena_allocator(&ctx, nullptr);

	char8_t **items = array_new(mem, typeof(*items), 64);

	rune op;
	u8view_t sv_cpy = sv;
	while ((op = ucscut(nullptr, &sv_cpy, U"×÷", 2)) != MBEND) {
		rune ch;
		sscanf(sv_cpy.p, "%" SCNxRUNE, &ch);

		char8_t buf[U8_LEN_MAX];
		int w = rtoucs(buf, sizeof(buf), ch);
		total += w;

		if (op == U'÷')
			array_push(&items, array_new(mem, char8_t, 64));
		array_extend(items[array_len(items) - 1], buf, w);
	}

	size_t off = 0;
	char8_t *p = malloc(total);
	if (p == nullptr)
		err("malloc:");
	for (ptrdiff_t i = 0; i < array_len(items); i++) {
		char8_t *g = items[i];
		memcpy(p + off, g, array_len(g));
		off += array_len(g);
	}

	u8view_t buf = {p, total};

	/* Assert the item count is correct */
	ptrdiff_t items_got = CNTFUNC(buf);
	if (items_got != array_len(items)) {
		warn("case %d: expected %zu %s(s) but got %zu: ‘%s’", id, array_len(items),
		     STR(BRKTYPE_LONG), items_got, sv.p);
		rv = false;
		goto out;
	}

	/* Assert the individual items are correct */
	u8view_t it1, buf_cpy = buf;
	for (size_t i = 0; ITERFUNC(&it1, &buf_cpy); i++) {
		char8_t *it2 = items[i];
		if (!ucseq(it1, ((u8view_t){it2, array_len(it2)}))) {
			warn("case %d: expected %s ‘%.*s’ but got ‘%.*s’", id,
			     STR(BRKTYPE_LONG), (int)array_len(it2), it2, SV_PRI_ARGS(it1));
			rv = false;
			goto out;
		}
	}

out:
	deleteall(mem);
	free(p);
	return rv;
}
