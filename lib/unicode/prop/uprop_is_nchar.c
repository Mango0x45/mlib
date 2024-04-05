#include "rune.h"
#include "unicode/prop.h"

bool
rprop_is_nchar(rune ch)
{
	return (ch >= 0xFDD0 && ch <= 0xFDEF)
	    || ((ch & 0xFFFE) == 0xFFFE
	        && (ch & RUNE_C(0xFF0000)) <= RUNE_C(0x0F0000));
}
