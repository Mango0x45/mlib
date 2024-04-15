#ifndef MLIB_UNICODE_PROP_H
#define MLIB_UNICODE_PROP_H

#include <inttypes.h>
#include <stddef.h>

#include "__rune.h"
#include "__u8view.h"

#define __mlib_uprop_attrs __nodiscard__, __unsequenced__

struct rview {
	const rune *p;
	size_t len;
};

struct lcctx {
	bool az_or_tr : 1; /* Azeri or Turkish */
	bool lt       : 1; /* Lithuanian */

	bool after_I    : 1; /* After ‘I’ */
	bool before_acc : 1; /* Before accent on ‘i’ or ‘j’ in Lithuanian */
	bool before_dot : 1; /* Before U+0307 */
	bool eow        : 1; /* End of word */
};

struct tcctx {
	bool az_or_tr : 1; /* Azeri or Turkish */
	bool lt       : 1; /* Lithuanian */

	bool after_i : 1; /* After ‘i’ */
};

struct ucctx {
	bool az_or_tr : 1; /* Azeri or Turkish */
	bool lt       : 1; /* Lithuanian */

	bool ẞ : 1; /* Uppercase ‘ß’ into ‘ẞ’ (instead of ‘SS’) */
	bool after_i : 1; /* After ‘i’ */
};

enum uprop_age : uint_least16_t {
	AGE_NA = 0, /* Not Assigned */
	AGE_V1_1 = (1 << 8) | 1,
	AGE_V2_0 = (2 << 8) | 0,
	AGE_V2_1 = (2 << 8) | 1,
	AGE_V3_0 = (3 << 8) | 0,
	AGE_V3_1 = (3 << 8) | 1,
	AGE_V3_2 = (3 << 8) | 2,
	AGE_V4_0 = (4 << 8) | 0,
	AGE_V4_1 = (4 << 8) | 1,
	AGE_V5_0 = (5 << 8) | 0,
	AGE_V5_1 = (5 << 8) | 1,
	AGE_V5_2 = (5 << 8) | 2,
	AGE_V6_0 = (6 << 8) | 0,
	AGE_V6_1 = (6 << 8) | 1,
	AGE_V6_2 = (6 << 8) | 2,
	AGE_V6_3 = (6 << 8) | 3,
	AGE_V7_0 = (7 << 8) | 0,
	AGE_V8_0 = (8 << 8) | 0,
	AGE_V9_0 = (9 << 8) | 0,
	AGE_V10_0 = (10 << 8) | 0,
	AGE_V11_0 = (11 << 8) | 0,
	AGE_V12_0 = (12 << 8) | 0,
	AGE_V12_1 = (12 << 8) | 1,
	AGE_V13_0 = (13 << 8) | 0,
	AGE_V14_0 = (14 << 8) | 0,
	AGE_V15_0 = (15 << 8) | 0,
	AGE_V15_1 = (15 << 8) | 1,
};

[[__mlib_uprop_attrs, gnu::__always_inline__]]
static inline int
uprop_age_major(enum uprop_age a)
{
	return a >> 8;
}

[[__mlib_uprop_attrs, gnu::__always_inline__]]
static inline int
uprop_age_minor(enum uprop_age a)
{
	return a & 0xFF;
}

