#include "rune.h"
#include "unicode/prop.h"

bool
uprop_is_ri(rune ch)
{
	return ch >= RUNE_C(0x1F1E6) && ch <= RUNE_C(0x1F1FF);
}
