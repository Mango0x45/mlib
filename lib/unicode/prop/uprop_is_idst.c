#include "unicode/prop.h"

bool
uprop_is_idst(rune ch)
{
	return ch == 0x2FF2 || ch == 0x2FF3;
}
