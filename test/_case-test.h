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
#define FUNC     CONCAT(u8, CASETYPE)

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
	struct u8view sv = {line, strlen(line)};
	struct u8view before, after, flags;
	u8cut(&before, &sv, U";", 1);
	u8cut(&after,  &sv, U";", 1);
	u8cut(&flags,  &sv, U";", 1);

	enum caseflags cf = u8eq(flags, U8("ẞ"))  ? CF_ẞ
	                  : u8eq(flags, U8("AZ")) ? CF_LANG_AZ
	                  : u8eq(flags, U8("LT")) ? CF_LANG_LT
	                  : u8eq(flags, U8("NL")) ? CF_LANG_NL
	                                          : 0;
	char8_t *buf = bufalloc(nullptr, 1, after.len);
	size_t bufsz = FUNC(nullptr, 0, before, cf);
	if (bufsz != after.len) {
		warn("case %d: expected %s buffer size of %zu but got %zu",
		     id, STR(CASETYPE_VERB), after.len, bufsz);
		return false;
	}

	bufsz = FUNC(buf, bufsz, before, cf);
	if (bufsz != after.len) {
		warn("case %d: expected %scased length of %zu but got %zu",
		     id, STR(CASETYPE_VERB), after.len, bufsz);
		return false;
	}

	if (!memeq(buf, after.p, bufsz)) {
		warn("case %d: expected ‘%.*s’ but got ‘%.*s’",
		     id, SV_PRI_ARGS(after), (int)bufsz, buf);
		return false;
	}

	free(buf);
	return true;
}
