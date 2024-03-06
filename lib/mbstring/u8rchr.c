#include <stddef.h>
#include <stdint.h>

#define _RUNE_NO_MACRO_WRAPPER 1
#include "mbstring.h"

static char8_t *
memrchr1(const char8_t *s, size_t k, const char8_t *n)
{
	for (const char8_t *p = s + k - 1; k-- > 0; p--) {
		if (*p == *n)
			return (char8_t *)p;
	}
	return nullptr;
}

static char8_t *
memrchr2(const char8_t *h, size_t k, const char8_t *n)
{
	uint16_t hw, nw;
	const char8_t *H = h + k - 1;
	hw = H[-1] << 8 | H[-0];
	nw = n[+0] << 8 | n[+1];

	for (H -= 2, k -= 2; k; k--, hw = hw >> 8 | (*H-- << 8)) {
		if (hw == nw)
			return (char8_t *)H + 1;
	}

	return hw == nw ? (char8_t *)H + 1 : nullptr;
}

static char8_t *
memrchr3(const char8_t *h, size_t k, const char8_t *n)
{
	uint32_t hw, nw;
	const char8_t *H = h + k - 1;
	hw = H[-2] << 24 | H[-1] << 16 | H[-0] << 8;
	nw = n[+0] << 24 | n[+1] << 16 | n[+2] << 8;

	for (H -= 3, k -= 3; k;
	     k--, hw = (hw >> 8 | (*H-- << 24)) & UINT32_C(0xFFFFFF00))
	{
		if (hw == nw)
			return (char8_t *)H + 1;
	}

	return hw == nw ? (char8_t *)H + 1 : nullptr;
}

static char8_t *
memrchr4(const char8_t *h, size_t k, const char8_t *n)
{
	uint32_t hw, nw;
	const char8_t *H = h + k - 1;
	hw = H[-3] << 24 | H[-2] << 16 | H[-1] << 8 | H[-0];
	nw = n[+0] << 24 | n[+1] << 16 | n[+2] << 8 | n[+3];

	for (H -= 4, k -= 4; k; k--, hw = hw >> 8 | (*H-- << 24)) {
		if (hw == nw)
			return (char8_t *)H + 1;
	}

	return hw == nw ? (char8_t *)H + 1 : nullptr;
}

char8_t *
u8rchr(const char8_t *s, rune ch, size_t n)
{
	char8_t buf[U8_LEN_MAX];
	int m = rtou8(buf, ch, sizeof(buf));

	if (n < (size_t)m)
		return nullptr;
	switch (m) {
	case 1:
		return (char8_t *)memrchr1(s, n, buf);
	case 2:
		return (char8_t *)memrchr2(s, n, buf);
	case 3:
		return (char8_t *)memrchr3(s, n, buf);
	case 4:
		return (char8_t *)memrchr4(s, n, buf);
	}

	unreachable();
}
