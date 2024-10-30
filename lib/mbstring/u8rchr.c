#include <stddef.h>
#include <stdint.h>

#include "mbstring.h"

static const char8_t *
memrchr1(const char8_t *s, size_t k, const char8_t *n)
{
	for (const char8_t *p = s + k - 1; k-- > 0; p--) {
		if (*p == *n)
			return p;
	}
	return nullptr;
}

static const char8_t *
memrchr2(const char8_t *h, size_t k, const char8_t *n)
{
	uint16_t hw, nw;
	const char8_t *H = h + k - 1;
	hw = H[-1] << 8 | H[-0];
	nw = n[+0] << 8 | n[+1];

	for (H -= 2, k -= 2; k; k--, hw = hw >> 8 | (*H-- << 8)) {
		if (hw == nw)
			return H + 1;
	}

	return hw == nw ? H + 1 : nullptr;
}

static const char8_t *
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
			return H + 1;
	}

	return hw == nw ? H + 1 : nullptr;
}

static const char8_t *
memrchr4(const char8_t *h, size_t k, const char8_t *n)
{
	uint32_t hw, nw;
	const char8_t *H = h + k - 1;
	hw = H[-3] << 24 | H[-2] << 16 | H[-1] << 8 | H[-0];
	nw = n[+0] << 24 | n[+1] << 16 | n[+2] << 8 | n[+3];

	for (H -= 4, k -= 4; k; k--, hw = hw >> 8 | (*H-- << 24)) {
		if (hw == nw)
			return H + 1;
	}

	return hw == nw ? H + 1 : nullptr;
}

const char8_t *
u8rchr(u8view_t sv, rune ch)
{
	char8_t buf[U8_LEN_MAX];
	int n = rtou8(buf, ch, sizeof(buf));

	if (sv.len < n)
		return nullptr;
	switch (n) {
	case 1:
		return memrchr1(sv.p, sv.len, buf);
	case 2:
		return memrchr2(sv.p, sv.len, buf);
	case 3:
		return memrchr3(sv.p, sv.len, buf);
	case 4:
		return memrchr4(sv.p, sv.len, buf);
	}

	unreachable();
}
