#include <stdarg.h>
#include <stdio.h>

#include "errors.h"

void
vwarnx(const char *fmt, va_list ap)
{
	fprintf(stderr, "%s: ", progname());
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
}
