#ifndef MLIB_MBIOO_H
#define MLIB_MBIOO_H

#include <stdio.h>

#include "__charN_t.h"
#include "__rune.h"

int freadrune(rune *, FILE *);

constexpr rune MBEOF = 0x110000;
constexpr rune MBERR = 0x110001;

#endif /* !MLIB_MBIOO_H */
