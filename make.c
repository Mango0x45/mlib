#define _GNU_SOURCE
#include <errno.h>
#if __has_include(<features.h>)
#	include <features.h>
#endif
#include <glob.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CBS_PTHREAD
#include "cbs.h"

#define CC      "cc"
#define LIBNAME "libmlib"

#define CFLAGS_ALL WARNINGS, "-pipe", "-std=c23", "-Iinclude" GLIB_EXTRAS
#define CFLAGS_DBG "-g", "-ggdb3", "-O0", "-fsanitize=address,undefined"
#define CFLAGS_RLS "-O3", "-flto", "-DNDEBUG" NOT_APPLE_EXTRAS

#define WARNINGS                                                               \
	"-Wall", "-Wextra", "-Wpedantic", "-Werror", "-Wno-attributes", "-Wvla",   \
		"-Wno-pointer-sign", "-Wno-parentheses"

#ifdef __GLIBC__
#	define GLIB_EXTRAS , "-D_GNU_SOURCE"
#else
#	define GLIB_EXTRAS
#endif

#ifndef __APPLE__
#	define NOT_APPLE_EXTRAS , "-march=native", "-mtune=native"
#else
#	define NOT_APPLE_EXTRAS
#endif

#define CMDRC(c)                                                               \
	do {                                                                       \
		int ec;                                                                \
		if ((ec = cmdexec(c)) != EXIT_SUCCESS)                                 \
			diex("%s terminated with exit-code %d", *(c)._argv, ec);           \
		cmdclr(&(c));                                                          \
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

	while ((opt = getopt(argc, argv, "afj:prs")) != -1) {
		switch (opt) {
		case '?':
			fprintf(stderr,
			        "Usage: %s [-j procs] [-afprs]\n"
			        "       %s clean | gen | test\n",
			        *argv, *argv);
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
		cmd_t c = {};
		if (streq(*argv, "clean")) {
			cmdadd(&c, "find", ".", "(", "-name", "*.[ao]", "-or", "-name",
			       "*.so", ")", "-delete");
		} else if (streq(*argv, "gen")) {
			cmdadd(&c, "find", "gen", "-mindepth", "2", "-type", "f",
			       "-executable", "-not", "(", "-name", "scale", "-or", "-name",
			       "bool-props.py", ")", "-exec", "{}", ";");
		} else if (streq(*argv, "test"))
			cmdadd(&c, "./test/run-tests");
		else if (streq(*argv, "manstall"))
			diex("TODO: not implemented");
		else
			diex("invalid subcommand — ‘%s’", *argv);
		cmdput(c);
		CMDRC(c);
	} else {
		if (!flagset('a') && !flagset('s'))
			flags |= 1 << ('a' - 'a');

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

		if (flagset('a')
		    && (flagset('f')
		        || foutdatedv(LIBNAME ".a", (const char **)g.gl_pathv,
		                      g.gl_pathc)))
		{
			cmdadd(&c, "ar", "rcs", LIBNAME ".a");
			cmdaddv(&c, g.gl_pathv, g.gl_pathc);
			if (flagset('p'))
				cmdput(c);
			else
				fprintf(stderr, "AR\t%s\n", LIBNAME ".a");
			CMDRC(c);
		}

		if (flagset('s')
		    && (flagset('f')
		        || foutdatedv(LIBNAME ".so", (const char **)g.gl_pathv,
		                      g.gl_pathc)))
		{
			struct strv sv = {};
			env_or_default(&sv, "CC", CC);
			cmdaddv(&c, sv.buf, sv.len);
			cmdadd(&c, "-shared", "-o", LIBNAME ".so");
			cmdaddv(&c, g.gl_pathv, g.gl_pathc);
			if (flagset('p'))
				cmdput(c);
			else
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
		cmdadd(&c, CFLAGS_ALL, "-fPIC", "-o", dst, "-c", src);
		if (flagset('p'))
			cmdput(c);
		else
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
