#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"

void
vwarn(const char *fmt, va_list ap)
{
	int save = errno;
	fprintf(stderr, "%s: ", mlib_progname());
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, ": %s\n", strerror(save));
}
