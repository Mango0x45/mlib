#include <stdarg.h>
#include <stdlib.h>

#include "errors.h"

void
cerr(int code, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarn(fmt, ap);
	va_end(ap);
	exit(code);
}
