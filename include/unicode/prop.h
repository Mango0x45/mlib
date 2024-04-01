#ifndef MLIB_UNICODE_PROP_H
#define MLIB_UNICODE_PROP_H

#include <inttypes.h>

#include "__rune.h"

enum [[clang::flag_enum]] uprop_gc : uint_fast32_t {
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

enum uprop_gc uprop_get_gc(rune);

#endif /* !MLIB_UNICODE_PROP_H */
