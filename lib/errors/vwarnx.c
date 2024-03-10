#include <stdarg.h>
#include <stdio.h>

#include "errors.h"

void
vwarnx(const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", mlib_progname());
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
}
