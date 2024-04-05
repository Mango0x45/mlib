#include "unicode/prop.h"

bool
uprop_is_join_c(rune ch)
{
	return ch == 0x200C || ch == 0x200D;
}
