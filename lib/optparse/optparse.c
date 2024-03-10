#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "mbstring.h"
#include "optparse.h"

#define OPT_MSG_INVALID "invalid option"
#define OPT_MSG_MISSING "option requires an argument"
#define OPT_MSG_TOOMANY "option takes no arguments"

#define IS_SHORTOPT(s) ((s)[0] == '-' && (s)[1] != '-' && (s)[1] != '\0')
#define IS_LONGOPT(s)  ((s)[0] == '-' && (s)[1] == '-' && (s)[2] != '\0')

#define error(st, msg, x) \
	_Generic((x), const char *: error_s, rune: error_r)((st), (msg), (x))

static bool is_a_match(const char *, const char *);
static rune error_r(struct optparse *, const char *, rune);
static rune error_s(struct optparse *, const char *, const char *);
static rune shortopt(struct optparse *, const struct op_option *, size_t);

struct optparse
mkoptparser(char **argv)
{
	return (struct optparse){
		._argv = argv,
		.optind = argv[0] != nullptr,
	};
}

rune
optparse(struct optparse *st, const struct op_option *opts, size_t nopts)
{
	st->errmsg[0] = '\0';
	st->optarg = (struct u8view){};

	const char *opt = st->_argv[st->optind];
	if (opt == nullptr)
		return 0;
	if (streq(opt, "--")) {
		st->optind++;
		return 0;
	}
	if (IS_SHORTOPT(opt))
		return shortopt(st, opts, nopts);
	if (!IS_LONGOPT(opt))
		return 0;

	st->_subopt = 0;
	st->optind++;
	opt += 2; /* Skip ‘--’ */

	for (size_t i = 0; i < nopts; i++) {
		struct op_option o = opts[i];
		if (!is_a_match(opt, o.longopt))
			continue;
		switch (o.argtype) {
		case OPT_NONE:
			if (strchr(opt, '=') != nullptr)
				return error(st, OPT_MSG_TOOMANY, opt);
			break;
		case OPT_REQ: {
			const char *p = strchr(opt, '=');
			if (p == nullptr) {
				if (st->_argv[st->optind] == nullptr)
					return error(st, OPT_MSG_MISSING, opt);
				st->optarg.p = st->_argv[st->optind++];
			} else
				st->optarg.p = p + 1;
			st->optarg.len = strlen(st->optarg.p);
		} break;
		case OPT_OPT: {
			const char *p = strchr(opt, '=');
			if (p == nullptr)
				st->optarg = (struct u8view){};
			else {
				st->optarg.p = p + 1;
				st->optarg.len = strlen(st->optarg.p);
			}
		} break;
		}
		return o.shortopt;
	}

	return error(st, OPT_MSG_INVALID, opt);
}

rune
shortopt(struct optparse *st, const struct op_option *opts, size_t nopts)
{
	rune ch;
	const char *opt = st->_argv[st->optind];
	st->_subopt += u8tor(&ch, opt + st->_subopt + 1);
	if (ch == '\0') {
		st->_subopt = 0;
		st->optind++;
		return optparse(st, opts, nopts);
	}
	for (size_t i = 0; i < nopts; i++) {
		if (opts[i].shortopt != ch)
			continue;
		if (opts[i].argtype == OPT_NONE)
			goto out;
		if (opt[st->_subopt + 1] != '\0') {
			st->optarg.p = opt + st->_subopt + 1;
			st->optarg.len = strlen(st->optarg.p);
			st->_subopt = 0;
			st->optind++;
			goto out;
		}
		if (opts[i].argtype == OPT_OPT) {
			st->optarg = (struct u8view){};
			goto out;
		}
		if (st->_argv[st->optind + 1] == nullptr) {
			st->optarg = (struct u8view){};
			return error(st, OPT_MSG_MISSING, ch);
		}
		st->optarg.p = st->_argv[st->optind + 1];
		st->optarg.len = strlen(st->optarg.p);
		st->optind += 2;
		goto out;
	}
	return error(st, OPT_MSG_INVALID, ch);
out:
	return ch;
}

bool
is_a_match(const char *u, const char *t)
{
	for (; *u && *t && *u != '='; u++, t++) {
		if (*u != *t)
			return false;
	}
	return *t == '\0' && (*u == '\0' || *u == '=');
}

rune
error_s(struct optparse *st, const char *msg, const char *s)
{
	const char *p = strchr(s, '=');
	snprintf(st->errmsg, sizeof(st->errmsg), u8"%s — ‘%.*s’", msg,
	         (int)(p ? p - s : strlen(s)), s);
	return -1;
}

rune
error_r(struct optparse *st, const char *msg, rune ch)
{
	char buf[U8_LEN_MAX + 1] = {};
	rtou8(buf, ch, sizeof(buf));
	return error_s(st, msg, buf);
}
