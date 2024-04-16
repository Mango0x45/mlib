#ifndef MLIB__U8VIEW_H
#define MLIB__U8VIEW_H

#include <stddef.h>

#include "_charN_t.h"

struct u8view {
	const char8_t *p;
	size_t len;
};

#endif /* !MLIB__U8VIEW_H */
