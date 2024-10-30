#ifndef MLIB__UNVIEW_H
#define MLIB__UNVIEW_H

#include <stddef.h>

#include "_charN_t.h"

typedef struct {
	const char8_t *p;
	ptrdiff_t len;
} u8view_t;

typedef struct {
	const char16_t *p;
	ptrdiff_t len;
} u16view_t;

typedef struct {
	const char32_t *p;
	ptrdiff_t len;
} u32view_t;

#endif /* !MLIB__UNVIEW_H */
