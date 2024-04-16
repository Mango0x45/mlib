#define _GNU_SOURCE
#include <errno.h>
#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CBS_PTHREAD
#include "cbs.h"

#define CC         "gcc"
#define CFLAGS_ALL WARNINGS, "-pipe", "-std=c23", "-Iinclude"
#define CFLAGS_DBG CFLAGS_ALL, "-g", "-ggdb3", "-Og"
#ifdef __APPLE__
#	define CFLAGS_RLS CFLAGS_ALL, "-O3", "-flto", "-DNDEBUG"
#else
#	define CFLAGS_RLS \
		CFLAGS_ALL, "-O3", "-flto", "-DNDEBUG", "-march=native", "-mtune=native"
#endif
#define LIBNAME "libmlib"
#define WARNINGS \
	"-Wall", "-Wextra", "-Wpedantic", "-Werror", "-Wno-attributes", "-Wvla", \
		"-Wno-pointer-sign"

#define CMDRC(c) \
	do { \
		int ec; \
		if ((ec = cmdexec(c)) != EXIT_SUCCESS) \
			diex("%s terminated with exit-code %d", *(c)._argv, ec); \
		cmdclr(&(c)); \
	} while (false)

#define flagset(o)  (flags & (1 << ((o) - 'a')))
#define streq(x, y) (!strcmp(x, y))

static int globerr(const char *, int);
static void work(void *);

static unsigned long flags;

int
main(int argc, char **argv)
{
	int opt, procs = -1;

	cbsinit(argc, argv);
	rebuild();

	while ((opt = getopt(argc, argv, "fj:r")) != -1) {
		switch (opt) {
		case '?':
			fprintf(stderr, "Usage: %s [-j procs] [-fr]\n", *argv);
			exit(EXIT_FAILURE);
		case 'j':
			procs = atoi(optarg);
			break;
		default:
			flags |= 1 << (opt - 'a');
		}
	}

	argc -= optind;
	argv += optind;

	if (argc >= 1) {
		if (!streq(*argv, "clean")) {
			diex("invalid subcommand — ‘%s’", *argv);
			exit(EXIT_FAILURE);
		}
		cmd_t c = {};
		cmdadd(&c, "find", ".", "(", "-name", "*.[ao]", "-or", "-name", "*.so",
		       ")", "-delete");
		cmdput(c);
		CMDRC(c);
	} else {
		cmd_t c = {};
		glob_t g;
		tpool_t tp;

		if (glob("lib/*/*.c", 0, globerr, &g))
			die("glob");
		if (glob("lib/unicode/*/*.c", GLOB_APPEND, globerr, &g))
			die("glob");

		if (procs == -1 && (procs = nproc()) == -1) {
			if (errno)
				die("nproc");
			procs = 8;
		}

		tpinit(&tp, procs);
		for (size_t i = 0; i < g.gl_pathc; i++)
			tpenq(&tp, work, g.gl_pathv[i], nullptr);
		tpwait(&tp);
		tpfree(&tp);

		for (size_t i = 0; i < g.gl_pathc; i++)
			g.gl_pathv[i][strlen(g.gl_pathv[i]) - 1] = 'o';

		if (flagset('f')
		    || foutdatedv(LIBNAME ".a", (const char **)g.gl_pathv, g.gl_pathc))
		{
			cmdadd(&c, "ar", "rcs", LIBNAME ".a");
			cmdaddv(&c, g.gl_pathv, g.gl_pathc);
			fprintf(stderr, "AR\t%s\n", LIBNAME ".a");
			CMDRC(c);
		}

		if (flagset('f')
		    || foutdatedv(LIBNAME ".so", (const char **)g.gl_pathv, g.gl_pathc))
		{
			struct strv sv = {};
			env_or_default(&sv, "CC", CC);
			cmdaddv(&c, sv.buf, sv.len);
			cmdadd(&c, "-shared", "-o", LIBNAME ".so");
			cmdaddv(&c, g.gl_pathv, g.gl_pathc);
			fprintf(stderr, "CC\t%s\n", LIBNAME ".so");
			CMDRC(c);
		}

		globfree(&g);
	}

	return EXIT_SUCCESS;
}

void
work(void *p)
{
	char *dst, *src = p;
	cmd_t c = {};
	struct strv sv = {};

	if (!(dst = strdup(src)))
		die("strdup");
	dst[strlen(dst) - 1] = 'o';

	if (flagset('f') || foutdated(dst, src)) {
		env_or_default(&sv, "CC", CC);
		if (flagset('r'))
			env_or_default(&sv, "CFLAGS", CFLAGS_RLS);
		else
			env_or_default(&sv, "CFLAGS", CFLAGS_DBG);
		cmdaddv(&c, sv.buf, sv.len);
		cmdadd(&c, "-Iinclude", "-fPIC", "-o", dst, "-c", src);
		fprintf(stderr, "CC\t%s\n", dst);
		CMDRC(c);
	}

	free(dst);
}

int
globerr(const char *s, int e)
{
	errno = e;
	die("glob: %s", s);
}
