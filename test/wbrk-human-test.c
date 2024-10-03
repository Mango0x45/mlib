#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <alloc.h>
#include <array.h>
#include <errors.h>
#include <macros.h>
#include <mbstring.h>
#include <unicode/string.h>

#define TESTFILE "wbrk-human.in"

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

		if (!test((u8view_t){line, nr}, id))
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
	u8view_t src;
	ucscut(&src, &sv, U";", 1);

	allocator_t mem = init_heap_allocator(nullptr);

	u8view_t w;
	u8view_t *ws = array_new(mem, typeof(*ws), 64);

	while (ucscut(&w, &sv, U"|", 1) != MBEND)
		array_push(ws, w);
	if (w.len > 0)
		array_push(ws, w);

	/* Assert the word count is correct */
	size_t n;
	/* TODO: Fix return type and remove cast */
	if ((ptrdiff_t)(n = ucswcnt_human(src)) != array_len(ws)) {
		warn("case %d: expected %tu words but got %zu", id, array_len(ws), n);
		return false;
	}

	/* Assert the individual words are correct */
	for (size_t i = 0; ucswnext_human(&w, &src) != 0; i++) {
		if (!ucseq(w, ws[i])) {
			warn("case %d: expected word %zu to be ‘%.*s’ but got ‘%.*s’", id,
			     i, SV_PRI_ARGS(ws[i]), SV_PRI_ARGS(w));
			return false;
		}
	}

	array_free(ws);
	return true;
}
