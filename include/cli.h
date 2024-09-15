#ifndef MLIB_CLI_H
#define MLIB_CLI_H

#include <stddef.h>

#include "_attrs.h"
#include "_rune.h"
#include "_uNview.h"

struct optparser {
	bool _b;
	int _subopt;
	char **_argv;

	int optind;
	char errmsg[128];
	u8view_t optarg;
};

enum cliarg {
	CLI_NONE,
	CLI_OPT,
	CLI_REQ,
};

struct cli_option {
	rune shortopt;
	u8view_t longopt;
	enum cliarg argtype;
};

[[nodiscard]] rune optparse(struct optparser *, const struct cli_option *,
                            size_t);

[[_mlib_inline]]
static inline struct optparser
mkoptparser(char **argv)
{
	return (struct optparser){
		._argv = argv,
		.optind = argv[0] != nullptr,
	};
}

#endif /* !MLIB_CLI_H */
