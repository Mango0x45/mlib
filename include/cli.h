#ifndef MLIB_CLI_H
#define MLIB_CLI_H

#include <stddef.h>

#include "_attrs.h"
#include "_rune.h"
#include "_uNview.h"

typedef struct {
	bool _b;
	int _subopt;
	char **_argv;

	int optind;
	char errmsg[128];
	u8view_t optarg;
} optparser_t;

typedef enum {
	CLI_NONE,
	CLI_OPT,
	CLI_REQ,
} cli_opt_kind_t;

typedef struct {
	rune shortopt;
	u8view_t longopt;
	cli_opt_kind_t argtype;
} cli_opt_t;

[[nodiscard]] rune optparse(optparser_t *, const cli_opt_t *, size_t);

[[_mlib_inline]]
static inline optparser_t
mkoptparser(char **argv)
{
	return (optparser_t){
		._argv = argv,
		.optind = argv[0] != nullptr,
	};
}

#endif /* !MLIB_CLI_H */
