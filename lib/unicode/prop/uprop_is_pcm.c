/* This file is autogenerated by gen/prop/bool-props; DO NOT EDIT. */

#include "__bsearch.h"
#include "bitset.h"
#include "rune.h"
#include "unicode/prop.h"

/* clang-format off */

static const struct {
	rune lo, hi;
} lookup[] = {
	{RUNE_C(0x000600), RUNE_C(0x000605)},
	{RUNE_C(0x0006DD), RUNE_C(0x0006DD)},
	{RUNE_C(0x00070F), RUNE_C(0x00070F)},
	{RUNE_C(0x000890), RUNE_C(0x000891)},
	{RUNE_C(0x0008E2), RUNE_C(0x0008E2)},
	{RUNE_C(0x0110BD), RUNE_C(0x0110BD)},
	{RUNE_C(0x0110CD), RUNE_C(0x0110CD)},
};

__MLIB_DEFINE_BSEARCH_CONTAINS(lookup)

bool
uprop_is_pcm(rune ch)
{
	return mlib_lookup_contains(ch);
}