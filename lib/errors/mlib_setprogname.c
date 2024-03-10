#include <string.h>

#include "errors.h"

const char *__mlib_errors_progname;

void
mlib_setprogname(const char *s)
{
	const char *p = strrchr(s, '/');
	__mlib_errors_progname = p ? p + 1 : s;
}
