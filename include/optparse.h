#ifndef MLIB_OPTPARSE_H
#define MLIB_OPTPARSE_H

#include <stddef.h>

#include "__charN_t.h"
#include "__rune.h"
#include "__u8view.h"
#include "_attrs.h"

struct optparse {
	bool _b;
	int _subopt;
	char **_argv;

	int optind;
	char errmsg[128];
	struct u8view optarg;
};

enum op_argkind {
	OPT_NONE,
	OPT_OPT,
	OPT_REQ,
};

struct op_option {
	rune shortopt;
	struct u8view longopt;
	enum op_argkind argtype;
};

[[nodiscard]] rune optparse(struct optparse *, const struct op_option *,
                            size_t);

[[_mlib_inline]]
static inline struct optparse
mkoptparser(char **argv)
{
	return (struct optparse){
		._argv = argv,
		.optind = argv[0] != nullptr,
	};
}

#endif /* !MLIB_OPTPARSE_H */
