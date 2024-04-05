#include "unicode/prop.h"

bool
uprop_is_idsu(rune ch)
{
	return ch == 0x2FFE || ch == 0x2FFF;
}
