#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "macros.h"

void
(usage)(const char *s, ...)
{
	ASSUME(s != nullptr);
	ASSUME(mlib_progname() != nullptr);

	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "Usage: %s %s\n", mlib_progname(), s);
	while ((s = va_arg(ap, char *)) != nullptr)
		fprintf(stderr, "       %s %s\n", mlib_progname(), s);

	va_end(ap);
}
