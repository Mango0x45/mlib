#ifndef MLIB_ERRORS_H
#define MLIB_ERRORS_H

#include <stdarg.h>

[[gnu::format(printf, 1, 2)]] void warn(const char *, ...);
[[gnu::format(printf, 1, 2)]] void warnx(const char *, ...);
void vwarn(const char *, va_list);
void vwarnx(const char *, va_list);

[[noreturn, gnu::format(printf, 1, 2)]] void err(const char *, ...);
[[noreturn, gnu::format(printf, 1, 2)]] void errx(const char *, ...);
[[noreturn, gnu::format(printf, 2, 3)]] void cerr(int, const char *, ...);
[[noreturn, gnu::format(printf, 2, 3)]] void cerrx(int, const char *, ...);

extern const char *__mlib_errors_progname;

void mlib_setprogname(const char *);

[[gnu::always_inline]]
static inline const char *
mlib_progname(void)
{
	return __mlib_errors_progname;
}

#endif /* !MLIB_ERRORS_H */
