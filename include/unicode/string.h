#ifndef MLIB_UNICODE_STRING_H
#define MLIB_UNICODE_STRING_H

#include <stddef.h>

#include "__charN_t.h"
#include "__u8view.h"

size_t u8glen(const char8_t *, size_t);
size_t u8gnext(struct u8view *, const char8_t **, size_t *);

#endif /* !MLIB_UNICODE_STRING_H */
