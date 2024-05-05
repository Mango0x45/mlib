#ifndef MLIB_MBIO_H
#define MLIB_MBIO_H

#include <stdio.h>

#include "_charN_t.h"
#include "_rune.h"

int freadrune(rune *, FILE *);

constexpr rune MBEOF = 0x110000;
constexpr rune MBERR = 0x110001;

#endif /* !MLIB_MBIO_H */