enum uprop_blk {
	BLK_NB = 0,                    /* No Block */
	BLK_ADLAM,                     /* Adlam */
	BLK_AEGEAN_NUMBERS,            /* Aegean Numbers */
	BLK_AHOM,                      /* Ahom */
	BLK_ALCHEMICAL,                /* Alchemical Symbols */
	BLK_ALPHABETIC_PF,             /* Alphabetic Presentation Forms */
	BLK_ANATOLIAN_HIEROGLYPHS,     /* Anatolian Hieroglyphs */
	BLK_ANCIENT_GREEK_MUSIC,       /* Ancient Greek Musical Notation */
	BLK_ANCIENT_GREEK_NUMBERS,     /* Ancient Greek Numbers */
	BLK_ANCIENT_SYMBOLS,           /* Ancient Symbols */
	BLK_ARABIC,                    /* Arabic */
	BLK_ARABIC_EXT_A,              /* Arabic Extended-A */
	BLK_ARABIC_EXT_B,              /* Arabic Extended-B */
	BLK_ARABIC_EXT_C,              /* Arabic Extended-C */
	BLK_ARABIC_MATH,               /* Arabic Mathematical Alphabetic Symbols */
	BLK_ARABIC_PF_A,               /* Arabic Presentation Forms-A */
	BLK_ARABIC_PF_B,               /* Arabic Presentation Forms-B */
	BLK_ARABIC_SUP,                /* Arabic Supplement */
	BLK_ARMENIAN,                  /* Armenian */
	BLK_ARROWS,                    /* Arrows */
	BLK_ASCII,                     /* Basic Latin */
	BLK_AVESTAN,                   /* Avestan */
	BLK_BALINESE,                  /* Balinese */
	BLK_BAMUM,                     /* Bamum */
	BLK_BAMUM_SUP,                 /* Bamum Supplement */
	BLK_BASSA_VAH,                 /* Bassa Vah */
	BLK_BATAK,                     /* Batak */
	BLK_BENGALI,                   /* Bengali */
	BLK_BHAIKSUKI,                 /* Bhaiksuki */
	BLK_BLOCK_ELEMENTS,            /* Block Elements */
	BLK_BOPOMOFO,                  /* Bopomofo */
	BLK_BOPOMOFO_EXT,              /* Bopomofo Extended */
	BLK_BOX_DRAWING,               /* Box Drawing */
	BLK_BRAHMI,                    /* Brahmi */
	BLK_BRAILLE,                   /* Braille Patterns */
	BLK_BUGINESE,                  /* Buginese */
	BLK_BUHID,                     /* Buhid */
	BLK_BYZANTINE_MUSIC,           /* Byzantine Musical Symbols */
	BLK_CARIAN,                    /* Carian */
	BLK_CAUCASIAN_ALBANIAN,        /* Caucasian Albanian */
	BLK_CHAKMA,                    /* Chakma */
	BLK_CHAM,                      /* Cham */
	BLK_CHEROKEE,                  /* Cherokee */
	BLK_CHEROKEE_SUP,              /* Cherokee Supplement */
	BLK_CHESS_SYMBOLS,             /* Chess Symbols */
	BLK_CHORASMIAN,                /* Chorasmian */
	BLK_CJK,                       /* CJK Unified Ideographs */
	BLK_CJK_COMPAT,                /* CJK Compatibility */
	BLK_CJK_COMPAT_FORMS,          /* CJK Compatibility Forms */
	BLK_CJK_COMPAT_IDEOGRAPHS,     /* CJK Compatibility Ideographs */
	BLK_CJK_COMPAT_IDEOGRAPHS_SUP, /* CJK Compatibility Ideographs Supplement */
	BLK_CJK_EXT_A,                 /* CJK Unified Ideographs Extension-A */
	BLK_CJK_EXT_B,                 /* CJK Unified Ideographs Extension-B */
	BLK_CJK_EXT_C,                 /* CJK Unified Ideographs Extension-C */
	BLK_CJK_EXT_D,                 /* CJK Unified Ideographs Extension-D */
	BLK_CJK_EXT_E,                 /* CJK Unified Ideographs Extension-E */
	BLK_CJK_EXT_F,                 /* CJK Unified Ideographs Extension-F */
	BLK_CJK_EXT_G,                 /* CJK Unified Ideographs Extension-G */
	BLK_CJK_EXT_H,                 /* CJK Unified Ideographs Extension-H */
	BLK_CJK_EXT_I,                 /* CJK Unified Ideographs Extension-I */
	BLK_CJK_RADICALS_SUP,          /* CJK Radicals Supplement */
	BLK_CJK_STROKES,               /* CJK Strokes */
	BLK_CJK_SYMBOLS,               /* CJK Symbols and Punctuation */
	BLK_COMPAT_JAMO,               /* Hangul Compatibility Jamo */
	BLK_CONTROL_PICTURES,          /* Control Pictures */
	BLK_COPTIC,                    /* Coptic */
	BLK_COPTIC_EPACT_NUMBERS,      /* Coptic Epact Numbers */
	BLK_COUNTING_ROD,              /* Counting Rod Numerals */
	BLK_CUNEIFORM,                 /* Cuneiform */
	BLK_CUNEIFORM_NUMBERS,         /* Cuneiform Numbers And Punctuation */
	BLK_CURRENCY_SYMBOLS,          /* Currency Symbols */
	BLK_CYPRIOT_SYLLABARY,         /* Cypriot Syllabary */
	BLK_CYPRO_MINOAN,              /* Cypro Minoan */
	BLK_CYRILLIC,                  /* Cyrillic */
	BLK_CYRILLIC_EXT_A,            /* Cyrillic Extended-A */
	BLK_CYRILLIC_EXT_B,            /* Cyrillic Extended-B */
	BLK_CYRILLIC_EXT_C,            /* Cyrillic Extended-C */
	BLK_CYRILLIC_EXT_D,            /* Cyrillic Extended-D */
	BLK_CYRILLIC_SUP,              /* Cyrillic Supplement */
	BLK_DESERET,                   /* Deseret */
	BLK_DEVANAGARI,                /* Devanagari */
	BLK_DEVANAGARI_EXT,            /* Devanagari Extended */
	BLK_DEVANAGARI_EXT_A,          /* Devanagari Extended-A */
	BLK_DIACRITICALS,              /* Combining Diacritical Marks */
	BLK_DIACRITICALS_EXT,          /* Combining Diacritical Marks Extended */
	BLK_DIACRITICALS_FOR_SYMBOLS,  /* Combining Diacritical Marks for Symbols */
	BLK_DIACRITICALS_SUP,          /* Combining Diacritical Marks Supplement */
	BLK_DINGBATS,                  /* Dingbats */
	BLK_DIVES_AKURU,               /* Dives Akuru */
	BLK_DOGRA,                     /* Dogra */
	BLK_DOMINO,                    /* Domino Tiles */
	BLK_DUPLOYAN,                  /* Duployan */
	BLK_EARLY_DYNASTIC_CUNEIFORM,  /* Early Dynastic Cuneiform */
	BLK_EGYPTIAN_HIEROGLYPH_FORMAT_CONTROLS, /* Egyptian Hieroglyph Format
	                                          * Controls
	                                          */
	BLK_EGYPTIAN_HIEROGLYPHS,                /* Egyptian Hieroglyphs */
	BLK_ELBASAN,                             /* Elbasan */
	BLK_ELYMAIC,                             /* Elymaic */
	BLK_EMOTICONS,                           /* Emoticons */
	BLK_ENCLOSED_ALPHANUM,                   /* Enclosed Alphanumerics */
	BLK_ENCLOSED_ALPHANUM_SUP,       /* Enclosed Alphanumeric Supplement */
	BLK_ENCLOSED_CJK,                /* Enclosed CJK Letters and Months */
	BLK_ENCLOSED_IDEOGRAPHIC_SUP,    /* Enclosed Ideographic Supplement */
	BLK_ETHIOPIC,                    /* Ethiopic */
	BLK_ETHIOPIC_EXT,                /* Ethiopic Extended */
	BLK_ETHIOPIC_EXT_A,              /* Ethiopic Extended-A */
	BLK_ETHIOPIC_EXT_B,              /* Ethiopic Extended-B */
	BLK_ETHIOPIC_SUP,                /* Ethiopic Supplement */
	BLK_GEOMETRIC_SHAPES,            /* Geometric Shapes */
	BLK_GEOMETRIC_SHAPES_EXT,        /* Geometric Shapes Extended */
	BLK_GEORGIAN,                    /* Georgian */
	BLK_GEORGIAN_EXT,                /* Georgian Extended */
	BLK_GEORGIAN_SUP,                /* Georgian Supplement */
	BLK_GLAGOLITIC,                  /* Glagolitic */
	BLK_GLAGOLITIC_SUP,              /* Glagolitic Supplement */
	BLK_GOTHIC,                      /* Gothic */
	BLK_GRANTHA,                     /* Grantha */
	BLK_GREEK,                       /* Greek and Coptic */
	BLK_GREEK_EXT,                   /* Greek Extended */
	BLK_GUJARATI,                    /* Gujarati */
	BLK_GUNJALA_GONDI,               /* Gunjala Gondi */
	BLK_GURMUKHI,                    /* Gurmukhi */
	BLK_HALF_AND_FULL_FORMS,         /* Halfwidth and Fullwidth Forms */
	BLK_HALF_MARKS,                  /* Combining Half Marks */
	BLK_HANGUL,                      /* Hangul Syllables */
	BLK_HANIFI_ROHINGYA,             /* Hanifi Rohingya */
	BLK_HANUNOO,                     /* Hanunoo */
	BLK_HATRAN,                      /* Hatran */
	BLK_HEBREW,                      /* Hebrew */
	BLK_HIGH_PU_SURROGATES,          /* High Private Use Surrogates */
	BLK_HIGH_SURROGATES,             /* High Surrogates */
	BLK_HIRAGANA,                    /* Hiragana */
	BLK_IDC,                         /* Ideographic Description Characters */
	BLK_IDEOGRAPHIC_SYMBOLS,         /* Ideographic Symbols and Punctuation */
	BLK_IMPERIAL_ARAMAIC,            /* Imperial Aramaic */
	BLK_INDIC_NUMBER_FORMS,          /* Common Indic Number Forms */
	BLK_INDIC_SIYAQ_NUMBERS,         /* Indic Siyaq Numbers */
	BLK_INSCRIPTIONAL_PAHLAVI,       /* Inscriptional Pahlavi */
	BLK_INSCRIPTIONAL_PARTHIAN,      /* Inscriptional Parthian */
	BLK_IPA_EXT,                     /* IPA Extensions */
	BLK_JAMO,                        /* Hangul Jamo */
	BLK_JAMO_EXT_A,                  /* Hangul Jamo Extended-A */
	BLK_JAMO_EXT_B,                  /* Hangul Jamo Extended-B */
	BLK_JAVANESE,                    /* Javanese */
	BLK_KAITHI,                      /* Kaithi */
	BLK_KAKTOVIK_NUMERALS,           /* Kaktovik Numerals */
	BLK_KANA_EXT_A,                  /* Kana Extended-A */
	BLK_KANA_EXT_B,                  /* Kana Extended-B */
	BLK_KANA_SUP,                    /* Kana Supplement */
	BLK_KANBUN,                      /* Kanbun */
	BLK_KANGXI,                      /* Kangxi Radicals */
	BLK_KANNADA,                     /* Kannada */
	BLK_KATAKANA,                    /* Katakana */
	BLK_KATAKANA_EXT,                /* Katakana Phonetic Extensions */
	BLK_KAWI,                        /* Kawi */
	BLK_KAYAH_LI,                    /* Kayah Li */
	BLK_KHAROSHTHI,                  /* Kharoshthi */
	BLK_KHITAN_SMALL_SCRIPT,         /* Khitan Small Script */
	BLK_KHMER,                       /* Khmer */
	BLK_KHMER_SYMBOLS,               /* Khmer Symbols */
	BLK_KHOJKI,                      /* Khojki */
	BLK_KHUDAWADI,                   /* Khudawadi */
	BLK_LAO,                         /* Lao */
	BLK_LATIN_1_SUP,                 /* Latin-1 Supplement */
	BLK_LATIN_EXT_A,                 /* Latin Extended-A */
	BLK_LATIN_EXT_ADDITIONAL,        /* Latin Extended Additional */
	BLK_LATIN_EXT_B,                 /* Latin Extended-B */
	BLK_LATIN_EXT_C,                 /* Latin Extended-C */
	BLK_LATIN_EXT_D,                 /* Latin Extended-D */
	BLK_LATIN_EXT_E,                 /* Latin Extended-E */
	BLK_LATIN_EXT_F,                 /* Latin Extended-F */
	BLK_LATIN_EXT_G,                 /* Latin Extended-G */
	BLK_LEPCHA,                      /* Lepcha */
	BLK_LETTERLIKE_SYMBOLS,          /* Letterlike Symbols */
	BLK_LIMBU,                       /* Limbu */
	BLK_LINEAR_A,                    /* Linear A */
	BLK_LINEAR_B_IDEOGRAMS,          /* Linear B Ideograms */
	BLK_LINEAR_B_SYLLABARY,          /* Linear B Syllabary */
	BLK_LISU,                        /* Lisu */
	BLK_LISU_SUP,                    /* Lisu Supplement */
	BLK_LOW_SURROGATES,              /* Low Surrogates */
	BLK_LYCIAN,                      /* Lycian */
	BLK_LYDIAN,                      /* Lydian */
	BLK_MAHAJANI,                    /* Mahajani */
	BLK_MAHJONG,                     /* Mahjong Tiles */
	BLK_MAKASAR,                     /* Makasar */
	BLK_MALAYALAM,                   /* Malayalam */
	BLK_MANDAIC,                     /* Mandaic */
	BLK_MANICHAEAN,                  /* Manichaean */
	BLK_MARCHEN,                     /* Marchen */
	BLK_MASARAM_GONDI,               /* Masaram Gondi */
	BLK_MATH_ALPHANUM,               /* Mathematical Alphanumeric Symbols */
	BLK_MATH_OPERATORS,              /* Mathematical Operators */
	BLK_MAYAN_NUMERALS,              /* Mayan Numerals */
	BLK_MEDEFAIDRIN,                 /* Medefaidrin */
	BLK_MEETEI_MAYEK,                /* Meetei Mayek */
	BLK_MEETEI_MAYEK_EXT,            /* Meetei Mayek Extensions */
	BLK_MENDE_KIKAKUI,               /* Mende Kikakui */
	BLK_MEROITIC_CURSIVE,            /* Meroitic Cursive */
	BLK_MEROITIC_HIEROGLYPHS,        /* Meroitic Hieroglyphs */
	BLK_MIAO,                        /* Miao */
	BLK_MISC_ARROWS,                 /* Miscellaneous Symbols And Arrows */
	BLK_MISC_MATH_SYMBOLS_A,         /* Miscellaneous Mathematical Symbols-A */
	BLK_MISC_MATH_SYMBOLS_B,         /* Miscellaneous Mathematical Symbols-B */
	BLK_MISC_PICTOGRAPHS,            /* Miscellaneous Symbols And Pictographs */
	BLK_MISC_SYMBOLS,                /* Miscellaneous Symbols */
	BLK_MISC_TECHNICAL,              /* Miscellaneous Technical */
	BLK_MODI,                        /* Modi */
	BLK_MODIFIER_LETTERS,            /* Spacing Modifier Letters */
	BLK_MODIFIER_TONE_LETTERS,       /* Modifier Tone Letters */
	BLK_MONGOLIAN,                   /* Mongolian */
	BLK_MONGOLIAN_SUP,               /* Mongolian Supplement */
	BLK_MRO,                         /* Mro */
	BLK_MULTANI,                     /* Multani */
	BLK_MUSIC,                       /* Musical Symbols */
	BLK_MYANMAR,                     /* Myanmar */
	BLK_MYANMAR_EXT_A,               /* Myanmar Extended-A */
	BLK_MYANMAR_EXT_B,               /* Myanmar Extended-B */
	BLK_NABATAEAN,                   /* Nabataean */
	BLK_NAG_MUNDARI,                 /* Nag Mundari */
	BLK_NANDINAGARI,                 /* Nandinagari */
	BLK_NEW_TAI_LUE,                 /* New Tai Lue */
	BLK_NEWA,                        /* Newa */
	BLK_NKO,                         /* NKo */
	BLK_NUMBER_FORMS,                /* Number Forms */
	BLK_NUSHU,                       /* Nushu */
	BLK_NYIAKENG_PUACHUE_HMONG,      /* Nyiakeng Puachue Hmong */
	BLK_OCR,                         /* Optical Character Recognition */
	BLK_OGHAM,                       /* Ogham */
	BLK_OL_CHIKI,                    /* Ol Chiki */
	BLK_OLD_HUNGARIAN,               /* Old Hungarian */
	BLK_OLD_ITALIC,                  /* Old Italic */
	BLK_OLD_NORTH_ARABIAN,           /* Old North Arabian */
	BLK_OLD_PERMIC,                  /* Old Permic */
	BLK_OLD_PERSIAN,                 /* Old Persian */
	BLK_OLD_SOGDIAN,                 /* Old Sogdian */
	BLK_OLD_SOUTH_ARABIAN,           /* Old South Arabian */
	BLK_OLD_TURKIC,                  /* Old Turkic */
	BLK_OLD_UYGHUR,                  /* Old Uyghur */
	BLK_ORIYA,                       /* Oriya */
	BLK_ORNAMENTAL_DINGBATS,         /* Ornamental Dingbats */
	BLK_OSAGE,                       /* Osage */
	BLK_OSMANYA,                     /* Osmanya */
	BLK_OTTOMAN_SIYAQ_NUMBERS,       /* Ottoman Siyaq Numbers */
	BLK_PAHAWH_HMONG,                /* Pahawh Hmong */
	BLK_PALMYRENE,                   /* Palmyrene */
	BLK_PAU_CIN_HAU,                 /* Pau Cin Hau */
	BLK_PHAGS_PA,                    /* Phags Pa */
	BLK_PHAISTOS,                    /* Phaistos Disc */
	BLK_PHOENICIAN,                  /* Phoenician */
	BLK_PHONETIC_EXT,                /* Phonetic Extensions */
	BLK_PHONETIC_EXT_SUP,            /* Phonetic Extensions Supplement */
	BLK_PLAYING_CARDS,               /* Playing Cards */
	BLK_PSALTER_PAHLAVI,             /* Psalter Pahlavi */
	BLK_PUA,                         /* Private Use Area */
	BLK_PUNCTUATION,                 /* General Punctuation */
	BLK_REJANG,                      /* Rejang */
	BLK_RUMI,                        /* Rumi Numeral Symbols */
	BLK_RUNIC,                       /* Runic */
	BLK_SAMARITAN,                   /* Samaritan */
	BLK_SAURASHTRA,                  /* Saurashtra */
	BLK_SHARADA,                     /* Sharada */
	BLK_SHAVIAN,                     /* Shavian */
	BLK_SHORTHAND_FORMAT_CONTROLS,   /* Shorthand Format Controls */
	BLK_SIDDHAM,                     /* Siddham */
	BLK_SINHALA,                     /* Sinhala */
	BLK_SINHALA_ARCHAIC_NUMBERS,     /* Sinhala Archaic Numbers */
	BLK_SMALL_FORMS,                 /* Small Form Variants */
	BLK_SMALL_KANA_EXT,              /* Small Kana Extension */
	BLK_SOGDIAN,                     /* Sogdian */
	BLK_SORA_SOMPENG,                /* Sora_Sompeng */
	BLK_SOYOMBO,                     /* Soyombo */
	BLK_SPECIALS,                    /* Specials */
	BLK_SUNDANESE,                   /* Sundanese */
	BLK_SUNDANESE_SUP,               /* Sundanese Supplement */
	BLK_SUP_ARROWS_A,                /* Supplemental Arrows-A */
	BLK_SUP_ARROWS_B,                /* Supplemental Arrows-B */
	BLK_SUP_ARROWS_C,                /* Supplemental Arrows-C */
	BLK_SUP_MATH_OPERATORS,          /* Supplemental Mathematical Operators */
	BLK_SUP_PUA_A,                   /* Supplementary Private Use Area-A */
	BLK_SUP_PUA_B,                   /* Supplementary Private Use Area-B */
	BLK_SUP_PUNCTUATION,             /* Supplemental Punctuation */
	BLK_SUP_SYMBOLS_AND_PICTOGRAPHS, /* Supplemental Symbols And Pictographs */
	BLK_SUPER_AND_SUB,               /* Superscripts And Subscripts */
	BLK_SUTTON_SIGNWRITING,          /* Sutton SignWriting */
	BLK_SYLOTI_NAGRI,                /* Syloti Nagri */
	BLK_SYMBOLS_AND_PICTOGRAPHS_EXT_A, /* Symbols And Pictographs Extended-A */
	BLK_SYMBOLS_FOR_LEGACY_COMPUTING,  /* Symbols For Legacy Computing */
	BLK_SYRIAC,                        /* Syriac */
	BLK_SYRIAC_SUP,                    /* Syriac Supplement */
	BLK_TAGALOG,                       /* Tagalog */
	BLK_TAGBANWA,                      /* Tagbanwa */
	BLK_TAGS,                          /* Tags */
	BLK_TAI_LE,                        /* Tai Le */
	BLK_TAI_THAM,                      /* Tai Tham */
	BLK_TAI_VIET,                      /* Tai Viet */
	BLK_TAI_XUAN_JING,                 /* Tai Xuan Jing Symbols */
	BLK_TAKRI,                         /* Takri */
	BLK_TAMIL,                         /* Tamil */
	BLK_TAMIL_SUP,                     /* Tamil Supplement */
	BLK_TANGSA,                        /* Tangsa */
	BLK_TANGUT,                        /* Tangut */
	BLK_TANGUT_COMPONENTS,             /* Tangut Components */
	BLK_TANGUT_SUP,                    /* Tangut Supplement */
	BLK_TELUGU,                        /* Telugu */
	BLK_THAANA,                        /* Thaana */
	BLK_THAI,                          /* Thai */
	BLK_TIBETAN,                       /* Tibetan */
	BLK_TIFINAGH,                      /* Tifinagh */
	BLK_TIRHUTA,                       /* Tirhuta */
	BLK_TOTO,                          /* Toto */
	BLK_TRANSPORT_AND_MAP,             /* Transport And Map Symbols */
	BLK_UCAS,             /* Unified Canadian Aboriginal Syllabics */
	BLK_UCAS_EXT,         /* Unified Canadian Aboriginal Syllabics Extended */
	BLK_UCAS_EXT_A,       /* Unified Canadian Aboriginal Syllabics Extended-A */
	BLK_UGARITIC,         /* Ugaritic */
	BLK_VAI,              /* Vai */
	BLK_VEDIC_EXT,        /* Vedic Extensions */
	BLK_VERTICAL_FORMS,   /* Vertical_Forms */
	BLK_VITHKUQI,         /* Vithkuqi */
	BLK_VS,               /* Variation Selectors */
	BLK_VS_SUP,           /* Variation Selectors Supplement */
	BLK_WANCHO,           /* Wancho */
	BLK_WARANG_CITI,      /* Warang Citi */
	BLK_YEZIDI,           /* Yezidi */
	BLK_YI_RADICALS,      /* Yi Radicals */
	BLK_YI_SYLLABLES,     /* Yi Syllables */
	BLK_YIJING,           /* Yijing Hexagram Symbols */
	BLK_ZANABAZAR_SQUARE, /* Zanabazar Square */
	BLK_ZNAMENNY_MUSIC,   /* Znamenny Musical Notation */
};

