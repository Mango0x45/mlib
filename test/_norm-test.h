#if !defined(NORMTYPE)
#	error "NORMTYPE must be defined"
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

#define TESTFILE "norm.in"

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
	bool rv = true;
	arena a = mkarena(0);
	struct arena_ctx ctx = {.a = &a};

	dynarr(struct u8view) columns = {
		.alloc = alloc_arena,
		.ctx = &ctx,
	};

	struct u8view column;
	while (ucscut(&column, &sv, U";", 1) != MBEND) {
		dynarr(char8_t) s = {
			.alloc = alloc_arena,
			.ctx = &ctx,
		};

		rune _;
		struct u8view cp;
		do {
			rune ch;
			_ = ucscut(&cp, &column, U" ", 1);
			sscanf(cp.p, "%" SCNxRUNE, &ch);
			char8_t buf[U8_LEN_MAX];
			int w = rtoucs(buf, sizeof(buf), ch);
			DAEXTEND(&s, buf, w);
		} while (_ != MBEND);

		DAPUSH(&columns, ((struct u8view){s.buf, s.len}));
	}

	for (size_t i = 0; i < 5; i++) {
		size_t base;
		const char *nt = STR(NORMTYPE);
		if (streq(nt, "NT_NFC"))
			base = i < 3 ? 1 : 3;
		else if (streq(nt, "NT_NFD"))
			base = i < 3 ? 2 : 4;
		else if (streq(nt, "NT_NFKC"))
			base = 3;
		else if (streq(nt, "NT_NFKD"))
			base = 4;
		else
			err("invalid NORMTYPE ‘%s’", nt);

		struct u8view normd = {};
		normd.p =
			ucsnorm(&normd.len, columns.buf[i], alloc_arena, &ctx, NORMTYPE);
		if (!ucseq(columns.buf[base], normd)) {
			warn("case %d: expected c%zu to be ‘%.*s’ but got ‘%.*s’", id,
			     i + 1, SV_PRI_ARGS(columns.buf[base]), SV_PRI_ARGS(normd));
			rv = false;
			goto out;
		}
	}

out:
	arena_free(&a);
	return rv;
}
