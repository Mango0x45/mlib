#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define _RUNE_NO_MACRO_WRAPPER 1
#include "mbstring.h"

/* NOTE: The memmem*() functions were taken directly from the memmem()
   implementation on OpenBSD.  As a result, these functions are licensed under
   OpenBSDs 2-Clause BSD License instead of this libraries 0-Clause BSD License.

   The license for these functions is as follows:

       Copyright © 2005–2020 Rich Felker, et al.

       Permission is hereby granted, free of charge, to any person obtaining
       a copy of this software and associated documentation files (the
       “Software”), to deal in the Software without restriction, including
       without limitation the rights to use, copy, modify, merge, publish,
       distribute, sublicense, and/or sell copies of the Software, and to
       permit persons to whom the Software is furnished to do so, subject to
       the following conditions:

       The above copyright notice and this permission notice shall be
       included in all copies or substantial portions of the Software.

       THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
       EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
       MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
       IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
       CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
       TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
       SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

static char8_t *
memmem2(const char8_t *h, size_t k, const char8_t *n)
{
	uint16_t hw, nw;
	hw = h[0] << 8 | h[1];
	nw = n[0] << 8 | n[1];

	for (h += 2, k -= 2; k; k--, hw = hw << 8 | *h++) {
		if (hw == nw)
			return (char8_t *)h - 2;
	}
	return hw == nw ? (char8_t *)h - 2 : nullptr;
}

static char8_t *
memmem3(const char8_t *h, size_t k, const char8_t *n)
{
	uint32_t hw, nw;
	hw = h[0] << 24 | h[1] << 16 | h[2] << 8;
	nw = n[0] << 24 | n[1] << 16 | n[2] << 8;

	for (h += 3, k -= 3; k; k--, hw = (hw | *h++) << 8) {
		if (hw == nw)
			return (char8_t *)h - 3;
	}
	return hw == nw ? (char8_t *)h - 3 : nullptr;
}

static char8_t *
memmem4(const char8_t *h, size_t k, const char8_t *n)
{
	uint32_t hw, nw;
	hw = h[0] << 24 | h[1] << 16 | h[2] << 8 | h[3];
	nw = n[0] << 24 | n[1] << 16 | n[2] << 8 | n[3];

	for (h += 4, k -= 4; k; k--, hw = hw << 8 | *h++) {
		if (hw == nw)
			return (char8_t *)h - 4;
	}
	return hw == nw ? (char8_t *)h - 4 : nullptr;
}

char8_t *
u8chr(const char8_t *s, rune ch, size_t n)
{
	char8_t buf[U8_LEN_MAX];
	int m = rtou8(buf, ch, sizeof(buf));

	if (n < (size_t)m)
		return nullptr;
	switch (m) {
	case 1:
		return memchr(s, ch, n);
	case 2:
		return memmem2(s, n, buf);
	case 3:
		return memmem3(s, n, buf);
	case 4:
		return memmem4(s, n, buf);
	}

	unreachable();
}
