#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <alloc.h>
#include <errors.h>
#include <macros.h>
#include <mbstring.h>
#include <unicode/string.h>

#define TESTFILE "upper.in"

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
	struct u8view before, after, flags;
	before.p = line;
	after.p = strchr(line, ';') + 1;
	before.len = after.p - before.p - 1;
	flags.p = strchr(after.p, ';') + 1;
	after.len = flags.p - after.p - 1;
	flags.len = strlen(flags.p);

	enum caseflags cf = 0;
	if (u8eq(U8_ARGS(flags), U8_ARGS(U8("ẞ"))))
		cf |= CF_ẞ;
	else if (u8eq(U8_ARGS(flags), U8_ARGS(U8("AZ"))))
		cf |= CF_LANG_AZ;
	else if (u8eq(U8_ARGS(flags), U8_ARGS(U8("LT"))))
		cf |= CF_LANG_LT;

	char8_t *buf = bufalloc(nullptr, 1, after.len);
	size_t bufsz = u8upper(nullptr, 0, U8_ARGS(before), cf);
	if (bufsz != after.len) {
		warn("case %d: expected uppercased buffer size of %zu but got %zu "
		     "(flags=‘%.*s’)",
		     id, after.len, bufsz, U8_PRI_ARGS(flags));
		return false;
	}

	bufsz = u8upper(buf, bufsz, U8_ARGS(before), cf);
	if (bufsz != after.len) {
		warn("case %d: expected uppercased length of %zu but got %zu "
		     "(flags=‘%.*s’)",
		     id, after.len, bufsz, U8_PRI_ARGS(flags));
		return false;
	}

	if (!memeq(buf, after.p, bufsz)) {
		warn("case %d: expected ‘%.*s’ but got ‘%.*s’ (flags=‘%.*s’)", id,
		     U8_PRI_ARGS(after), (int)bufsz, buf, U8_PRI_ARGS(flags));
		return false;
	}

	free(buf);
	return true;
}
