/* This file is autogenerated by gen/prop/bool-props; DO NOT EDIT. */

#include "__bsearch.h"
#include "bitset.h"
#include "rune.h"
#include "unicode/prop.h"

/* clang-format off */

static constexpr bitset(bs, LATIN1_MAX) = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const struct {
	rune lo, hi;
} lookup[] = {
	{RUNE_C(0x00034F), RUNE_C(0x00034F)},
	{RUNE_C(0x00061C), RUNE_C(0x00061C)},
	{RUNE_C(0x00115F), RUNE_C(0x001160)},
	{RUNE_C(0x0017B4), RUNE_C(0x0017B5)},
	{RUNE_C(0x00180B), RUNE_C(0x00180F)},
	{RUNE_C(0x00200B), RUNE_C(0x00200F)},
	{RUNE_C(0x00202A), RUNE_C(0x00202E)},
	{RUNE_C(0x002060), RUNE_C(0x00206F)},
	{RUNE_C(0x003164), RUNE_C(0x003164)},
	{RUNE_C(0x00FE00), RUNE_C(0x00FE0F)},
	{RUNE_C(0x00FEFF), RUNE_C(0x00FEFF)},
	{RUNE_C(0x00FFA0), RUNE_C(0x00FFA0)},
	{RUNE_C(0x00FFF0), RUNE_C(0x00FFF8)},
	{RUNE_C(0x01BCA0), RUNE_C(0x01BCA3)},
	{RUNE_C(0x01D173), RUNE_C(0x01D17A)},
	{RUNE_C(0x0E0000), RUNE_C(0x0E0FFF)},
};

__MLIB_DEFINE_BSEARCH_CONTAINS(lookup)

bool
uprop_is_di(rune ch)
{
	return ch <= LATIN1_MAX ? TESTBIT(bs, ch) : mlib_lookup_contains(ch);
}