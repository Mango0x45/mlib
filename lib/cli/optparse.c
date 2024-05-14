#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "macros.h"
#include "mbstring.h"

#define CLI_MSG_INVALID "invalid option"
#define CLI_MSG_MISSING "option requires an argument"
#define CLI_MSG_TOOMANY "option takes no arguments"

#define IS_DASHDASH(s) ((s).len == 2 && (s).p[0] == '-' && (s).p[1] == '-')
#define IS_LONGOPT(s)  ((s).len >= 3 && (s).p[0] == '-' && (s).p[1] == '-')
#define IS_SHORTOPT(s) ((s).len >= 2 && (s).p[0] == '-' && (s).p[1] != '-')

#define error(st, msg, x)                                                      \
	_Generic((x), struct u8view: error_s, rune: error_r)((st), (msg), (x))

static rune error_r(struct optparser *, const char *, rune);
static rune error_s(struct optparser *, const char *, struct u8view);
static rune shortopt(struct optparser *, const struct cli_option *, size_t);

rune
optparse(struct optparser *st, const struct cli_option *opts, size_t nopts)
{
	st->errmsg[0] = '\0';
	st->optarg = (struct u8view){};

	struct u8view opt = {.p = st->_argv[st->optind]};
	if (opt.p == nullptr)
		return 0;
	opt.len = strlen(opt.p);

	if (IS_DASHDASH(opt)) {
		st->optind++;
		return 0;
	}
	if (IS_SHORTOPT(opt))
		return shortopt(st, opts, nopts);
	if (!IS_LONGOPT(opt))
		return 0;

	st->_subopt = 0;
	st->optind++;

	/* Skip ‘--’ */
	VSHFT(&opt, 2);

	const struct cli_option *o = nullptr;
	const char8_t *eq_p = u8chr(opt, '=');
	struct u8view opt_no_eq = {
		.p = opt.p,
		.len = eq_p == nullptr ? opt.len : (size_t)(eq_p - opt.p),
	};

	for (size_t i = 0; i < nopts; i++) {
		struct u8view lo = opts[i].longopt;
		if (lo.p == nullptr || !u8haspfx(lo, opt_no_eq))
			continue;
		if (o != nullptr)
			return error(st, CLI_MSG_INVALID, opt_no_eq);
		o = opts + i;
	}

	if (o == nullptr)
		return error(st, CLI_MSG_INVALID, opt_no_eq);

	switch (o->argtype) {
	case CLI_NONE:
		if (eq_p != nullptr)
			return error(st, CLI_MSG_TOOMANY, opt);
		break;
	case CLI_OPT:
		if (eq_p == nullptr)
			st->optarg = (struct u8view){};
		else {
			ASSUME(opt.len > opt_no_eq.len);
			st->optarg = (struct u8view){
				.p = eq_p + 1,
				.len = opt.len - opt_no_eq.len + 1,
			};
		}
		break;
	case CLI_REQ:
		if (eq_p == nullptr) {
			if (st->_argv[st->optind] == nullptr)
				return error(st, CLI_MSG_MISSING, opt);
			st->optarg.p = st->_argv[st->optind++];
			st->optarg.len = strlen(st->optarg.p);
		} else {
			ASSUME(opt.len > opt_no_eq.len);
			st->optarg = (struct u8view){
				.p = eq_p + 1,
				.len = opt.len - opt_no_eq.len + 1,
			};
		}
		break;
	}

	return o->shortopt;
}

rune
shortopt(struct optparser *st, const struct cli_option *opts, size_t nopts)
{
	rune ch;
	const char8_t *opt = st->_argv[st->optind];
	st->_subopt += ucstor(&ch, opt + st->_subopt + 1);
	if (ch == '\0') {
		st->_subopt = 0;
		st->optind++;
		return optparse(st, opts, nopts);
	}
	for (size_t i = 0; i < nopts; i++) {
		if (opts[i].shortopt != ch)
			continue;
		if (opts[i].argtype == CLI_NONE)
			goto out;
		if (opt[st->_subopt + 1] != '\0') {
			st->optarg.p = opt + st->_subopt + 1;
			st->optarg.len = strlen(st->optarg.p);
			st->_subopt = 0;
			st->optind++;
			goto out;
		}
		if (opts[i].argtype == CLI_OPT) {
			st->optarg = (struct u8view){};
			goto out;
		}
		if (st->_argv[st->optind + 1] == nullptr) {
			st->optarg = (struct u8view){};
			return error(st, CLI_MSG_MISSING, ch);
		}
		st->optarg.p = st->_argv[st->optind + 1];
		st->optarg.len = strlen(st->optarg.p);
		st->optind += 2;
		goto out;
	}
	return error(st, CLI_MSG_INVALID, ch);
out:
	return ch;
}

rune
error_s(struct optparser *st, const char *msg, struct u8view s)
{
	snprintf(st->errmsg, sizeof(st->errmsg), u8"%s — ‘%.*s’", msg,
	         SV_PRI_ARGS(s));
	return -1;
}

rune
error_r(struct optparser *st, const char *msg, rune ch)
{
	char buf[U8_LEN_MAX + 1] = {};
	snprintf(st->errmsg, sizeof(st->errmsg), u8"%s — ‘%.*s’", msg,
	         rtou8(buf, sizeof(buf), ch), buf);
	return -1;
}
