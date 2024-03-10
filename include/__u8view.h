#ifndef MLIB___U8VIEW_H
#define MLIB___U8VIEW_H

#include <stddef.h>

#include "__charN_t.h"

struct u8view {
	const char8_t *p;
	size_t len;
};

#endif /* !MLIB___U8VIEW_H */
