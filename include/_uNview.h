#ifndef MLIB__U8VIEW_H
#define MLIB__U8VIEW_H

#include <stddef.h>

#include "_charN_t.h"

struct u8view {
	const char8_t *p;
	size_t len;
};

struct u16view {
	const char16_t *p;
	size_t len;
};

struct u32view {
	const char32_t *p;
	size_t len;
};

#endif /* !MLIB__U8VIEW_H */
