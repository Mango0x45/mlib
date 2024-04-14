#ifndef MLIB_ERRORS_H
#define MLIB_ERRORS_H

#include <stdarg.h>

[[gnu::__format__(printf, 1, 2)]] void warn(const char *, ...);
void vwarn(const char *, va_list);

[[__noreturn__, gnu::__format__(printf, 1, 2)]] void err(const char *, ...);
[[__noreturn__, gnu::__format__(printf, 2, 3)]] void cerr(int, const char *,
                                                          ...);

extern const char *__mlib_errors_progname;

void mlib_setprogname(const char *);

[[gnu::__always_inline__]]
static inline const char *
mlib_progname(void)
{
	return __mlib_errors_progname;
}

#endif /* !MLIB_ERRORS_H */