enum uprop_bpt {
	BPT_N, /* None */
	BPT_C, /* Close */
	BPT_O, /* Open */
};

enum uprop_dt {
	DT_NONE, /* None */
	DT_CAN,  /* Canonical */
	DT_COM,  /* Compat */
	DT_ENC,  /* Circle */
	DT_FIN,  /* Final */
	DT_FONT, /* Font */
	DT_FRA,  /* Fraction */
	DT_INIT, /* Initial */
	DT_ISO,  /* Isolated */
	DT_MED,  /* Medial */
	DT_NAR,  /* Narrow */
	DT_NB,   /* Nobreak */
	DT_SML,  /* Small */
	DT_SQR,  /* Square */
	DT_SUB,  /* Sub */
	DT_SUP,  /* Super */
	DT_VERT, /* Vertical */
	DT_WIDE, /* Wide */
};

enum uprop_ea {
	EA_A,  /* Ambiguous */
	EA_F,  /* Fullwidth */
	EA_H,  /* Halfwidth */
	EA_NA, /* Wide */
	EA_N,  /* Neutral */
	EA_W,  /* Narrow */
};

enum [[clang::__flag_enum__]] uprop_gc : uint_least32_t {
	GC_CN = UINT32_C(1) << 0,  /* Not Assigned */
	GC_CC = UINT32_C(1) << 1,  /* Control */
	GC_CF = UINT32_C(1) << 2,  /* Format */
	GC_CO = UINT32_C(1) << 3,  /* Private Use */
	GC_CS = UINT32_C(1) << 4,  /* Surrogate */
	GC_LL = UINT32_C(1) << 5,  /* Lowercase Letter */
	GC_LM = UINT32_C(1) << 6,  /* Modifier Letter */
	GC_LO = UINT32_C(1) << 7,  /* Other Letter */
	GC_LT = UINT32_C(1) << 8,  /* Titlecase Letter */
	GC_LU = UINT32_C(1) << 9,  /* Uppercase Letter */
	GC_MC = UINT32_C(1) << 10, /* Spacing Mark */
	GC_ME = UINT32_C(1) << 11, /* Enclosing Mark */
	GC_MN = UINT32_C(1) << 12, /* Nonspacing Mark */
	GC_ND = UINT32_C(1) << 13, /* Decimal Number */
	GC_NL = UINT32_C(1) << 14, /* Letter Number */
	GC_NO = UINT32_C(1) << 15, /* Other Number */
	GC_PC = UINT32_C(1) << 16, /* Connector Punctuation */
	GC_PD = UINT32_C(1) << 17, /* Dash Punctuation */
	GC_PE = UINT32_C(1) << 18, /* Close Punctuation */
	GC_PF = UINT32_C(1) << 19, /* Final Punctuation */
	GC_PI = UINT32_C(1) << 20, /* Initial Punctuation */
	GC_PO = UINT32_C(1) << 21, /* Other Punctuation */
	GC_PS = UINT32_C(1) << 22, /* Open Punctuation */
	GC_SC = UINT32_C(1) << 23, /* Currency Symbol */
	GC_SK = UINT32_C(1) << 24, /* Modifier Symbol */
	GC_SM = UINT32_C(1) << 25, /* Math Symbol */
	GC_SO = UINT32_C(1) << 26, /* Other Symbol */
	GC_ZL = UINT32_C(1) << 27, /* Line Separator */
	GC_ZP = UINT32_C(1) << 28, /* Paragraph Separator */
	GC_ZS = UINT32_C(1) << 29, /* Space Separator */

