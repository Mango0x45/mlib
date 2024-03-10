#ifndef MLIB_OPTPARSE_H
#define MLIB_OPTPARSE_H

#include <stddef.h>

#include "__charN_t.h"
#include "__rune.h"
#include "__u8view.h"

struct optparse {
	int optind, subopt;
	char errmsg[128];
	char **argv;
	struct u8view optarg;
};

enum op_argkind {
	OPT_NONE,
	OPT_OPT,
	OPT_REQ,
};

struct op_option {
	rune shortopt;
	const char8_t *longopt;
	enum op_argkind argtype;
};

rune optparse(struct optparse *, const struct op_option *, size_t);
void optparse_init(struct optparse *, char **);

#endif /* !MLIB_OPTPARSE_H */
