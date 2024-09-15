#ifdef __STDC_NO_ATOMICS__
#	error "Atomics aren’t supported"
#endif

#define _GNU_SOURCE
#include <errno.h>
#include <glob.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if __has_include(<features.h>)
#	include <features.h>
#endif

#include "cbs.h"

#define LIBNAME "libmlib"
#define flagset(o) (flags & UINT32_C(1)<<(o)-'a')

[[noreturn, gnu::format(printf, 1, 2)]]
static void err(const char *, ...);
static void cc(void *);

static atomic_int rv;
static uint32_t flags;
static const char *argv0;

static char *cflags_req[] = {
	"-Wall",
	"-Wextra",
	"-Wpedantic",
	"-Wvla",
	"-Wno-attributes",
	"-Wno-pointer-sign",
	"-Wno-parentheses",
	"-Iinclude",
	"-pipe",
	"-std=c23",
#ifdef __GLIBC__
	"-D_GNU_SOURCE",
#endif
};

static char *cflags_dbg[] = {
	"-fsanitize=address,undefined",
	"-ggdb3",
	"-O0",
};

static char *cflags_rls[] = {
	"-DNDEBUG",
	"-flto",
	"-march=native",
	"-mtune=native",
	"-O3",
};

int
main(int argc, char **argv)
{
	int opt, procs = -1;

	cbsinit(argc, argv);
	rebuild();

	argv0 = basename(argv[0]);

	while ((opt = getopt(argc, argv, "afj:rs")) != -1) {
		switch (opt) {
		case '?':
			fprintf(stderr,
				"Usage: %s [-j procs] [-afrs]\n"
				"       %s clean | gen | test\n",
				*argv, *argv);
			exit(EXIT_FAILURE);
		case 'j':
			procs = atoi(optarg);
			break;
		default:
			flags |= UINT32_C(1) << opt-'a';
		}
	}

	if (!flagset('a') && !flagset('s'))
		flags |= 1 << 'a'-'a';

	argc -= optind;
	argv += optind;

	if (argc >= 1) {
		return EXIT_SUCCESS;
	}

	glob_t g;
	if (glob("lib/*/*.c", 0, nullptr, &g))
		err("glob:");
	if (glob("lib/unicode/*/*.c", GLOB_APPEND, nullptr, &g))
		err("glob:");

	if (procs == -1 && (procs = nproc()) == -1) {
		if (errno != 0)
			err("nproc:");
		procs = 1;
	}

	tpool tp;
	tpinit(&tp, procs);
	for (size_t i = 0; i < g.gl_pathc; i++)
		tpenq(&tp, cc, g.gl_pathv[i], nullptr);
	tpwait(&tp);
	tpfree(&tp);

	if (rv != EXIT_SUCCESS)
		exit(rv);

	for (size_t i = 0; i < g.gl_pathc; i++)
		g.gl_pathv[i][strlen(g.gl_pathv[i]) - 1] = 'o';

	if (flagset('a') && (flagset('f') || foutdated(LIBNAME ".a", g.gl_pathv, g.gl_pathc)))
	{
		struct strs cmd = {};
		strspushl(&cmd, "ar", "rcs", LIBNAME ".a");
		strspush(&cmd, g.gl_pathv, g.gl_pathc);
		cmdput(cmd);
		if (cmdexec(cmd) != EXIT_FAILURE) {
			rv = EXIT_FAILURE;
			goto out;
		}
		strsfree(&cmd);
	}

	if (flagset('s') && (flagset('f') || foutdated(LIBNAME ".so", g.gl_pathv, g.gl_pathc)))
	{
		struct strs cmd = {};
		strspushenvl(&cmd, "CC", "cc");
		strspushl(&cmd, "-shared", "-o", LIBNAME ".so");
		strspush(&cmd, g.gl_pathv, g.gl_pathc);
		cmdput(cmd);
		if (cmdexec(cmd) != EXIT_FAILURE)
			rv = EXIT_FAILURE;
		strsfree(&cmd);
	}

out:
	globfree(&g);
	return rv;
}

void
cc(void *_arg)
{
	char *arg = _arg;
	char *obj = swpext(arg, "o");

	if (!flagset('f') && !foutdatedl(obj, arg))
		goto out;

	struct strs cmd = {};
	strspushenvl(&cmd, "CC", "cc");
	strspush(&cmd, cflags_req, lengthof(cflags_req));
	if (flagset('r'))
		strspushenv(&cmd, "CFLAGS", cflags_rls, lengthof(cflags_rls));
	else
		strspushenv(&cmd, "CFLAGS", cflags_dbg, lengthof(cflags_dbg));
	strspushl(&cmd, "-fPIC", "-o", obj, "-c", arg);
	cmdput(cmd);

	if (cmdexec(cmd) != EXIT_SUCCESS)
		rv = EXIT_FAILURE;

	strsfree(&cmd);
out:
	free(obj);
}

void
err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int save = errno;
	flockfile(stderr);
	fprintf(stderr, "%s: ", argv0);
	vfprintf(stderr, fmt, ap);
	if (fmt[strlen(fmt) - 1] == ':')
		fprintf(stderr, " %s", strerror(save));
	fputc('\n', stderr);
	funlockfile(stderr);
	va_end(ap);
	exit(EXIT_FAILURE);
}
