#include <stdarg.h>
#include <stdlib.h>

#include "errors.h"

void
err(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarn(fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}
