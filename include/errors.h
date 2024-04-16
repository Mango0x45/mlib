#ifndef MLIB_ERRORS_H
#define MLIB_ERRORS_H

#include <stdarg.h>

#include "_attrs.h"

[[gnu::format(printf, 1, 2)]] void warn(const char *, ...);
void vwarn(const char *, va_list);

[[noreturn, gnu::format(printf, 1, 2)]] void err(const char *, ...);
[[noreturn, gnu::format(printf, 2, 3)]] void cerr(int, const char *, ...);

extern const char *_mlib_errors_progname;

void mlib_setprogname(const char *);

[[_mlib_inline]]
static inline const char *
mlib_progname(void)
{
	return _mlib_errors_progname;
}

#endif /* !MLIB_ERRORS_H */