	/* Punctuation */
	GC_P = GC_PC | GC_PD | GC_PE | GC_PF | GC_PI | GC_PO | GC_PS,
	GC_C = GC_CC | GC_CF | GC_CN | GC_CO | GC_CS, /* Other */
	GC_LC = GC_LU | GC_LL | GC_LT,                /* Cased Letter */
	GC_L = GC_LL | GC_LM | GC_LO | GC_LT | GC_LU, /* Letter */
	GC_M = GC_MC | GC_ME | GC_MN,                 /* Mark */
	GC_N = GC_ND | GC_NL | GC_NO,                 /* Number */
	GC_S = GC_SC | GC_SK | GC_SM | GC_SO,         /* Symbol */
	GC_Z = GC_ZL | GC_ZP | GC_ZS,                 /* Separator */
};

enum uprop_lb {
	LB_XX,  /* Unknown */
	LB_AI,  /* Ambiguous */
	LB_AK,  /* Aksara */
	LB_AL,  /* Alphabetic */
	LB_AP,  /* Aksara Prebase */
	LB_AS,  /* Aksara Start */
	LB_B2,  /* Break Both */
	LB_BA,  /* Break After */
	LB_BB,  /* Break Before */
	LB_BK,  /* Mandatory Break */
	LB_CB,  /* Contingent Break */
	LB_CJ,  /* Conditional Japanese_Starter */
	LB_CL,  /* Close Punctuation */
	LB_CM,  /* Combining Mark */
	LB_CP,  /* Close Parenthesis */
	LB_CR,  /* Carriage Return */
	LB_EB,  /* E Base */
	LB_EM,  /* E Modifier */
	LB_EX,  /* Exclamation */
	LB_GL,  /* Glue */
	LB_H2,  /* H2 */
	LB_H3,  /* H3 */
	LB_HL,  /* Hebrew Letter */
	LB_HY,  /* Hyphen */
	LB_ID,  /* Ideographic */
	LB_IN,  /* Inseparable */
	LB_IS,  /* Infix Numeric */
	LB_JL,  /* JL */
	LB_JT,  /* JT */
	LB_JV,  /* JV */
	LB_LF,  /* Line Feed */
	LB_NL,  /* Next Line */
	LB_NS,  /* Nonstarter */
	LB_NU,  /* Numeric */
	LB_OP,  /* Open Punctuation */
	LB_PO,  /* Postfix Numeric */
	LB_PR,  /* Prefix Numeric */
	LB_QU,  /* Quotation */
	LB_RI,  /* Regional Indicator */
	LB_SA,  /* Complex Context */
	LB_SG,  /* Surrogate */
	LB_SP,  /* Space */
	LB_SY,  /* Break Symbols */
	LB_VF,  /* Virama Final */
	LB_VI,  /* Virama */
	LB_WJ,  /* Word Joiner */
	LB_ZWJ, /* ZWJ */
	LB_ZW,  /* ZWSpace */
};

