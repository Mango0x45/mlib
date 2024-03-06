#include "bob.h"
#include "mbstring.h"

struct u8str *
u8strpushr(struct u8str *b, rune ch)
{
	if (!u8strgrow(b, b->len + rtou8(nullptr, ch, 0)))
		return nullptr;
	b->len += rtou8(b->p + b->len, ch, b->cap - b->len);
	return b;
}
