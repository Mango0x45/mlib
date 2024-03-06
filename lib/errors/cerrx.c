#include <stdarg.h>
#include <stdlib.h>

#include "errors.h"

void
cerrx(int code, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vwarnx(fmt, ap);
	va_end(ap);
	exit(code);
}