enum uprop_nt {
	NT_NONE, /* None */
	NT_DE,   /* Decimal */
	NT_DI,   /* Digit */
	NT_NU,   /* Numeric */
};

enum uprop_sc {
	SC_ZZZZ = 0, /* Unknown */
	SC_ADLM,     /* Adlam */
	SC_AGHB,     /* Caucasian Albanian */
	SC_AHOM,     /* Ahom */
	SC_ARAB,     /* Arabic */
	SC_ARMI,     /* Imperial Aramaic */
	SC_ARMN,     /* Armenian */
	SC_AVST,     /* Avestan */
	SC_BALI,     /* Balinese */
	SC_BAMU,     /* Bamum */
	SC_BASS,     /* Bassa Vah */
	SC_BATK,     /* Batak */
	SC_BENG,     /* Bengali */
	SC_BHKS,     /* Bhaiksuki */
	SC_BOPO,     /* Bopomofo */
	SC_BRAH,     /* Brahmi */
	SC_BRAI,     /* Braille */
	SC_BUGI,     /* Buginese */
	SC_BUHD,     /* Buhid */
	SC_CAKM,     /* Chakma */
	SC_CANS,     /* Canadian Aboriginal */
	SC_CARI,     /* Carian */
	SC_CHAM,     /* Cham */
	SC_CHER,     /* Cherokee */
	SC_CHRS,     /* Chorasmian */
	SC_COPT,     /* Coptic */
	SC_CPMN,     /* Cypro Minoan */
	SC_CPRT,     /* Cypriot */
	SC_CYRL,     /* Cyrillic */
	SC_DEVA,     /* Devanagari */
	SC_DIAK,     /* Dives Akuru */
	SC_DOGR,     /* Dogra */
	SC_DSRT,     /* Deseret */
	SC_DUPL,     /* Duployan */
	SC_EGYP,     /* Egyptian Hieroglyphs */
	SC_ELBA,     /* Elbasan */
	SC_ELYM,     /* Elymaic */
	SC_ETHI,     /* Ethiopic */
	SC_GEOR,     /* Georgian */
	SC_GLAG,     /* Glagolitic */
	SC_GONG,     /* Gunjala Gondi */
	SC_GONM,     /* Masaram Gondi */
	SC_GOTH,     /* Gothic */
	SC_GRAN,     /* Grantha */
	SC_GREK,     /* Greek */
	SC_GUJR,     /* Gujarati */
	SC_GURU,     /* Gurmukhi */
	SC_HANG,     /* Hangul */
	SC_HANI,     /* Han */
	SC_HANO,     /* Hanunoo */
	SC_HATR,     /* Hatran */
	SC_HEBR,     /* Hebrew */
	SC_HIRA,     /* Hiragana */
	SC_HLUW,     /* Anatolian Hieroglyphs */
	SC_HMNG,     /* Pahawh Hmong */
	SC_HMNP,     /* Nyiakeng Puachue Hmong */
	SC_HRKT,     /* Katakana or Hiragana */
	SC_HUNG,     /* Old Hungarian */
	SC_ITAL,     /* Old Italic */
	SC_JAVA,     /* Javanese */
	SC_KALI,     /* Kayah Li */
	SC_KANA,     /* Katakana */
	SC_KAWI,     /* Kawi */
	SC_KHAR,     /* Kharoshthi */
	SC_KHMR,     /* Khmer */
	SC_KHOJ,     /* Khojki */
	SC_KITS,     /* Khitan Small Script */
	SC_KNDA,     /* Kannada */
	SC_KTHI,     /* Kaithi */
	SC_LANA,     /* Tai Tham */
	SC_LAOO,     /* Lao */
	SC_LATN,     /* Latin */
	SC_LEPC,     /* Lepcha */
	SC_LIMB,     /* Limbu */
	SC_LINA,     /* Linear-A */
	SC_LINB,     /* Linear-B */
	SC_LISU,     /* Lisu */
	SC_LYCI,     /* Lycian */
	SC_LYDI,     /* Lydian */
	SC_MAHJ,     /* Mahajani */
	SC_MAKA,     /* Makasar */
	SC_MAND,     /* Mandaic */
	SC_MANI,     /* Manichaean */
	SC_MARC,     /* Marchen */
	SC_MEDF,     /* Medefaidrin */
	SC_MEND,     /* Mende Kikakui */
	SC_MERC,     /* Meroitic Cursive */
	SC_MERO,     /* Meroitic Hieroglyphs */
	SC_MLYM,     /* Malayalam */
	SC_MODI,     /* Modi */
	SC_MONG,     /* Mongolian */
	SC_MROO,     /* Mro */
	SC_MTEI,     /* Meetei Mayek */
	SC_MULT,     /* Multani */
	SC_MYMR,     /* Myanmar */
	SC_NAGM,     /* Nag Mundari */
	SC_NAND,     /* Nandinagari */
	SC_NARB,     /* Old North Arabian */
	SC_NBAT,     /* Nabataean */
	SC_NEWA,     /* Newa */
	SC_NKOO,     /* Nko */
	SC_NSHU,     /* Nushu */
	SC_OGAM,     /* Ogham */
	SC_OLCK,     /* Ol Chiki */
	SC_ORKH,     /* Old Turkic */
	SC_ORYA,     /* Oriya */
	SC_OSGE,     /* Osage */
	SC_OSMA,     /* Osmanya */
	SC_OUGR,     /* Old Uyghur */
	SC_PALM,     /* Palmyrene */
	SC_PAUC,     /* Pau Cin Hau */
	SC_PERM,     /* Old Permic */
	SC_PHAG,     /* Phags Pa */
	SC_PHLI,     /* Inscriptional Pahlavi */
	SC_PHLP,     /* Psalter Pahlavi */
	SC_PHNX,     /* Phoenician */
	SC_PLRD,     /* Miao */
	SC_PRTI,     /* Inscriptional Parthian */
	SC_RJNG,     /* Rejang */
	SC_ROHG,     /* Hanifi Rohingya */
	SC_RUNR,     /* Runic */
	SC_SAMR,     /* Samaritan */
	SC_SARB,     /* Old South Arabian */
	SC_SAUR,     /* Saurashtra */
	SC_SGNW,     /* SignWriting */
	SC_SHAW,     /* Shavian */
	SC_SHRD,     /* Sharada */
	SC_SIDD,     /* Siddham */
	SC_SIND,     /* Khudawadi */
	SC_SINH,     /* Sinhala */
	SC_SOGD,     /* Sogdian */
	SC_SOGO,     /* Old Sogdian */
	SC_SORA,     /* Sora Sompeng */
	SC_SOYO,     /* Soyombo */
	SC_SUND,     /* Sundanese */
	SC_SYLO,     /* Syloti Nagri */
	SC_SYRC,     /* Syriac */
	SC_TAGB,     /* Tagbanwa */
	SC_TAKR,     /* Takri */
	SC_TALE,     /* Tai Le */
	SC_TALU,     /* New Tai Lue */
	SC_TAML,     /* Tamil */
	SC_TANG,     /* Tangut */
	SC_TAVT,     /* Tai Viet */
	SC_TELU,     /* Telugu */
	SC_TFNG,     /* Tifinagh */
	SC_TGLG,     /* Tagalog */
	SC_THAA,     /* Thaana */
	SC_THAI,     /* Thai */
	SC_TIBT,     /* Tibetan */
	SC_TIRH,     /* Tirhuta */
	SC_TNSA,     /* Tangsa */
	SC_TOTO,     /* Toto */
	SC_UGAR,     /* Ugaritic */
	SC_VAII,     /* Vai */
	SC_VITH,     /* Vithkuqi */
	SC_WARA,     /* Warang Citi */
	SC_WCHO,     /* Wancho */
	SC_XPEO,     /* Old Persian */
	SC_XSUX,     /* Cuneiform */
	SC_YEZI,     /* Yezidi */
	SC_YIII,     /* Yi */
	SC_ZANB,     /* Zanabazar Square */
	SC_ZINH,     /* Inherited */
	SC_ZYYY,     /* Common */
};

