#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"

void
vwarn(const char *fmt, va_list ap)
{
	int save = errno;
	flockfile(stderr);
	fprintf(stderr, "%s: ", mlib_progname());
	vfprintf(stderr, fmt, ap);
	if (fmt[strlen(fmt) - 1] == ':')
		fprintf(stderr, " %s", strerror(save));
	fputc('\n', stderr);
	funlockfile(stderr);
}
