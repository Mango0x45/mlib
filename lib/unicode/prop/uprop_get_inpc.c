/* This file is autogenerated by gen/prop/inpc; DO NOT EDIT. */

#include "_bsearch.h"
#include "rune.h"
#include "unicode/prop.h"

static const struct {
	rune lo, hi;
	enum uprop_inpc val;
} lookup[] = {
	{RUNE_C(0x000900), RUNE_C(0x000902), INPC_TOP},
	{RUNE_C(0x000903), RUNE_C(0x000903), INPC_RIGHT},
	{RUNE_C(0x00093A), RUNE_C(0x00093A), INPC_TOP},
	{RUNE_C(0x00093B), RUNE_C(0x00093B), INPC_RIGHT},
	{RUNE_C(0x00093C), RUNE_C(0x00093C), INPC_BOTTOM},
	{RUNE_C(0x00093E), RUNE_C(0x00093E), INPC_RIGHT},
	{RUNE_C(0x00093F), RUNE_C(0x00093F), INPC_LEFT},
	{RUNE_C(0x000940), RUNE_C(0x000940), INPC_RIGHT},
	{RUNE_C(0x000941), RUNE_C(0x000944), INPC_BOTTOM},
	{RUNE_C(0x000945), RUNE_C(0x000948), INPC_TOP},
	{RUNE_C(0x000949), RUNE_C(0x00094C), INPC_RIGHT},
	{RUNE_C(0x00094D), RUNE_C(0x00094D), INPC_BOTTOM},
	{RUNE_C(0x00094E), RUNE_C(0x00094E), INPC_LEFT},
	{RUNE_C(0x00094F), RUNE_C(0x00094F), INPC_RIGHT},
	{RUNE_C(0x000951), RUNE_C(0x000951), INPC_TOP},
	{RUNE_C(0x000952), RUNE_C(0x000952), INPC_BOTTOM},
	{RUNE_C(0x000955), RUNE_C(0x000955), INPC_TOP},
	{RUNE_C(0x000956), RUNE_C(0x000957), INPC_BOTTOM},
	{RUNE_C(0x000962), RUNE_C(0x000963), INPC_BOTTOM},
	{RUNE_C(0x000981), RUNE_C(0x000981), INPC_TOP},
	{RUNE_C(0x000982), RUNE_C(0x000983), INPC_RIGHT},
	{RUNE_C(0x0009BC), RUNE_C(0x0009BC), INPC_BOTTOM},
	{RUNE_C(0x0009BE), RUNE_C(0x0009BE), INPC_RIGHT},
	{RUNE_C(0x0009BF), RUNE_C(0x0009BF), INPC_LEFT},
	{RUNE_C(0x0009C0), RUNE_C(0x0009C0), INPC_RIGHT},
	{RUNE_C(0x0009C1), RUNE_C(0x0009C4), INPC_BOTTOM},
	{RUNE_C(0x0009C7), RUNE_C(0x0009C8), INPC_LEFT},
	{RUNE_C(0x0009CB), RUNE_C(0x0009CC), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0009CD), RUNE_C(0x0009CD), INPC_BOTTOM},
	{RUNE_C(0x0009D7), RUNE_C(0x0009D7), INPC_RIGHT},
	{RUNE_C(0x0009E2), RUNE_C(0x0009E3), INPC_BOTTOM},
	{RUNE_C(0x0009FE), RUNE_C(0x0009FE), INPC_TOP},
	{RUNE_C(0x000A01), RUNE_C(0x000A02), INPC_TOP},
	{RUNE_C(0x000A03), RUNE_C(0x000A03), INPC_RIGHT},
	{RUNE_C(0x000A3C), RUNE_C(0x000A3C), INPC_BOTTOM},
	{RUNE_C(0x000A3E), RUNE_C(0x000A3E), INPC_RIGHT},
	{RUNE_C(0x000A3F), RUNE_C(0x000A3F), INPC_LEFT},
	{RUNE_C(0x000A40), RUNE_C(0x000A40), INPC_RIGHT},
	{RUNE_C(0x000A41), RUNE_C(0x000A42), INPC_BOTTOM},
	{RUNE_C(0x000A47), RUNE_C(0x000A48), INPC_TOP},
	{RUNE_C(0x000A4B), RUNE_C(0x000A4C), INPC_TOP},
	{RUNE_C(0x000A4D), RUNE_C(0x000A4D), INPC_BOTTOM},
	{RUNE_C(0x000A51), RUNE_C(0x000A51), INPC_BOTTOM},
	{RUNE_C(0x000A70), RUNE_C(0x000A71), INPC_TOP},
	{RUNE_C(0x000A75), RUNE_C(0x000A75), INPC_BOTTOM},
	{RUNE_C(0x000A81), RUNE_C(0x000A82), INPC_TOP},
	{RUNE_C(0x000A83), RUNE_C(0x000A83), INPC_RIGHT},
	{RUNE_C(0x000ABC), RUNE_C(0x000ABC), INPC_BOTTOM},
	{RUNE_C(0x000ABE), RUNE_C(0x000ABE), INPC_RIGHT},
	{RUNE_C(0x000ABF), RUNE_C(0x000ABF), INPC_LEFT},
	{RUNE_C(0x000AC0), RUNE_C(0x000AC0), INPC_RIGHT},
	{RUNE_C(0x000AC1), RUNE_C(0x000AC4), INPC_BOTTOM},
	{RUNE_C(0x000AC5), RUNE_C(0x000AC5), INPC_TOP},
	{RUNE_C(0x000AC7), RUNE_C(0x000AC8), INPC_TOP},
	{RUNE_C(0x000AC9), RUNE_C(0x000AC9), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x000ACB), RUNE_C(0x000ACC), INPC_RIGHT},
	{RUNE_C(0x000ACD), RUNE_C(0x000ACD), INPC_BOTTOM},
	{RUNE_C(0x000AE2), RUNE_C(0x000AE3), INPC_BOTTOM},
	{RUNE_C(0x000AFA), RUNE_C(0x000AFF), INPC_TOP},
	{RUNE_C(0x000B01), RUNE_C(0x000B01), INPC_TOP},
	{RUNE_C(0x000B02), RUNE_C(0x000B03), INPC_RIGHT},
	{RUNE_C(0x000B3C), RUNE_C(0x000B3C), INPC_BOTTOM},
	{RUNE_C(0x000B3E), RUNE_C(0x000B3E), INPC_RIGHT},
	{RUNE_C(0x000B3F), RUNE_C(0x000B3F), INPC_TOP},
	{RUNE_C(0x000B40), RUNE_C(0x000B40), INPC_RIGHT},
	{RUNE_C(0x000B41), RUNE_C(0x000B44), INPC_BOTTOM},
	{RUNE_C(0x000B47), RUNE_C(0x000B47), INPC_LEFT},
	{RUNE_C(0x000B48), RUNE_C(0x000B48), INPC_TOP_AND_LEFT},
	{RUNE_C(0x000B4B), RUNE_C(0x000B4B), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x000B4C), RUNE_C(0x000B4C), INPC_TOP_AND_LEFT_AND_RIGHT},
	{RUNE_C(0x000B4D), RUNE_C(0x000B4D), INPC_BOTTOM},
	{RUNE_C(0x000B55), RUNE_C(0x000B56), INPC_TOP},
	{RUNE_C(0x000B57), RUNE_C(0x000B57), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x000B62), RUNE_C(0x000B63), INPC_BOTTOM},
	{RUNE_C(0x000B82), RUNE_C(0x000B82), INPC_TOP},
	{RUNE_C(0x000BBE), RUNE_C(0x000BBF), INPC_RIGHT},
	{RUNE_C(0x000BC0), RUNE_C(0x000BC0), INPC_TOP},
	{RUNE_C(0x000BC1), RUNE_C(0x000BC2), INPC_RIGHT},
	{RUNE_C(0x000BC6), RUNE_C(0x000BC8), INPC_LEFT},
	{RUNE_C(0x000BCA), RUNE_C(0x000BCC), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x000BCD), RUNE_C(0x000BCD), INPC_TOP},
	{RUNE_C(0x000BD7), RUNE_C(0x000BD7), INPC_RIGHT},
	{RUNE_C(0x000C00), RUNE_C(0x000C00), INPC_TOP},
	{RUNE_C(0x000C01), RUNE_C(0x000C03), INPC_RIGHT},
	{RUNE_C(0x000C04), RUNE_C(0x000C04), INPC_TOP},
	{RUNE_C(0x000C3C), RUNE_C(0x000C3C), INPC_BOTTOM},
	{RUNE_C(0x000C3E), RUNE_C(0x000C40), INPC_TOP},
	{RUNE_C(0x000C41), RUNE_C(0x000C44), INPC_RIGHT},
	{RUNE_C(0x000C46), RUNE_C(0x000C47), INPC_TOP},
	{RUNE_C(0x000C48), RUNE_C(0x000C48), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x000C4A), RUNE_C(0x000C4D), INPC_TOP},
	{RUNE_C(0x000C55), RUNE_C(0x000C55), INPC_TOP},
	{RUNE_C(0x000C56), RUNE_C(0x000C56), INPC_BOTTOM},
	{RUNE_C(0x000C62), RUNE_C(0x000C63), INPC_BOTTOM},
	{RUNE_C(0x000C81), RUNE_C(0x000C81), INPC_TOP},
	{RUNE_C(0x000C82), RUNE_C(0x000C83), INPC_RIGHT},
	{RUNE_C(0x000CBC), RUNE_C(0x000CBC), INPC_BOTTOM},
	{RUNE_C(0x000CBE), RUNE_C(0x000CBE), INPC_RIGHT},
	{RUNE_C(0x000CBF), RUNE_C(0x000CBF), INPC_TOP},
	{RUNE_C(0x000CC0), RUNE_C(0x000CC0), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x000CC1), RUNE_C(0x000CC4), INPC_RIGHT},
	{RUNE_C(0x000CC6), RUNE_C(0x000CC6), INPC_TOP},
	{RUNE_C(0x000CC7), RUNE_C(0x000CC8), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x000CCA), RUNE_C(0x000CCB), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x000CCC), RUNE_C(0x000CCD), INPC_TOP},
	{RUNE_C(0x000CD5), RUNE_C(0x000CD6), INPC_RIGHT},
	{RUNE_C(0x000CE2), RUNE_C(0x000CE3), INPC_BOTTOM},
	{RUNE_C(0x000CF3), RUNE_C(0x000CF3), INPC_RIGHT},
	{RUNE_C(0x000D00), RUNE_C(0x000D01), INPC_TOP},
	{RUNE_C(0x000D02), RUNE_C(0x000D03), INPC_RIGHT},
	{RUNE_C(0x000D3B), RUNE_C(0x000D3C), INPC_TOP},
	{RUNE_C(0x000D3E), RUNE_C(0x000D42), INPC_RIGHT},
	{RUNE_C(0x000D43), RUNE_C(0x000D44), INPC_BOTTOM},
	{RUNE_C(0x000D46), RUNE_C(0x000D48), INPC_LEFT},
	{RUNE_C(0x000D4A), RUNE_C(0x000D4C), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x000D4D), RUNE_C(0x000D4E), INPC_TOP},
	{RUNE_C(0x000D57), RUNE_C(0x000D57), INPC_RIGHT},
	{RUNE_C(0x000D62), RUNE_C(0x000D63), INPC_BOTTOM},
	{RUNE_C(0x000D81), RUNE_C(0x000D81), INPC_TOP},
	{RUNE_C(0x000D82), RUNE_C(0x000D83), INPC_RIGHT},
	{RUNE_C(0x000DCA), RUNE_C(0x000DCA), INPC_TOP},
	{RUNE_C(0x000DCF), RUNE_C(0x000DD1), INPC_RIGHT},
	{RUNE_C(0x000DD2), RUNE_C(0x000DD3), INPC_TOP},
	{RUNE_C(0x000DD4), RUNE_C(0x000DD4), INPC_BOTTOM},
	{RUNE_C(0x000DD6), RUNE_C(0x000DD6), INPC_BOTTOM},
	{RUNE_C(0x000DD8), RUNE_C(0x000DD8), INPC_RIGHT},
	{RUNE_C(0x000DD9), RUNE_C(0x000DD9), INPC_LEFT},
	{RUNE_C(0x000DDA), RUNE_C(0x000DDA), INPC_TOP_AND_LEFT},
	{RUNE_C(0x000DDB), RUNE_C(0x000DDB), INPC_LEFT},
	{RUNE_C(0x000DDC), RUNE_C(0x000DDC), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x000DDD), RUNE_C(0x000DDD), INPC_TOP_AND_LEFT_AND_RIGHT},
	{RUNE_C(0x000DDE), RUNE_C(0x000DDE), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x000DDF), RUNE_C(0x000DDF), INPC_RIGHT},
	{RUNE_C(0x000DF2), RUNE_C(0x000DF3), INPC_RIGHT},
	{RUNE_C(0x000E30), RUNE_C(0x000E30), INPC_RIGHT},
	{RUNE_C(0x000E31), RUNE_C(0x000E31), INPC_TOP},
	{RUNE_C(0x000E32), RUNE_C(0x000E33), INPC_RIGHT},
	{RUNE_C(0x000E34), RUNE_C(0x000E37), INPC_TOP},
	{RUNE_C(0x000E38), RUNE_C(0x000E3A), INPC_BOTTOM},
	{RUNE_C(0x000E40), RUNE_C(0x000E44), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x000E45), RUNE_C(0x000E45), INPC_RIGHT},
	{RUNE_C(0x000E47), RUNE_C(0x000E4E), INPC_TOP},
	{RUNE_C(0x000EB0), RUNE_C(0x000EB0), INPC_RIGHT},
	{RUNE_C(0x000EB1), RUNE_C(0x000EB1), INPC_TOP},
	{RUNE_C(0x000EB2), RUNE_C(0x000EB3), INPC_RIGHT},
	{RUNE_C(0x000EB4), RUNE_C(0x000EB7), INPC_TOP},
	{RUNE_C(0x000EB8), RUNE_C(0x000EBA), INPC_BOTTOM},
	{RUNE_C(0x000EBB), RUNE_C(0x000EBB), INPC_TOP},
	{RUNE_C(0x000EBC), RUNE_C(0x000EBC), INPC_BOTTOM},
	{RUNE_C(0x000EC0), RUNE_C(0x000EC4), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x000EC8), RUNE_C(0x000ECE), INPC_TOP},
	{RUNE_C(0x000F18), RUNE_C(0x000F19), INPC_BOTTOM},
	{RUNE_C(0x000F35), RUNE_C(0x000F35), INPC_BOTTOM},
	{RUNE_C(0x000F37), RUNE_C(0x000F37), INPC_BOTTOM},
	{RUNE_C(0x000F39), RUNE_C(0x000F39), INPC_TOP},
	{RUNE_C(0x000F3E), RUNE_C(0x000F3E), INPC_RIGHT},
	{RUNE_C(0x000F3F), RUNE_C(0x000F3F), INPC_LEFT},
	{RUNE_C(0x000F71), RUNE_C(0x000F71), INPC_BOTTOM},
	{RUNE_C(0x000F72), RUNE_C(0x000F72), INPC_TOP},
	{RUNE_C(0x000F73), RUNE_C(0x000F73), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x000F74), RUNE_C(0x000F75), INPC_BOTTOM},
	{RUNE_C(0x000F76), RUNE_C(0x000F79), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x000F7A), RUNE_C(0x000F7E), INPC_TOP},
	{RUNE_C(0x000F7F), RUNE_C(0x000F7F), INPC_RIGHT},
	{RUNE_C(0x000F80), RUNE_C(0x000F80), INPC_TOP},
	{RUNE_C(0x000F81), RUNE_C(0x000F81), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x000F82), RUNE_C(0x000F83), INPC_TOP},
	{RUNE_C(0x000F84), RUNE_C(0x000F84), INPC_BOTTOM},
	{RUNE_C(0x000F86), RUNE_C(0x000F87), INPC_TOP},
	{RUNE_C(0x000F8D), RUNE_C(0x000F97), INPC_BOTTOM},
	{RUNE_C(0x000F99), RUNE_C(0x000FBC), INPC_BOTTOM},
	{RUNE_C(0x000FC6), RUNE_C(0x000FC6), INPC_BOTTOM},
	{RUNE_C(0x00102B), RUNE_C(0x00102C), INPC_RIGHT},
	{RUNE_C(0x00102D), RUNE_C(0x00102E), INPC_TOP},
	{RUNE_C(0x00102F), RUNE_C(0x001030), INPC_BOTTOM},
	{RUNE_C(0x001031), RUNE_C(0x001031), INPC_LEFT},
	{RUNE_C(0x001032), RUNE_C(0x001036), INPC_TOP},
	{RUNE_C(0x001037), RUNE_C(0x001037), INPC_BOTTOM},
	{RUNE_C(0x001038), RUNE_C(0x001038), INPC_RIGHT},
	{RUNE_C(0x00103A), RUNE_C(0x00103A), INPC_TOP},
	{RUNE_C(0x00103B), RUNE_C(0x00103B), INPC_RIGHT},
	{RUNE_C(0x00103C), RUNE_C(0x00103C), INPC_TOP_AND_BOTTOM_AND_LEFT},
	{RUNE_C(0x00103D), RUNE_C(0x00103E), INPC_BOTTOM},
	{RUNE_C(0x001056), RUNE_C(0x001057), INPC_RIGHT},
	{RUNE_C(0x001058), RUNE_C(0x001059), INPC_BOTTOM},
	{RUNE_C(0x00105E), RUNE_C(0x001060), INPC_BOTTOM},
	{RUNE_C(0x001062), RUNE_C(0x001064), INPC_RIGHT},
	{RUNE_C(0x001067), RUNE_C(0x00106D), INPC_RIGHT},
	{RUNE_C(0x001071), RUNE_C(0x001074), INPC_TOP},
	{RUNE_C(0x001082), RUNE_C(0x001082), INPC_BOTTOM},
	{RUNE_C(0x001083), RUNE_C(0x001083), INPC_RIGHT},
	{RUNE_C(0x001084), RUNE_C(0x001084), INPC_LEFT},
	{RUNE_C(0x001085), RUNE_C(0x001086), INPC_TOP},
	{RUNE_C(0x001087), RUNE_C(0x00108C), INPC_RIGHT},
	{RUNE_C(0x00108D), RUNE_C(0x00108D), INPC_BOTTOM},
	{RUNE_C(0x00108F), RUNE_C(0x00108F), INPC_RIGHT},
	{RUNE_C(0x00109A), RUNE_C(0x00109C), INPC_RIGHT},
	{RUNE_C(0x00109D), RUNE_C(0x00109D), INPC_TOP},
	{RUNE_C(0x001712), RUNE_C(0x001712), INPC_TOP},
	{RUNE_C(0x001713), RUNE_C(0x001714), INPC_BOTTOM},
	{RUNE_C(0x001715), RUNE_C(0x001715), INPC_RIGHT},
	{RUNE_C(0x001732), RUNE_C(0x001732), INPC_TOP},
	{RUNE_C(0x001733), RUNE_C(0x001733), INPC_BOTTOM},
	{RUNE_C(0x001734), RUNE_C(0x001734), INPC_RIGHT},
	{RUNE_C(0x001752), RUNE_C(0x001752), INPC_TOP},
	{RUNE_C(0x001753), RUNE_C(0x001753), INPC_BOTTOM},
	{RUNE_C(0x001772), RUNE_C(0x001772), INPC_TOP},
	{RUNE_C(0x001773), RUNE_C(0x001773), INPC_BOTTOM},
	{RUNE_C(0x0017B6), RUNE_C(0x0017B6), INPC_RIGHT},
	{RUNE_C(0x0017B7), RUNE_C(0x0017BA), INPC_TOP},
	{RUNE_C(0x0017BB), RUNE_C(0x0017BD), INPC_BOTTOM},
	{RUNE_C(0x0017BE), RUNE_C(0x0017BE), INPC_TOP_AND_LEFT},
	{RUNE_C(0x0017BF), RUNE_C(0x0017BF), INPC_TOP_AND_LEFT_AND_RIGHT},
	{RUNE_C(0x0017C0), RUNE_C(0x0017C0), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0017C1), RUNE_C(0x0017C3), INPC_LEFT},
	{RUNE_C(0x0017C4), RUNE_C(0x0017C5), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0017C6), RUNE_C(0x0017C6), INPC_TOP},
	{RUNE_C(0x0017C7), RUNE_C(0x0017C8), INPC_RIGHT},
	{RUNE_C(0x0017C9), RUNE_C(0x0017D1), INPC_TOP},
	{RUNE_C(0x0017D3), RUNE_C(0x0017D3), INPC_TOP},
	{RUNE_C(0x0017DD), RUNE_C(0x0017DD), INPC_TOP},
	{RUNE_C(0x001920), RUNE_C(0x001921), INPC_TOP},
	{RUNE_C(0x001922), RUNE_C(0x001922), INPC_BOTTOM},
	{RUNE_C(0x001923), RUNE_C(0x001924), INPC_RIGHT},
	{RUNE_C(0x001925), RUNE_C(0x001926), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x001927), RUNE_C(0x001928), INPC_TOP},
	{RUNE_C(0x001929), RUNE_C(0x00192B), INPC_RIGHT},
	{RUNE_C(0x001930), RUNE_C(0x001931), INPC_RIGHT},
	{RUNE_C(0x001932), RUNE_C(0x001932), INPC_BOTTOM},
	{RUNE_C(0x001933), RUNE_C(0x001938), INPC_RIGHT},
	{RUNE_C(0x001939), RUNE_C(0x001939), INPC_BOTTOM},
	{RUNE_C(0x00193A), RUNE_C(0x00193A), INPC_TOP},
	{RUNE_C(0x00193B), RUNE_C(0x00193B), INPC_BOTTOM},
	{RUNE_C(0x0019B0), RUNE_C(0x0019B4), INPC_RIGHT},
	{RUNE_C(0x0019B5), RUNE_C(0x0019B7), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x0019B8), RUNE_C(0x0019B9), INPC_RIGHT},
	{RUNE_C(0x0019BA), RUNE_C(0x0019BA), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x0019BB), RUNE_C(0x0019C0), INPC_RIGHT},
	{RUNE_C(0x0019C8), RUNE_C(0x0019C9), INPC_RIGHT},
	{RUNE_C(0x001A17), RUNE_C(0x001A17), INPC_TOP},
	{RUNE_C(0x001A18), RUNE_C(0x001A18), INPC_BOTTOM},
	{RUNE_C(0x001A19), RUNE_C(0x001A19), INPC_LEFT},
	{RUNE_C(0x001A1A), RUNE_C(0x001A1A), INPC_RIGHT},
	{RUNE_C(0x001A1B), RUNE_C(0x001A1B), INPC_TOP},
	{RUNE_C(0x001A55), RUNE_C(0x001A55), INPC_LEFT},
	{RUNE_C(0x001A56), RUNE_C(0x001A56), INPC_BOTTOM},
	{RUNE_C(0x001A57), RUNE_C(0x001A57), INPC_RIGHT},
	{RUNE_C(0x001A58), RUNE_C(0x001A5A), INPC_TOP},
	{RUNE_C(0x001A5B), RUNE_C(0x001A5E), INPC_BOTTOM},
	{RUNE_C(0x001A61), RUNE_C(0x001A61), INPC_RIGHT},
	{RUNE_C(0x001A62), RUNE_C(0x001A62), INPC_TOP},
	{RUNE_C(0x001A63), RUNE_C(0x001A64), INPC_RIGHT},
	{RUNE_C(0x001A65), RUNE_C(0x001A68), INPC_TOP},
	{RUNE_C(0x001A69), RUNE_C(0x001A6A), INPC_BOTTOM},
	{RUNE_C(0x001A6B), RUNE_C(0x001A6B), INPC_TOP},
	{RUNE_C(0x001A6C), RUNE_C(0x001A6C), INPC_BOTTOM},
	{RUNE_C(0x001A6D), RUNE_C(0x001A6D), INPC_RIGHT},
	{RUNE_C(0x001A6E), RUNE_C(0x001A72), INPC_LEFT},
	{RUNE_C(0x001A73), RUNE_C(0x001A7C), INPC_TOP},
	{RUNE_C(0x001A7F), RUNE_C(0x001A7F), INPC_BOTTOM},
	{RUNE_C(0x001B00), RUNE_C(0x001B03), INPC_TOP},
	{RUNE_C(0x001B04), RUNE_C(0x001B04), INPC_RIGHT},
	{RUNE_C(0x001B34), RUNE_C(0x001B34), INPC_TOP},
	{RUNE_C(0x001B35), RUNE_C(0x001B35), INPC_RIGHT},
	{RUNE_C(0x001B36), RUNE_C(0x001B37), INPC_TOP},
	{RUNE_C(0x001B38), RUNE_C(0x001B3A), INPC_BOTTOM},
	{RUNE_C(0x001B3B), RUNE_C(0x001B3B), INPC_BOTTOM_AND_RIGHT},
	{RUNE_C(0x001B3C), RUNE_C(0x001B3C), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x001B3D), RUNE_C(0x001B3D), INPC_TOP_AND_BOTTOM_AND_RIGHT},
	{RUNE_C(0x001B3E), RUNE_C(0x001B3F), INPC_LEFT},
	{RUNE_C(0x001B40), RUNE_C(0x001B41), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x001B42), RUNE_C(0x001B42), INPC_TOP},
	{RUNE_C(0x001B43), RUNE_C(0x001B43), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x001B44), RUNE_C(0x001B44), INPC_RIGHT},
	{RUNE_C(0x001B6B), RUNE_C(0x001B6B), INPC_TOP},
	{RUNE_C(0x001B6C), RUNE_C(0x001B6C), INPC_BOTTOM},
	{RUNE_C(0x001B6D), RUNE_C(0x001B73), INPC_TOP},
	{RUNE_C(0x001B80), RUNE_C(0x001B81), INPC_TOP},
	{RUNE_C(0x001B82), RUNE_C(0x001B82), INPC_RIGHT},
	{RUNE_C(0x001BA1), RUNE_C(0x001BA1), INPC_RIGHT},
	{RUNE_C(0x001BA2), RUNE_C(0x001BA3), INPC_BOTTOM},
	{RUNE_C(0x001BA4), RUNE_C(0x001BA4), INPC_TOP},
	{RUNE_C(0x001BA5), RUNE_C(0x001BA5), INPC_BOTTOM},
	{RUNE_C(0x001BA6), RUNE_C(0x001BA6), INPC_LEFT},
	{RUNE_C(0x001BA7), RUNE_C(0x001BA7), INPC_RIGHT},
	{RUNE_C(0x001BA8), RUNE_C(0x001BA9), INPC_TOP},
	{RUNE_C(0x001BAA), RUNE_C(0x001BAA), INPC_RIGHT},
	{RUNE_C(0x001BAC), RUNE_C(0x001BAD), INPC_BOTTOM},
	{RUNE_C(0x001BE6), RUNE_C(0x001BE6), INPC_TOP},
	{RUNE_C(0x001BE7), RUNE_C(0x001BE7), INPC_RIGHT},
	{RUNE_C(0x001BE8), RUNE_C(0x001BE9), INPC_TOP},
	{RUNE_C(0x001BEA), RUNE_C(0x001BEC), INPC_RIGHT},
	{RUNE_C(0x001BED), RUNE_C(0x001BED), INPC_TOP},
	{RUNE_C(0x001BEE), RUNE_C(0x001BEE), INPC_RIGHT},
	{RUNE_C(0x001BEF), RUNE_C(0x001BF1), INPC_TOP},
	{RUNE_C(0x001BF2), RUNE_C(0x001BF3), INPC_RIGHT},
	{RUNE_C(0x001C24), RUNE_C(0x001C26), INPC_RIGHT},
	{RUNE_C(0x001C27), RUNE_C(0x001C28), INPC_LEFT},
	{RUNE_C(0x001C29), RUNE_C(0x001C29), INPC_TOP_AND_LEFT},
	{RUNE_C(0x001C2A), RUNE_C(0x001C2B), INPC_RIGHT},
	{RUNE_C(0x001C2C), RUNE_C(0x001C2C), INPC_BOTTOM},
	{RUNE_C(0x001C2D), RUNE_C(0x001C33), INPC_TOP},
	{RUNE_C(0x001C34), RUNE_C(0x001C35), INPC_LEFT},
	{RUNE_C(0x001C36), RUNE_C(0x001C36), INPC_TOP},
	{RUNE_C(0x001C37), RUNE_C(0x001C37), INPC_BOTTOM},
	{RUNE_C(0x001CD0), RUNE_C(0x001CD2), INPC_TOP},
	{RUNE_C(0x001CD4), RUNE_C(0x001CD4), INPC_OVERSTRUCK},
	{RUNE_C(0x001CD5), RUNE_C(0x001CD9), INPC_BOTTOM},
	{RUNE_C(0x001CDA), RUNE_C(0x001CDB), INPC_TOP},
	{RUNE_C(0x001CDC), RUNE_C(0x001CDF), INPC_BOTTOM},
	{RUNE_C(0x001CE0), RUNE_C(0x001CE0), INPC_TOP},
	{RUNE_C(0x001CE1), RUNE_C(0x001CE1), INPC_RIGHT},
	{RUNE_C(0x001CE2), RUNE_C(0x001CE8), INPC_OVERSTRUCK},
	{RUNE_C(0x001CED), RUNE_C(0x001CED), INPC_BOTTOM},
	{RUNE_C(0x001CF4), RUNE_C(0x001CF4), INPC_TOP},
	{RUNE_C(0x001CF7), RUNE_C(0x001CF7), INPC_RIGHT},
	{RUNE_C(0x001DFB), RUNE_C(0x001DFB), INPC_TOP},
	{RUNE_C(0x0020F0), RUNE_C(0x0020F0), INPC_TOP},
	{RUNE_C(0x00A802), RUNE_C(0x00A802), INPC_TOP},
	{RUNE_C(0x00A806), RUNE_C(0x00A806), INPC_TOP},
	{RUNE_C(0x00A80B), RUNE_C(0x00A80B), INPC_TOP},
	{RUNE_C(0x00A823), RUNE_C(0x00A824), INPC_RIGHT},
	{RUNE_C(0x00A825), RUNE_C(0x00A825), INPC_BOTTOM},
	{RUNE_C(0x00A826), RUNE_C(0x00A826), INPC_TOP},
	{RUNE_C(0x00A827), RUNE_C(0x00A827), INPC_RIGHT},
	{RUNE_C(0x00A82C), RUNE_C(0x00A82C), INPC_BOTTOM},
	{RUNE_C(0x00A880), RUNE_C(0x00A881), INPC_RIGHT},
	{RUNE_C(0x00A8B4), RUNE_C(0x00A8C3), INPC_RIGHT},
	{RUNE_C(0x00A8C4), RUNE_C(0x00A8C4), INPC_BOTTOM},
	{RUNE_C(0x00A8C5), RUNE_C(0x00A8C5), INPC_TOP},
	{RUNE_C(0x00A8E0), RUNE_C(0x00A8F1), INPC_TOP},
	{RUNE_C(0x00A8FF), RUNE_C(0x00A8FF), INPC_TOP},
	{RUNE_C(0x00A926), RUNE_C(0x00A92A), INPC_TOP},
	{RUNE_C(0x00A92B), RUNE_C(0x00A92D), INPC_BOTTOM},
	{RUNE_C(0x00A947), RUNE_C(0x00A949), INPC_BOTTOM},
	{RUNE_C(0x00A94A), RUNE_C(0x00A94A), INPC_TOP},
	{RUNE_C(0x00A94B), RUNE_C(0x00A94E), INPC_BOTTOM},
	{RUNE_C(0x00A94F), RUNE_C(0x00A951), INPC_TOP},
	{RUNE_C(0x00A952), RUNE_C(0x00A953), INPC_RIGHT},
	{RUNE_C(0x00A980), RUNE_C(0x00A982), INPC_TOP},
	{RUNE_C(0x00A983), RUNE_C(0x00A983), INPC_RIGHT},
	{RUNE_C(0x00A9B3), RUNE_C(0x00A9B3), INPC_TOP},
	{RUNE_C(0x00A9B4), RUNE_C(0x00A9B5), INPC_RIGHT},
	{RUNE_C(0x00A9B6), RUNE_C(0x00A9B7), INPC_TOP},
	{RUNE_C(0x00A9B8), RUNE_C(0x00A9B9), INPC_BOTTOM},
	{RUNE_C(0x00A9BA), RUNE_C(0x00A9BB), INPC_LEFT},
	{RUNE_C(0x00A9BC), RUNE_C(0x00A9BC), INPC_TOP},
	{RUNE_C(0x00A9BD), RUNE_C(0x00A9BD), INPC_BOTTOM},
	{RUNE_C(0x00A9BE), RUNE_C(0x00A9BE), INPC_BOTTOM_AND_RIGHT},
	{RUNE_C(0x00A9BF), RUNE_C(0x00A9BF), INPC_BOTTOM_AND_LEFT},
	{RUNE_C(0x00A9C0), RUNE_C(0x00A9C0), INPC_BOTTOM_AND_RIGHT},
	{RUNE_C(0x00A9E5), RUNE_C(0x00A9E5), INPC_TOP},
	{RUNE_C(0x00AA29), RUNE_C(0x00AA2C), INPC_TOP},
	{RUNE_C(0x00AA2D), RUNE_C(0x00AA2D), INPC_BOTTOM},
	{RUNE_C(0x00AA2E), RUNE_C(0x00AA2E), INPC_TOP},
	{RUNE_C(0x00AA2F), RUNE_C(0x00AA30), INPC_LEFT},
	{RUNE_C(0x00AA31), RUNE_C(0x00AA31), INPC_TOP},
	{RUNE_C(0x00AA32), RUNE_C(0x00AA32), INPC_BOTTOM},
	{RUNE_C(0x00AA33), RUNE_C(0x00AA33), INPC_RIGHT},
	{RUNE_C(0x00AA34), RUNE_C(0x00AA34), INPC_LEFT},
	{RUNE_C(0x00AA35), RUNE_C(0x00AA36), INPC_BOTTOM},
	{RUNE_C(0x00AA43), RUNE_C(0x00AA43), INPC_TOP},
	{RUNE_C(0x00AA4C), RUNE_C(0x00AA4C), INPC_TOP},
	{RUNE_C(0x00AA4D), RUNE_C(0x00AA4D), INPC_RIGHT},
	{RUNE_C(0x00AA7B), RUNE_C(0x00AA7B), INPC_RIGHT},
	{RUNE_C(0x00AA7C), RUNE_C(0x00AA7C), INPC_TOP},
	{RUNE_C(0x00AA7D), RUNE_C(0x00AA7D), INPC_RIGHT},
	{RUNE_C(0x00AAB0), RUNE_C(0x00AAB0), INPC_TOP},
	{RUNE_C(0x00AAB1), RUNE_C(0x00AAB1), INPC_RIGHT},
	{RUNE_C(0x00AAB2), RUNE_C(0x00AAB3), INPC_TOP},
	{RUNE_C(0x00AAB4), RUNE_C(0x00AAB4), INPC_BOTTOM},
	{RUNE_C(0x00AAB5), RUNE_C(0x00AAB6), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x00AAB7), RUNE_C(0x00AAB8), INPC_TOP},
	{RUNE_C(0x00AAB9), RUNE_C(0x00AAB9), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x00AABA), RUNE_C(0x00AABA), INPC_RIGHT},
	{RUNE_C(0x00AABB), RUNE_C(0x00AABC), INPC_VISUAL_ORDER_LEFT},
	{RUNE_C(0x00AABD), RUNE_C(0x00AABD), INPC_RIGHT},
	{RUNE_C(0x00AABE), RUNE_C(0x00AABF), INPC_TOP},
	{RUNE_C(0x00AAC1), RUNE_C(0x00AAC1), INPC_TOP},
	{RUNE_C(0x00AAEB), RUNE_C(0x00AAEB), INPC_LEFT},
	{RUNE_C(0x00AAEC), RUNE_C(0x00AAEC), INPC_BOTTOM},
	{RUNE_C(0x00AAED), RUNE_C(0x00AAED), INPC_TOP},
	{RUNE_C(0x00AAEE), RUNE_C(0x00AAEE), INPC_LEFT},
	{RUNE_C(0x00AAEF), RUNE_C(0x00AAEF), INPC_RIGHT},
	{RUNE_C(0x00AAF5), RUNE_C(0x00AAF5), INPC_RIGHT},
	{RUNE_C(0x00ABE3), RUNE_C(0x00ABE4), INPC_RIGHT},
	{RUNE_C(0x00ABE5), RUNE_C(0x00ABE5), INPC_TOP},
	{RUNE_C(0x00ABE6), RUNE_C(0x00ABE7), INPC_RIGHT},
	{RUNE_C(0x00ABE8), RUNE_C(0x00ABE8), INPC_BOTTOM},
	{RUNE_C(0x00ABE9), RUNE_C(0x00ABEA), INPC_RIGHT},
	{RUNE_C(0x00ABEC), RUNE_C(0x00ABEC), INPC_RIGHT},
	{RUNE_C(0x00ABED), RUNE_C(0x00ABED), INPC_BOTTOM},
	{RUNE_C(0x010A01), RUNE_C(0x010A01), INPC_OVERSTRUCK},
	{RUNE_C(0x010A02), RUNE_C(0x010A03), INPC_BOTTOM},
	{RUNE_C(0x010A05), RUNE_C(0x010A05), INPC_TOP},
	{RUNE_C(0x010A06), RUNE_C(0x010A06), INPC_OVERSTRUCK},
	{RUNE_C(0x010A0C), RUNE_C(0x010A0E), INPC_BOTTOM},
	{RUNE_C(0x010A0F), RUNE_C(0x010A0F), INPC_TOP},
	{RUNE_C(0x010A38), RUNE_C(0x010A38), INPC_TOP},
	{RUNE_C(0x010A39), RUNE_C(0x010A3A), INPC_BOTTOM},
	{RUNE_C(0x011000), RUNE_C(0x011000), INPC_RIGHT},
	{RUNE_C(0x011001), RUNE_C(0x011001), INPC_TOP},
	{RUNE_C(0x011002), RUNE_C(0x011002), INPC_RIGHT},
	{RUNE_C(0x011038), RUNE_C(0x01103B), INPC_TOP},
	{RUNE_C(0x01103C), RUNE_C(0x011041), INPC_BOTTOM},
	{RUNE_C(0x011042), RUNE_C(0x011046), INPC_TOP},
	{RUNE_C(0x011070), RUNE_C(0x011070), INPC_TOP},
	{RUNE_C(0x011073), RUNE_C(0x011074), INPC_TOP},
	{RUNE_C(0x011080), RUNE_C(0x011081), INPC_TOP},
	{RUNE_C(0x011082), RUNE_C(0x011082), INPC_RIGHT},
	{RUNE_C(0x0110B0), RUNE_C(0x0110B0), INPC_RIGHT},
	{RUNE_C(0x0110B1), RUNE_C(0x0110B1), INPC_LEFT},
	{RUNE_C(0x0110B2), RUNE_C(0x0110B2), INPC_RIGHT},
	{RUNE_C(0x0110B3), RUNE_C(0x0110B4), INPC_BOTTOM},
	{RUNE_C(0x0110B5), RUNE_C(0x0110B6), INPC_TOP},
	{RUNE_C(0x0110B7), RUNE_C(0x0110B8), INPC_RIGHT},
	{RUNE_C(0x0110B9), RUNE_C(0x0110BA), INPC_BOTTOM},
	{RUNE_C(0x0110C2), RUNE_C(0x0110C2), INPC_BOTTOM},
	{RUNE_C(0x011100), RUNE_C(0x011102), INPC_TOP},
	{RUNE_C(0x011127), RUNE_C(0x011129), INPC_TOP},
	{RUNE_C(0x01112A), RUNE_C(0x01112B), INPC_BOTTOM},
	{RUNE_C(0x01112C), RUNE_C(0x01112C), INPC_LEFT},
	{RUNE_C(0x01112D), RUNE_C(0x01112D), INPC_TOP},
	{RUNE_C(0x01112E), RUNE_C(0x01112F), INPC_TOP_AND_BOTTOM},
	{RUNE_C(0x011130), RUNE_C(0x011130), INPC_TOP},
	{RUNE_C(0x011131), RUNE_C(0x011132), INPC_BOTTOM},
	{RUNE_C(0x011134), RUNE_C(0x011134), INPC_TOP},
	{RUNE_C(0x011145), RUNE_C(0x011146), INPC_RIGHT},
	{RUNE_C(0x011173), RUNE_C(0x011173), INPC_BOTTOM},
	{RUNE_C(0x011180), RUNE_C(0x011181), INPC_TOP},
	{RUNE_C(0x011182), RUNE_C(0x011182), INPC_RIGHT},
	{RUNE_C(0x0111B3), RUNE_C(0x0111B3), INPC_RIGHT},
	{RUNE_C(0x0111B4), RUNE_C(0x0111B4), INPC_LEFT},
	{RUNE_C(0x0111B5), RUNE_C(0x0111B5), INPC_RIGHT},
	{RUNE_C(0x0111B6), RUNE_C(0x0111BB), INPC_BOTTOM},
	{RUNE_C(0x0111BC), RUNE_C(0x0111BE), INPC_TOP},
	{RUNE_C(0x0111BF), RUNE_C(0x0111BF), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x0111C0), RUNE_C(0x0111C0), INPC_RIGHT},
	{RUNE_C(0x0111C2), RUNE_C(0x0111C3), INPC_TOP},
	{RUNE_C(0x0111C9), RUNE_C(0x0111CA), INPC_BOTTOM},
	{RUNE_C(0x0111CB), RUNE_C(0x0111CB), INPC_TOP},
	{RUNE_C(0x0111CC), RUNE_C(0x0111CC), INPC_BOTTOM},
	{RUNE_C(0x0111CE), RUNE_C(0x0111CE), INPC_LEFT},
	{RUNE_C(0x0111CF), RUNE_C(0x0111CF), INPC_TOP},
	{RUNE_C(0x01122C), RUNE_C(0x01122E), INPC_RIGHT},
	{RUNE_C(0x01122F), RUNE_C(0x01122F), INPC_BOTTOM},
	{RUNE_C(0x011230), RUNE_C(0x011231), INPC_TOP},
	{RUNE_C(0x011232), RUNE_C(0x011233), INPC_TOP_AND_RIGHT},
	{RUNE_C(0x011234), RUNE_C(0x011234), INPC_TOP},
	{RUNE_C(0x011235), RUNE_C(0x011235), INPC_RIGHT},
	{RUNE_C(0x011236), RUNE_C(0x011237), INPC_TOP},
	{RUNE_C(0x01123E), RUNE_C(0x01123E), INPC_TOP},
	{RUNE_C(0x011241), RUNE_C(0x011241), INPC_BOTTOM},
	{RUNE_C(0x0112DF), RUNE_C(0x0112DF), INPC_TOP},
	{RUNE_C(0x0112E0), RUNE_C(0x0112E0), INPC_RIGHT},
	{RUNE_C(0x0112E1), RUNE_C(0x0112E1), INPC_LEFT},
	{RUNE_C(0x0112E2), RUNE_C(0x0112E2), INPC_RIGHT},
	{RUNE_C(0x0112E3), RUNE_C(0x0112E4), INPC_BOTTOM},
	{RUNE_C(0x0112E5), RUNE_C(0x0112E8), INPC_TOP},
	{RUNE_C(0x0112E9), RUNE_C(0x0112EA), INPC_BOTTOM},
	{RUNE_C(0x011300), RUNE_C(0x011301), INPC_TOP},
	{RUNE_C(0x011302), RUNE_C(0x011303), INPC_RIGHT},
	{RUNE_C(0x01133B), RUNE_C(0x01133C), INPC_BOTTOM},
	{RUNE_C(0x01133E), RUNE_C(0x01133F), INPC_RIGHT},
	{RUNE_C(0x011340), RUNE_C(0x011340), INPC_TOP},
	{RUNE_C(0x011341), RUNE_C(0x011344), INPC_RIGHT},
	{RUNE_C(0x011347), RUNE_C(0x011348), INPC_LEFT},
	{RUNE_C(0x01134B), RUNE_C(0x01134C), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x01134D), RUNE_C(0x01134D), INPC_RIGHT},
	{RUNE_C(0x011357), RUNE_C(0x011357), INPC_RIGHT},
	{RUNE_C(0x011362), RUNE_C(0x011363), INPC_RIGHT},
	{RUNE_C(0x011366), RUNE_C(0x01136C), INPC_TOP},
	{RUNE_C(0x011370), RUNE_C(0x011374), INPC_TOP},
	{RUNE_C(0x011435), RUNE_C(0x011435), INPC_RIGHT},
	{RUNE_C(0x011436), RUNE_C(0x011436), INPC_LEFT},
	{RUNE_C(0x011437), RUNE_C(0x011437), INPC_RIGHT},
	{RUNE_C(0x011438), RUNE_C(0x01143D), INPC_BOTTOM},
	{RUNE_C(0x01143E), RUNE_C(0x01143F), INPC_TOP},
	{RUNE_C(0x011440), RUNE_C(0x011441), INPC_RIGHT},
	{RUNE_C(0x011442), RUNE_C(0x011442), INPC_BOTTOM},
	{RUNE_C(0x011443), RUNE_C(0x011444), INPC_TOP},
	{RUNE_C(0x011445), RUNE_C(0x011445), INPC_RIGHT},
	{RUNE_C(0x011446), RUNE_C(0x011446), INPC_BOTTOM},
	{RUNE_C(0x01145E), RUNE_C(0x01145E), INPC_TOP},
	{RUNE_C(0x0114B0), RUNE_C(0x0114B0), INPC_RIGHT},
	{RUNE_C(0x0114B1), RUNE_C(0x0114B1), INPC_LEFT},
	{RUNE_C(0x0114B2), RUNE_C(0x0114B2), INPC_RIGHT},
	{RUNE_C(0x0114B3), RUNE_C(0x0114B8), INPC_BOTTOM},
	{RUNE_C(0x0114B9), RUNE_C(0x0114B9), INPC_LEFT},
	{RUNE_C(0x0114BA), RUNE_C(0x0114BA), INPC_TOP},
	{RUNE_C(0x0114BB), RUNE_C(0x0114BB), INPC_TOP_AND_LEFT},
	{RUNE_C(0x0114BC), RUNE_C(0x0114BC), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0114BD), RUNE_C(0x0114BD), INPC_RIGHT},
	{RUNE_C(0x0114BE), RUNE_C(0x0114BE), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0114BF), RUNE_C(0x0114C0), INPC_TOP},
	{RUNE_C(0x0114C1), RUNE_C(0x0114C1), INPC_RIGHT},
	{RUNE_C(0x0114C2), RUNE_C(0x0114C3), INPC_BOTTOM},
	{RUNE_C(0x0115AF), RUNE_C(0x0115AF), INPC_RIGHT},
	{RUNE_C(0x0115B0), RUNE_C(0x0115B0), INPC_LEFT},
	{RUNE_C(0x0115B1), RUNE_C(0x0115B1), INPC_RIGHT},
	{RUNE_C(0x0115B2), RUNE_C(0x0115B5), INPC_BOTTOM},
	{RUNE_C(0x0115B8), RUNE_C(0x0115B8), INPC_LEFT},
	{RUNE_C(0x0115B9), RUNE_C(0x0115B9), INPC_TOP_AND_LEFT},
	{RUNE_C(0x0115BA), RUNE_C(0x0115BA), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x0115BB), RUNE_C(0x0115BB), INPC_TOP_AND_LEFT_AND_RIGHT},
	{RUNE_C(0x0115BC), RUNE_C(0x0115BD), INPC_TOP},
	{RUNE_C(0x0115BE), RUNE_C(0x0115BE), INPC_RIGHT},
	{RUNE_C(0x0115BF), RUNE_C(0x0115C0), INPC_BOTTOM},
	{RUNE_C(0x0115DC), RUNE_C(0x0115DD), INPC_BOTTOM},
	{RUNE_C(0x011630), RUNE_C(0x011632), INPC_RIGHT},
	{RUNE_C(0x011633), RUNE_C(0x011638), INPC_BOTTOM},
	{RUNE_C(0x011639), RUNE_C(0x01163A), INPC_TOP},
	{RUNE_C(0x01163B), RUNE_C(0x01163C), INPC_RIGHT},
	{RUNE_C(0x01163D), RUNE_C(0x01163D), INPC_TOP},
	{RUNE_C(0x01163E), RUNE_C(0x01163E), INPC_RIGHT},
	{RUNE_C(0x01163F), RUNE_C(0x01163F), INPC_BOTTOM},
	{RUNE_C(0x011640), RUNE_C(0x011640), INPC_TOP},
	{RUNE_C(0x0116AB), RUNE_C(0x0116AB), INPC_TOP},
	{RUNE_C(0x0116AC), RUNE_C(0x0116AC), INPC_RIGHT},
	{RUNE_C(0x0116AD), RUNE_C(0x0116AD), INPC_TOP},
	{RUNE_C(0x0116AE), RUNE_C(0x0116AE), INPC_LEFT},
	{RUNE_C(0x0116AF), RUNE_C(0x0116AF), INPC_RIGHT},
	{RUNE_C(0x0116B0), RUNE_C(0x0116B1), INPC_BOTTOM},
	{RUNE_C(0x0116B2), RUNE_C(0x0116B5), INPC_TOP},
	{RUNE_C(0x0116B6), RUNE_C(0x0116B6), INPC_RIGHT},
	{RUNE_C(0x0116B7), RUNE_C(0x0116B7), INPC_BOTTOM},
	{RUNE_C(0x01171D), RUNE_C(0x01171D), INPC_BOTTOM},
	{RUNE_C(0x01171E), RUNE_C(0x01171E), INPC_TOP_AND_BOTTOM_AND_LEFT},
	{RUNE_C(0x01171F), RUNE_C(0x01171F), INPC_TOP},
	{RUNE_C(0x011720), RUNE_C(0x011721), INPC_RIGHT},
	{RUNE_C(0x011722), RUNE_C(0x011723), INPC_TOP},
	{RUNE_C(0x011724), RUNE_C(0x011725), INPC_BOTTOM},
	{RUNE_C(0x011726), RUNE_C(0x011726), INPC_LEFT},
	{RUNE_C(0x011727), RUNE_C(0x011727), INPC_TOP},
	{RUNE_C(0x011728), RUNE_C(0x011728), INPC_BOTTOM},
	{RUNE_C(0x011729), RUNE_C(0x01172B), INPC_TOP},
	{RUNE_C(0x01182C), RUNE_C(0x01182C), INPC_RIGHT},
	{RUNE_C(0x01182D), RUNE_C(0x01182D), INPC_LEFT},
	{RUNE_C(0x01182E), RUNE_C(0x01182E), INPC_RIGHT},
	{RUNE_C(0x01182F), RUNE_C(0x011832), INPC_BOTTOM},
	{RUNE_C(0x011833), RUNE_C(0x011837), INPC_TOP},
	{RUNE_C(0x011838), RUNE_C(0x011838), INPC_RIGHT},
	{RUNE_C(0x011839), RUNE_C(0x01183A), INPC_BOTTOM},
	{RUNE_C(0x011930), RUNE_C(0x011934), INPC_RIGHT},
	{RUNE_C(0x011935), RUNE_C(0x011935), INPC_LEFT},
	{RUNE_C(0x011937), RUNE_C(0x011937), INPC_LEFT},
	{RUNE_C(0x011938), RUNE_C(0x011938), INPC_LEFT_AND_RIGHT},
	{RUNE_C(0x01193B), RUNE_C(0x01193C), INPC_TOP},
	{RUNE_C(0x01193D), RUNE_C(0x01193D), INPC_RIGHT},
	{RUNE_C(0x01193F), RUNE_C(0x01193F), INPC_TOP},
	{RUNE_C(0x011940), RUNE_C(0x011940), INPC_RIGHT},
	{RUNE_C(0x011941), RUNE_C(0x011941), INPC_TOP},
	{RUNE_C(0x011942), RUNE_C(0x011942), INPC_BOTTOM_AND_RIGHT},
	{RUNE_C(0x011943), RUNE_C(0x011943), INPC_BOTTOM},
	{RUNE_C(0x0119D1), RUNE_C(0x0119D1), INPC_RIGHT},
	{RUNE_C(0x0119D2), RUNE_C(0x0119D2), INPC_LEFT},
	{RUNE_C(0x0119D3), RUNE_C(0x0119D3), INPC_RIGHT},
	{RUNE_C(0x0119D4), RUNE_C(0x0119D7), INPC_BOTTOM},
	{RUNE_C(0x0119DA), RUNE_C(0x0119DB), INPC_TOP},
	{RUNE_C(0x0119DC), RUNE_C(0x0119DF), INPC_RIGHT},
	{RUNE_C(0x0119E0), RUNE_C(0x0119E0), INPC_BOTTOM},
	{RUNE_C(0x0119E4), RUNE_C(0x0119E4), INPC_LEFT},
	{RUNE_C(0x011A01), RUNE_C(0x011A01), INPC_TOP},
	{RUNE_C(0x011A02), RUNE_C(0x011A03), INPC_BOTTOM},
	{RUNE_C(0x011A04), RUNE_C(0x011A09), INPC_TOP},
	{RUNE_C(0x011A0A), RUNE_C(0x011A0A), INPC_BOTTOM},
	{RUNE_C(0x011A33), RUNE_C(0x011A34), INPC_BOTTOM},
	{RUNE_C(0x011A35), RUNE_C(0x011A38), INPC_TOP},
	{RUNE_C(0x011A39), RUNE_C(0x011A39), INPC_RIGHT},
	{RUNE_C(0x011A3A), RUNE_C(0x011A3A), INPC_TOP},
	{RUNE_C(0x011A3B), RUNE_C(0x011A3E), INPC_BOTTOM},
	{RUNE_C(0x011A51), RUNE_C(0x011A51), INPC_TOP},
	{RUNE_C(0x011A52), RUNE_C(0x011A53), INPC_BOTTOM},
	{RUNE_C(0x011A54), RUNE_C(0x011A56), INPC_TOP},
	{RUNE_C(0x011A57), RUNE_C(0x011A58), INPC_RIGHT},
	{RUNE_C(0x011A59), RUNE_C(0x011A5B), INPC_BOTTOM},
	{RUNE_C(0x011A84), RUNE_C(0x011A89), INPC_TOP},
	{RUNE_C(0x011A8A), RUNE_C(0x011A95), INPC_BOTTOM},
	{RUNE_C(0x011A96), RUNE_C(0x011A96), INPC_TOP},
	{RUNE_C(0x011A97), RUNE_C(0x011A97), INPC_RIGHT},
	{RUNE_C(0x011A98), RUNE_C(0x011A98), INPC_TOP},
	{RUNE_C(0x011C2F), RUNE_C(0x011C2F), INPC_RIGHT},
	{RUNE_C(0x011C30), RUNE_C(0x011C31), INPC_TOP},
	{RUNE_C(0x011C32), RUNE_C(0x011C36), INPC_BOTTOM},
	{RUNE_C(0x011C38), RUNE_C(0x011C3D), INPC_TOP},
	{RUNE_C(0x011C3E), RUNE_C(0x011C3E), INPC_RIGHT},
	{RUNE_C(0x011C3F), RUNE_C(0x011C3F), INPC_BOTTOM},
	{RUNE_C(0x011C92), RUNE_C(0x011CA7), INPC_BOTTOM},
	{RUNE_C(0x011CA9), RUNE_C(0x011CA9), INPC_RIGHT},
	{RUNE_C(0x011CAA), RUNE_C(0x011CB0), INPC_BOTTOM},
	{RUNE_C(0x011CB1), RUNE_C(0x011CB1), INPC_LEFT},
	{RUNE_C(0x011CB2), RUNE_C(0x011CB2), INPC_BOTTOM},
	{RUNE_C(0x011CB3), RUNE_C(0x011CB3), INPC_TOP},
	{RUNE_C(0x011CB4), RUNE_C(0x011CB4), INPC_RIGHT},
	{RUNE_C(0x011CB5), RUNE_C(0x011CB6), INPC_TOP},
	{RUNE_C(0x011D31), RUNE_C(0x011D35), INPC_TOP},
	{RUNE_C(0x011D36), RUNE_C(0x011D36), INPC_BOTTOM},
	{RUNE_C(0x011D3A), RUNE_C(0x011D3A), INPC_TOP},
	{RUNE_C(0x011D3C), RUNE_C(0x011D3D), INPC_TOP},
	{RUNE_C(0x011D3F), RUNE_C(0x011D41), INPC_TOP},
	{RUNE_C(0x011D42), RUNE_C(0x011D42), INPC_BOTTOM},
	{RUNE_C(0x011D43), RUNE_C(0x011D43), INPC_TOP},
	{RUNE_C(0x011D44), RUNE_C(0x011D44), INPC_BOTTOM},
	{RUNE_C(0x011D46), RUNE_C(0x011D46), INPC_RIGHT},
	{RUNE_C(0x011D47), RUNE_C(0x011D47), INPC_BOTTOM},
	{RUNE_C(0x011D8A), RUNE_C(0x011D8E), INPC_RIGHT},
	{RUNE_C(0x011D90), RUNE_C(0x011D91), INPC_TOP},
	{RUNE_C(0x011D93), RUNE_C(0x011D94), INPC_RIGHT},
	{RUNE_C(0x011D95), RUNE_C(0x011D95), INPC_TOP},
	{RUNE_C(0x011D96), RUNE_C(0x011D96), INPC_RIGHT},
	{RUNE_C(0x011EF3), RUNE_C(0x011EF3), INPC_TOP},
	{RUNE_C(0x011EF4), RUNE_C(0x011EF4), INPC_BOTTOM},
	{RUNE_C(0x011EF5), RUNE_C(0x011EF5), INPC_LEFT},
	{RUNE_C(0x011EF6), RUNE_C(0x011EF6), INPC_RIGHT},
	{RUNE_C(0x011F00), RUNE_C(0x011F02), INPC_TOP},
	{RUNE_C(0x011F03), RUNE_C(0x011F03), INPC_RIGHT},
	{RUNE_C(0x011F34), RUNE_C(0x011F35), INPC_RIGHT},
	{RUNE_C(0x011F36), RUNE_C(0x011F37), INPC_TOP},
	{RUNE_C(0x011F38), RUNE_C(0x011F3A), INPC_BOTTOM},
	{RUNE_C(0x011F3E), RUNE_C(0x011F3F), INPC_LEFT},
	{RUNE_C(0x011F40), RUNE_C(0x011F40), INPC_TOP},
	{RUNE_C(0x011F41), RUNE_C(0x011F41), INPC_RIGHT},
};

_MLIB_DEFINE_BSEARCH(enum uprop_inpc, lookup, INPC_NA)

enum uprop_inpc
uprop_get_inpc(rune ch)
{
	return ch < lookup[0].lo ? INPC_NA : mlib_lookup(ch);
}