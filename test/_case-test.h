#if !defined(CASETYPE) || !defined(CASETYPE_VERB)
#	error "CASETYPE and CASETYPE_VERB must be defined"
#endif

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <alloc.h>
#include <errors.h>
#include <macros.h>
#include <mbstring.h>
#include <unicode/string.h>

#define TESTFILE STR(CASETYPE) ".in"
#define FUNC     CONCAT(ucs, CASETYPE)

static bool test(const char8_t *, int);

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

		if (!test(line, id))
			rv = EXIT_FAILURE;
	}
	if (ferror(fp))
		err("getline: %s:", TESTFILE);

	free(line);
	fclose(fp);
	return rv;
}

bool
test(const char8_t *line, int id)
{
	u8view_t mapped, sv = {line, strlen(line)};
	u8view_t before, after, flags;
	ucscut(&before, &sv, U";", 1);
	ucscut(&after,  &sv, U";", 1);
	ucscut(&flags,  &sv, U";", 1);

	enum caseflags cf = ucseq(flags, U8("ẞ"))  ? CF_ẞ
	                  : ucseq(flags, U8("AZ")) ? CF_LANG_AZ
	                  : ucseq(flags, U8("LT")) ? CF_LANG_LT
	                  : ucseq(flags, U8("NL")) ? CF_LANG_NL
	                                          : 0;

	arena a = mkarena(0);
	mapped.p = FUNC(&mapped.len, before, cf, alloc_arena, &((struct arena_ctx){
		.a = &a,
	}));

	if (!ucseq(mapped, after)) {
		warn("case %d: expected ‘%.*s’ but got ‘%.*s’", id, SV_PRI_ARGS(after),
		     SV_PRI_ARGS(mapped));
		arena_free(&a);
		return false;
	}

	arena_free(&a);
	return true;
}
