/* This file is autogenerated by gen/prop/bool-props; DO NOT EDIT. */

#include "__bsearch.h"
#include "bitset.h"
#include "rune.h"
#include "unicode/prop.h"

/* clang-format off */

static constexpr bitset(bs, LATIN1_MAX) = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFE, 0xFF, 0xFF, 0x07, 0xFE, 0xFF, 0xFF, 0x07,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x20, 0x04,
	0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF,
};

static const struct {
	rune lo, hi;
} lookup[] = {
	{RUNE_C(0x000100), RUNE_C(0x0001BA)},
	{RUNE_C(0x0001BC), RUNE_C(0x0001BF)},
	{RUNE_C(0x0001C4), RUNE_C(0x000293)},
	{RUNE_C(0x000295), RUNE_C(0x0002B8)},
	{RUNE_C(0x0002C0), RUNE_C(0x0002C1)},
	{RUNE_C(0x0002E0), RUNE_C(0x0002E4)},
	{RUNE_C(0x000345), RUNE_C(0x000345)},
	{RUNE_C(0x000370), RUNE_C(0x000373)},
	{RUNE_C(0x000376), RUNE_C(0x000377)},
	{RUNE_C(0x00037A), RUNE_C(0x00037D)},
	{RUNE_C(0x00037F), RUNE_C(0x00037F)},
	{RUNE_C(0x000386), RUNE_C(0x000386)},
	{RUNE_C(0x000388), RUNE_C(0x00038A)},
	{RUNE_C(0x00038C), RUNE_C(0x00038C)},
	{RUNE_C(0x00038E), RUNE_C(0x0003A1)},
	{RUNE_C(0x0003A3), RUNE_C(0x0003F5)},
	{RUNE_C(0x0003F7), RUNE_C(0x000481)},
	{RUNE_C(0x00048A), RUNE_C(0x00052F)},
	{RUNE_C(0x000531), RUNE_C(0x000556)},
	{RUNE_C(0x000560), RUNE_C(0x000588)},
	{RUNE_C(0x0010A0), RUNE_C(0x0010C5)},
	{RUNE_C(0x0010C7), RUNE_C(0x0010C7)},
	{RUNE_C(0x0010CD), RUNE_C(0x0010CD)},
	{RUNE_C(0x0010D0), RUNE_C(0x0010FA)},
	{RUNE_C(0x0010FC), RUNE_C(0x0010FF)},
	{RUNE_C(0x0013A0), RUNE_C(0x0013F5)},
	{RUNE_C(0x0013F8), RUNE_C(0x0013FD)},
	{RUNE_C(0x001C80), RUNE_C(0x001C88)},
	{RUNE_C(0x001C90), RUNE_C(0x001CBA)},
	{RUNE_C(0x001CBD), RUNE_C(0x001CBF)},
	{RUNE_C(0x001D00), RUNE_C(0x001DBF)},
	{RUNE_C(0x001E00), RUNE_C(0x001F15)},
	{RUNE_C(0x001F18), RUNE_C(0x001F1D)},
	{RUNE_C(0x001F20), RUNE_C(0x001F45)},
	{RUNE_C(0x001F48), RUNE_C(0x001F4D)},
	{RUNE_C(0x001F50), RUNE_C(0x001F57)},
	{RUNE_C(0x001F59), RUNE_C(0x001F59)},
	{RUNE_C(0x001F5B), RUNE_C(0x001F5B)},
	{RUNE_C(0x001F5D), RUNE_C(0x001F5D)},
	{RUNE_C(0x001F5F), RUNE_C(0x001F7D)},
	{RUNE_C(0x001F80), RUNE_C(0x001FB4)},
	{RUNE_C(0x001FB6), RUNE_C(0x001FBC)},
	{RUNE_C(0x001FBE), RUNE_C(0x001FBE)},
	{RUNE_C(0x001FC2), RUNE_C(0x001FC4)},
	{RUNE_C(0x001FC6), RUNE_C(0x001FCC)},
	{RUNE_C(0x001FD0), RUNE_C(0x001FD3)},
	{RUNE_C(0x001FD6), RUNE_C(0x001FDB)},
	{RUNE_C(0x001FE0), RUNE_C(0x001FEC)},
	{RUNE_C(0x001FF2), RUNE_C(0x001FF4)},
	{RUNE_C(0x001FF6), RUNE_C(0x001FFC)},
	{RUNE_C(0x002071), RUNE_C(0x002071)},
	{RUNE_C(0x00207F), RUNE_C(0x00207F)},
	{RUNE_C(0x002090), RUNE_C(0x00209C)},
	{RUNE_C(0x002102), RUNE_C(0x002102)},
	{RUNE_C(0x002107), RUNE_C(0x002107)},
	{RUNE_C(0x00210A), RUNE_C(0x002113)},
	{RUNE_C(0x002115), RUNE_C(0x002115)},
	{RUNE_C(0x002119), RUNE_C(0x00211D)},
	{RUNE_C(0x002124), RUNE_C(0x002124)},
	{RUNE_C(0x002126), RUNE_C(0x002126)},
	{RUNE_C(0x002128), RUNE_C(0x002128)},
	{RUNE_C(0x00212A), RUNE_C(0x00212D)},
	{RUNE_C(0x00212F), RUNE_C(0x002134)},
	{RUNE_C(0x002139), RUNE_C(0x002139)},
	{RUNE_C(0x00213C), RUNE_C(0x00213F)},
	{RUNE_C(0x002145), RUNE_C(0x002149)},
	{RUNE_C(0x00214E), RUNE_C(0x00214E)},
	{RUNE_C(0x002160), RUNE_C(0x00217F)},
	{RUNE_C(0x002183), RUNE_C(0x002184)},
	{RUNE_C(0x0024B6), RUNE_C(0x0024E9)},
	{RUNE_C(0x002C00), RUNE_C(0x002CE4)},
	{RUNE_C(0x002CEB), RUNE_C(0x002CEE)},
	{RUNE_C(0x002CF2), RUNE_C(0x002CF3)},
	{RUNE_C(0x002D00), RUNE_C(0x002D25)},
	{RUNE_C(0x002D27), RUNE_C(0x002D27)},
	{RUNE_C(0x002D2D), RUNE_C(0x002D2D)},
	{RUNE_C(0x00A640), RUNE_C(0x00A66D)},
	{RUNE_C(0x00A680), RUNE_C(0x00A69D)},
	{RUNE_C(0x00A722), RUNE_C(0x00A787)},
	{RUNE_C(0x00A78B), RUNE_C(0x00A78E)},
	{RUNE_C(0x00A790), RUNE_C(0x00A7CA)},
	{RUNE_C(0x00A7D0), RUNE_C(0x00A7D1)},
	{RUNE_C(0x00A7D3), RUNE_C(0x00A7D3)},
	{RUNE_C(0x00A7D5), RUNE_C(0x00A7D9)},
	{RUNE_C(0x00A7F2), RUNE_C(0x00A7F6)},
	{RUNE_C(0x00A7F8), RUNE_C(0x00A7FA)},
	{RUNE_C(0x00AB30), RUNE_C(0x00AB5A)},
	{RUNE_C(0x00AB5C), RUNE_C(0x00AB69)},
	{RUNE_C(0x00AB70), RUNE_C(0x00ABBF)},
	{RUNE_C(0x00FB00), RUNE_C(0x00FB06)},
	{RUNE_C(0x00FB13), RUNE_C(0x00FB17)},
	{RUNE_C(0x00FF21), RUNE_C(0x00FF3A)},
	{RUNE_C(0x00FF41), RUNE_C(0x00FF5A)},
	{RUNE_C(0x010400), RUNE_C(0x01044F)},
	{RUNE_C(0x0104B0), RUNE_C(0x0104D3)},
	{RUNE_C(0x0104D8), RUNE_C(0x0104FB)},
	{RUNE_C(0x010570), RUNE_C(0x01057A)},
	{RUNE_C(0x01057C), RUNE_C(0x01058A)},
	{RUNE_C(0x01058C), RUNE_C(0x010592)},
	{RUNE_C(0x010594), RUNE_C(0x010595)},
	{RUNE_C(0x010597), RUNE_C(0x0105A1)},
	{RUNE_C(0x0105A3), RUNE_C(0x0105B1)},
	{RUNE_C(0x0105B3), RUNE_C(0x0105B9)},
	{RUNE_C(0x0105BB), RUNE_C(0x0105BC)},
	{RUNE_C(0x010780), RUNE_C(0x010780)},
	{RUNE_C(0x010783), RUNE_C(0x010785)},
	{RUNE_C(0x010787), RUNE_C(0x0107B0)},
	{RUNE_C(0x0107B2), RUNE_C(0x0107BA)},
	{RUNE_C(0x010C80), RUNE_C(0x010CB2)},
	{RUNE_C(0x010CC0), RUNE_C(0x010CF2)},
	{RUNE_C(0x0118A0), RUNE_C(0x0118DF)},
	{RUNE_C(0x016E40), RUNE_C(0x016E7F)},
	{RUNE_C(0x01D400), RUNE_C(0x01D454)},
	{RUNE_C(0x01D456), RUNE_C(0x01D49C)},
	{RUNE_C(0x01D49E), RUNE_C(0x01D49F)},
	{RUNE_C(0x01D4A2), RUNE_C(0x01D4A2)},
	{RUNE_C(0x01D4A5), RUNE_C(0x01D4A6)},
	{RUNE_C(0x01D4A9), RUNE_C(0x01D4AC)},
	{RUNE_C(0x01D4AE), RUNE_C(0x01D4B9)},
	{RUNE_C(0x01D4BB), RUNE_C(0x01D4BB)},
	{RUNE_C(0x01D4BD), RUNE_C(0x01D4C3)},
	{RUNE_C(0x01D4C5), RUNE_C(0x01D505)},
	{RUNE_C(0x01D507), RUNE_C(0x01D50A)},
	{RUNE_C(0x01D50D), RUNE_C(0x01D514)},
	{RUNE_C(0x01D516), RUNE_C(0x01D51C)},
	{RUNE_C(0x01D51E), RUNE_C(0x01D539)},
	{RUNE_C(0x01D53B), RUNE_C(0x01D53E)},
	{RUNE_C(0x01D540), RUNE_C(0x01D544)},
	{RUNE_C(0x01D546), RUNE_C(0x01D546)},
	{RUNE_C(0x01D54A), RUNE_C(0x01D550)},
	{RUNE_C(0x01D552), RUNE_C(0x01D6A5)},
	{RUNE_C(0x01D6A8), RUNE_C(0x01D6C0)},
	{RUNE_C(0x01D6C2), RUNE_C(0x01D6DA)},
	{RUNE_C(0x01D6DC), RUNE_C(0x01D6FA)},
	{RUNE_C(0x01D6FC), RUNE_C(0x01D714)},
	{RUNE_C(0x01D716), RUNE_C(0x01D734)},
	{RUNE_C(0x01D736), RUNE_C(0x01D74E)},
	{RUNE_C(0x01D750), RUNE_C(0x01D76E)},
	{RUNE_C(0x01D770), RUNE_C(0x01D788)},
	{RUNE_C(0x01D78A), RUNE_C(0x01D7A8)},
	{RUNE_C(0x01D7AA), RUNE_C(0x01D7C2)},
	{RUNE_C(0x01D7C4), RUNE_C(0x01D7CB)},
	{RUNE_C(0x01DF00), RUNE_C(0x01DF09)},
	{RUNE_C(0x01DF0B), RUNE_C(0x01DF1E)},
	{RUNE_C(0x01DF25), RUNE_C(0x01DF2A)},
	{RUNE_C(0x01E030), RUNE_C(0x01E06D)},
	{RUNE_C(0x01E900), RUNE_C(0x01E943)},
	{RUNE_C(0x01F130), RUNE_C(0x01F149)},
	{RUNE_C(0x01F150), RUNE_C(0x01F169)},
	{RUNE_C(0x01F170), RUNE_C(0x01F189)},
};

__MLIB_DEFINE_BSEARCH_CONTAINS(lookup)

bool
uprop_is_cased(rune ch)
{
	return ch <= LATIN1_MAX ? TESTBIT(bs, ch) : mlib_lookup_contains(ch);
}