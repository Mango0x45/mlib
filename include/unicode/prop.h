#ifndef MLIB_UNICODE_PROP_H
#define MLIB_UNICODE_PROP_H

#include <inttypes.h>

#include "__rune.h"
#include "__u8view.h"

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

enum [[clang::__flag_enum__]] uprop_gc : uint_fast32_t {
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

[[__nodiscard__, __unsequenced__]] double uprop_get_nv(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_bpt uprop_get_bpt(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_dt uprop_get_dt(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_ea uprop_get_ea(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_gc uprop_get_gc(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_lb uprop_get_lb(rune);
[[__nodiscard__, __unsequenced__]] enum uprop_nt uprop_get_nt(rune);
[[__nodiscard__, __unsequenced__]] rune uprop_get_bpb(rune);
[[__nodiscard__, __unsequenced__]] rune uprop_get_slc(rune);
[[__nodiscard__, __unsequenced__]] rune uprop_get_stc(rune);
[[__nodiscard__, __unsequenced__]] rune uprop_get_suc(rune);
[[__nodiscard__, __unsequenced__]] struct u8view uprop_get_na1(rune);
[[__nodiscard__, __unsequenced__]] struct u8view uprop_get_na(rune);

/* PROP PREDICATES START */
[[__nodiscard__, __unsequenced__]] bool uprop_is_ahex(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_alpha(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_bidi_c(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_bidi_m(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cased(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ci(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwcf(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwcm(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwkcf(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwl(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwt(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_cwu(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_dash(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_dep(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_di(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_dia(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ebase(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ecomp(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_emod(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_emoji(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_epres(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ext(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_extpic(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_gr_base(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_gr_ext(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_hex(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_id_compat_math_continue(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_id_compat_math_start(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_idc(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ideo(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ids(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_idsb(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_incb(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_loe(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_lower(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_math(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_pat_syn(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_pat_ws(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_pcm(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_qmark(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_radical(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_sd(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_sterm(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_term(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_uideo(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_upper(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_vs(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_wspace(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_xidc(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_xids(rune);
/* PROP PREDICATES END */

/* Manually implemented predicates */
[[__nodiscard__, __unsequenced__]] bool uprop_is_idst(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_idsu(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_join_c(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_nchar(rune);
[[__nodiscard__, __unsequenced__]] bool uprop_is_ri(rune);

#endif /* !MLIB_UNICODE_PROP_H */
