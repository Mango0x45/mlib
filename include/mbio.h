#ifndef MLIB_MBIOO_H
#define MLIB_MBIOO_H

#include <stdio.h>

#include "__charN_t.h"
#include "__rune.h"

typedef struct {
	char8_t _buf[4];
	int _fill;
} u8_io_state;

int freadrune(rune *, u8_io_state *, FILE *);

#endif /* !MLIB_MBIOO_H */
