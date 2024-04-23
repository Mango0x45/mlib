#include "_bsearch.h"
#include "unicode/prop.h"

#define M(...) ((struct rview)_(__VA_ARGS__))
#define _(...) \
	{(const rune []){__VA_ARGS__}, lengthof(((const rune []){__VA_ARGS__}))}

static const struct {
	rune k;
	struct rview v;
} lookup[] = {
	{0x00DF /* ß */, _('S', 's')},
	{0x0149 /* ŉ */, _(U'ʼ', 'N')},
	{0x01F0 /* ǰ */, _('J', 0x30C)},
	{0x0390 /* ΐ */, _(U'Ι', 0x308, 0x301)},
	{0x03B0 /* ΰ */, _(U'Υ', 0x308, 0x301)},
	{0x0587 /* և */, _(U'Ե', U'ւ')},
	{0x1E96 /* ẖ */, _('H', 0x331)},
	{0x1E97 /* ẗ */, _('T', 0x308)},
	{0x1E98 /* ẘ */, _('W', 0x30A)},
	{0x1E99 /* ẙ */, _('Y', 0x30A)},
	{0x1E9A /* ẚ */, _('A', U'ʾ')},
	{0x1F50 /* ὐ */, _(U'Υ', 0x313)},
	{0x1F52 /* ὒ */, _(U'Υ', 0x313, 0x300)},
	{0x1F54 /* ὔ */, _(U'Υ', 0x313, 0x301)},
	{0x1F56 /* ὖ */, _(U'Υ', 0x313, 0x342)},
	{0x1FB2 /* ᾲ */, _(U'Ὰ', 0x345)},
	{0x1FB4 /* ᾴ */, _(U'Ά', 0x345)},
	{0x1FB6 /* ᾶ */, _(U'Α', 0x342)},
	{0x1FB7 /* ᾷ */, _(U'Α', 0x342, 0x345)},
	{0x1FC2 /* ῂ */, _(U'Ὴ', 0x345)},
	{0x1FC4 /* ῄ */, _(U'Ή', 0x345)},
	{0x1FC6 /* ῆ */, _(U'Η', 0x342)},
	{0x1FC7 /* ῇ */, _(U'Η', 0x342, 0x345)},
	{0x1FD2 /* ῒ */, _(U'Ι', 0x308, 0x300)},
	{0x1FD3 /* ΐ */, _(U'Ι', 0x308, 0x301)},
	{0x1FD6 /* ῖ */, _(U'Ι', 0x342)},
	{0x1FD7 /* ῗ */, _(U'Ι', 0x308, 0x342)},
	{0x1FE2 /* ῢ */, _(U'Υ', 0x308, 0x300)},
	{0x1FE3 /* ΰ */, _(U'Υ', 0x308, 0x301)},
	{0x1FE4 /* ῤ */, _(U'Ρ', 0x313)},
	{0x1FE6 /* ῦ */, _(U'Υ', 0x342)},
	{0x1FE7 /* ῧ */, _(U'Υ', 0x308, 0x342)},
	{0x1FF2 /* ῲ */, _(U'Ὼ', 0x345)},
	{0x1FF4 /* ῴ */, _(U'Ώ', 0x345)},
	{0x1FF6 /* ῶ */, _(U'Ω', 0x342)},
	{0x1FF7 /* ῷ */, _(U'Ω', 0x342, 0x345)},
	{0xFB00 /* ﬀ */, _('F', 'f')},
	{0xFB01 /* ﬁ */, _('F', 'i')},
	{0xFB02 /* ﬂ */, _('F', 'l')},
	{0xFB03 /* ﬃ */, _('F', 'f', 'i')},
	{0xFB04 /* ﬄ */, _('F', 'f', 'l')},
	{0xFB05 /* ﬅ */, _('S', 't')},
	{0xFB06 /* ﬆ */, _('S', 't')},
	{0xFB13 /* ﬓ */, _(U'Մ', U'ն')},
	{0xFB14 /* ﬔ */, _(U'Մ', U'ե')},
	{0xFB15 /* ﬕ */, _(U'Մ', U'ի')},
	{0xFB16 /* ﬖ */, _(U'Վ', U'ն')},
	{0xFB17 /* ﬗ */, _(U'Մ', U'խ')},
};

_MLIB_DEFINE_BSEARCH_KV(struct rview, lookup, M(ch))

struct rview
uprop_get_tc(rune ch, struct tcctx ctx)
{
	constexpr rune COMB_DOT_ABOVE = 0x307;

	if (ch == 'i' && ctx.az_or_tr)
		return M(U'İ');
	if (ch == COMB_DOT_ABOVE && ctx.lt && ctx.after_soft_dotted)
		return M();

	rune CH = uprop_get_stc(ch);
	return ch != CH ? M(CH) : mlib_lookup_kv(ch);
}
