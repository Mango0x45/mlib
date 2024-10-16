#if !defined(NORMTYPE)
#	error "NORMTYPE must be defined"
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

#define TESTFILE "norm.in"

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
	arena_ctx_t ctx = {};
	allocator_t mem = init_arena_allocator(&ctx, nullptr);

	u8view_t column;
	u8view_t *columns = array_new(mem, typeof(*columns), 64);

	while (ucscut(&column, &sv, U";", 1) != MBEND) {
		char8_t *s = array_new(mem, typeof(*s), 64);

		rune _;
		u8view_t cp;
		do {
			rune ch;
			_ = ucscut(&cp, &column, U" ", 1);
			sscanf(cp.p, "%" SCNxRUNE, &ch);
			char8_t buf[U8_LEN_MAX];
			int w = rtoucs(buf, sizeof(buf), ch);
			array_extend(&s, buf, w);
		} while (_ != MBEND);

		array_push(&columns, ((u8view_t){s, array_len(s)}));
	}

	for (size_t i = 0; i < 5; i++) {
		size_t base;
		const char *nt = STR(NORMTYPE);
		if (streq(nt, "NF_NFC"))
			base = i < 3 ? 1 : 3;
		else if (streq(nt, "NF_NFD"))
			base = i < 3 ? 2 : 4;
		else if (streq(nt, "NF_NFKC"))
			base = 3;
		else if (streq(nt, "NF_NFKD"))
			base = 4;
		else
			err("invalid NORMTYPE ‘%s’", nt);

		u8view_t normd = {};
		normd.p = ucsnorm(&normd.len, columns[i], mem, NORMTYPE);
		if (!ucseq(columns[base], normd)) {
			warn("case %d: expected c%zu to be ‘%.*s’ but got ‘%.*s’", id,
			     i + 1, SV_PRI_ARGS(columns[base]), SV_PRI_ARGS(normd));
			rv = false;
			goto out;
		}
	}

out:
	deleteall(mem);
	return rv;
}