/* Not a Unicode property; but a nice-to-have */
[[__mlib_uprop_attrs]] struct u8view uprop_blkname(enum uprop_blk);

[[__mlib_uprop_attrs]] double uprop_get_nv(rune);
[[__mlib_uprop_attrs]] enum uprop_age uprop_get_age(rune);
[[__mlib_uprop_attrs]] enum uprop_blk uprop_get_blk(rune);
[[__mlib_uprop_attrs]] enum uprop_bpt uprop_get_bpt(rune);
[[__mlib_uprop_attrs]] enum uprop_dt uprop_get_dt(rune);
[[__mlib_uprop_attrs]] enum uprop_ea uprop_get_ea(rune);
[[__mlib_uprop_attrs]] enum uprop_gc uprop_get_gc(rune);
[[__mlib_uprop_attrs]] enum uprop_lb uprop_get_lb(rune);
[[__mlib_uprop_attrs]] enum uprop_nt uprop_get_nt(rune);
[[__mlib_uprop_attrs]] enum uprop_sc uprop_get_sc(rune);
[[__mlib_uprop_attrs]] rune uprop_get_bpb(rune);
[[__mlib_uprop_attrs]] rune uprop_get_slc(rune);
[[__mlib_uprop_attrs]] rune uprop_get_stc(rune);
[[__mlib_uprop_attrs]] rune uprop_get_suc(rune);
[[__mlib_uprop_attrs]] struct rview uprop_get_lc(rune, struct lcctx);
[[__mlib_uprop_attrs]] struct rview uprop_get_tc(rune, struct tcctx);
[[__mlib_uprop_attrs]] struct rview uprop_get_uc(rune, struct ucctx);
[[__mlib_uprop_attrs]] struct u8view uprop_get_na1(rune);
[[__mlib_uprop_attrs]] struct u8view uprop_get_na(rune);

