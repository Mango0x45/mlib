#include <string.h>

#include "bob.h"

struct u8str *
u8strpushstr(struct u8str *b, const char *s)
{
	return u8strpushu8(b, (struct u8view){.p = s, .len = strlen(s)});
}
