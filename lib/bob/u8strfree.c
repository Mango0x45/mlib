#include <stdlib.h>

#include "bob.h"

void
u8strfree(struct u8str b)
{
	free(b.p);
}