/* PROP PREDICATES START */
[[__mlib_uprop_attrs]] bool uprop_is_ahex(rune);
[[__mlib_uprop_attrs]] bool uprop_is_alpha(rune);
[[__mlib_uprop_attrs]] bool uprop_is_bidi_c(rune);
[[__mlib_uprop_attrs]] bool uprop_is_bidi_m(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cased(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ci(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwcf(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwcm(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwkcf(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwl(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwt(rune);
[[__mlib_uprop_attrs]] bool uprop_is_cwu(rune);
[[__mlib_uprop_attrs]] bool uprop_is_dash(rune);
[[__mlib_uprop_attrs]] bool uprop_is_dep(rune);
[[__mlib_uprop_attrs]] bool uprop_is_di(rune);
[[__mlib_uprop_attrs]] bool uprop_is_dia(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ebase(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ecomp(rune);
[[__mlib_uprop_attrs]] bool uprop_is_emod(rune);
[[__mlib_uprop_attrs]] bool uprop_is_emoji(rune);
[[__mlib_uprop_attrs]] bool uprop_is_epres(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ext(rune);
[[__mlib_uprop_attrs]] bool uprop_is_extpic(rune);
[[__mlib_uprop_attrs]] bool uprop_is_gr_base(rune);
[[__mlib_uprop_attrs]] bool uprop_is_gr_ext(rune);
[[__mlib_uprop_attrs]] bool uprop_is_hex(rune);
[[__mlib_uprop_attrs]] bool uprop_is_id_compat_math_continue(rune);
[[__mlib_uprop_attrs]] bool uprop_is_id_compat_math_start(rune);
[[__mlib_uprop_attrs]] bool uprop_is_idc(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ideo(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ids(rune);
[[__mlib_uprop_attrs]] bool uprop_is_idsb(rune);
[[__mlib_uprop_attrs]] bool uprop_is_incb(rune);
[[__mlib_uprop_attrs]] bool uprop_is_loe(rune);
[[__mlib_uprop_attrs]] bool uprop_is_lower(rune);
[[__mlib_uprop_attrs]] bool uprop_is_math(rune);
[[__mlib_uprop_attrs]] bool uprop_is_pat_syn(rune);
[[__mlib_uprop_attrs]] bool uprop_is_pat_ws(rune);
[[__mlib_uprop_attrs]] bool uprop_is_pcm(rune);
[[__mlib_uprop_attrs]] bool uprop_is_qmark(rune);
[[__mlib_uprop_attrs]] bool uprop_is_radical(rune);
[[__mlib_uprop_attrs]] bool uprop_is_sd(rune);
[[__mlib_uprop_attrs]] bool uprop_is_sterm(rune);
[[__mlib_uprop_attrs]] bool uprop_is_term(rune);
[[__mlib_uprop_attrs]] bool uprop_is_uideo(rune);
[[__mlib_uprop_attrs]] bool uprop_is_upper(rune);
[[__mlib_uprop_attrs]] bool uprop_is_vs(rune);
[[__mlib_uprop_attrs]] bool uprop_is_wspace(rune);
[[__mlib_uprop_attrs]] bool uprop_is_xidc(rune);
[[__mlib_uprop_attrs]] bool uprop_is_xids(rune);
/* PROP PREDICATES END */

/* Manually implemented predicates */
[[__mlib_uprop_attrs]] bool uprop_is_idst(rune);
[[__mlib_uprop_attrs]] bool uprop_is_idsu(rune);
[[__mlib_uprop_attrs]] bool uprop_is_join_c(rune);
[[__mlib_uprop_attrs]] bool uprop_is_nchar(rune);
[[__mlib_uprop_attrs]] bool uprop_is_ri(rune);

#endif /* !MLIB_UNICODE_PROP_H */
