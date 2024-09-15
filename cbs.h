/*
 * BSD Zero Clause License
 *
 * Copyright © 2023–2024 Thomas Voss
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef C_BUILD_SYSTEM_H
#define C_BUILD_SYSTEM_H

#define _GNU_SOURCE
#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#ifndef CBS_NO_THREADS
#	include <pthread.h>
#endif
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wordexp.h>

#define _vtoxs(...) ((char *[]){__VA_ARGS__})

#define lengthof(xs) (sizeof(xs) / sizeof(*(xs)))

struct strs {
	char **buf;
	size_t len, cap;
};

enum pkg_config_flags {
	PC_CFLAGS = 1 << 0,
	PC_LIBS   = 1 << 1,
	PC_SHARED = 1 << 2,
	PC_STATIC = 1 << 3,
};

static void cbsinit(int, char **);
static void rebuild(const char *); /* Always call via macro wrapper */
#define rebuild() rebuild(__FILE__)

static void strsfree(struct strs *);
static void strszero(struct strs *);
static void strspush(struct strs *, char **, size_t);
static void strspushenv(struct strs *, const char *, char **, size_t);
#define strspushl(xs, ...)                                                     \
	strspush((xs), _vtoxs(__VA_ARGS__), lengthof(_vtoxs(__VA_ARGS__)))
#define strspushenvl(xs, ev, ...)                                              \
	strspushenv((xs), (ev), _vtoxs(__VA_ARGS__), lengthof(_vtoxs(__VA_ARGS__)))

static bool fexists(const char *);
static int  fmdcmp(const char *, const char *);
static bool fmdolder(const char *, const char *);
static bool fmdnewer(const char *, const char *);
static bool foutdated(const char *, char **, size_t);
#define foutdatedl(s, ...)                                                     \
	foutdated((s), _vtoxs(__VA_ARGS__), lengthof(_vtoxs(__VA_ARGS__)))

static int   cmdexec(struct strs);
static pid_t cmdexec_async(struct strs);
static int   cmdexec_read(struct strs, char **, size_t *);
static int   cmdwait(pid_t);
static void  cmdput(struct strs);
static void  cmdfput(FILE *, struct strs);

static char *swpext(const char *, const char *);
static bool  pcquery(struct strs *, const char *, int);
static bool  binexists(const char *);
static int   nproc(void);

#ifndef CBS_NO_THREADS
typedef void tjob(void *);
typedef void tjob_free(void *);

struct _tqueue {
	void *arg;
	tjob *fn;
	tjob_free *free;
	struct _tqueue *next;
};

typedef struct {
	bool stop;
	size_t tcnt, left;
	pthread_t *thrds;
	pthread_cond_t cnd;
	pthread_mutex_t mtx;
	struct _tqueue *head, *tail;
} tpool;

static void tpinit(tpool *, size_t);
static void tpfree(tpool *);
static void tpwait(tpool *);
static void tpenq(tpool *, tjob *, void *, tjob_free *);
#endif /* !CBS_NO_THREADS */

static int    _cbs_argc;
static char **_cbs_argv;

/* Implementation */

#ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wunused-function"
#endif

#ifdef __APPLE__
#	define st_mtim st_mtimespec
#endif

void
cbsinit(int argc, char **argv)
{
	_cbs_argc = argc;
	_cbs_argv = malloc(sizeof(char *) * (argc + 1));
	assert(_cbs_argv != NULL);
	for (int i = 0; i < argc; i++) {
		_cbs_argv[i] = strdup(argv[i]);
		assert(_cbs_argv[i] != NULL);
	}
	_cbs_argv[argc] = NULL;

	char *s = strrchr(_cbs_argv[0], '/');
	if (s != NULL) {
		s[0] = 0;
		assert(chdir(_cbs_argv[0]) != -1);
		s[0] = '/';
	}
}

void
(rebuild)(const char *path)
{
	char *src, *dst;

	if ((src = strrchr(path, '/')) != NULL)
		src++;
	else
		src = (char *)path;

	if ((dst = strrchr(*_cbs_argv, '/')) != NULL)
		dst++;
	else
		dst = *_cbs_argv;

	if (!foutdatedl(dst, src))
		return;

	struct strs xs = {0};
	strspushenvl(&xs, "CC", "cc");
#ifndef CBS_NO_THREADS
	strspushl(&xs, "-lpthread");
#endif
	strspushl(&xs, "-std=c23", "-o", dst, src);
	cmdput(xs);
	assert(cmdexec(xs) == EXIT_SUCCESS);

	execvp(*_cbs_argv, _cbs_argv);
	assert(!"failed to execute process");
}

void
strsfree(struct strs *xs)
{
	free(xs->buf);
	xs->buf = NULL;
	xs->len = xs->cap = 0;
}

void
strszero(struct strs *xs)
{
	xs->len = 0;
	if (xs->cap > 0)
		xs->buf[0] = NULL;
}

void
strspush(struct strs *xs, char **ys, size_t n)
{
	if (n == 0)
		return;

	if (xs->len + n >= xs->cap) {
		xs->cap = (xs->len + n) * 2;
		xs->buf = realloc(xs->buf, sizeof(char *) * (xs->cap + 1));
		assert(xs->buf != NULL);
	}
	memcpy(xs->buf + xs->len, ys, n * sizeof(char *));
	xs->len += n;

	assert(xs->len <= xs->cap);
	xs->buf[xs->len] = NULL;
}

void
strspushenv(struct strs *xs, const char *ev, char **ys, size_t n)
{
	/* NOTE: Do your best to NOT modify any pushed envvar! */
	char *p = getenv(ev);
	if (p == NULL || *p == 0) {
		strspush(xs, ys, n);
		return;
	}

	wordexp_t we;
	assert(wordexp(p, &we, WRDE_NOCMD) == 0);

	/* TODO: Memory leak! */
	for (size_t i = 0; i < we.we_wordc; i++) {
		char *w = strdup(we.we_wordv[i]);
		assert(w != NULL);
		strspushl(xs, w);
	}

	wordfree(&we);
}

bool
fexists(const char *f)
{
	return !access(f, F_OK);
}

int
fmdcmp(const char *lhs, const char *rhs)
{
	int errnol, errnor;
	struct stat sbl, sbr;

	stat(lhs, &sbl); errnol = errno; errno = 0;
	stat(rhs, &sbr); errnor = errno;

	assert(errnol == 0 || errnol == ENOENT);
	assert(errnor == 0 || errnor == ENOENT);

	if (errnol == ENOENT && errnor == ENOENT)
		return 0;
	if (errnol == ENOENT)
		return -1;
	if (errnor == ENOENT)
		return +1;

	return sbl.st_mtim.tv_sec == sbr.st_mtim.tv_sec
	     ? sbl.st_mtim.tv_nsec - sbr.st_mtim.tv_nsec
	     : sbl.st_mtim.tv_sec  - sbr.st_mtim.tv_sec;
}

bool
fmdnewer(const char *lhs, const char *rhs)
{
	return fmdcmp(lhs, rhs) > 0;
}

bool
fmdolder(const char *lhs, const char *rhs)
{
	return fmdcmp(lhs, rhs) < 0;
}

bool
foutdated(const char *src, char **deps, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		if (fmdolder(src, deps[i]))
			return true;
	}
	return false;
}

int
cmdexec(struct strs xs)
{
	flockfile(stderr);
	int ret = cmdwait(cmdexec_async(xs));
	funlockfile(stderr);
	return ret;
}

pid_t
cmdexec_async(struct strs xs)
{
	pid_t pid = fork();
	assert(pid != -1);
	if (pid == 0) {
		execvp(xs.buf[0], xs.buf);
		assert(!"failed to execute process");
	}
	return pid;
}

int
cmdexec_read(struct strs xs, char **p, size_t *n)
{
	enum {
		R,
		W,
	};
	int fds[2];

	assert(pipe(fds) != -1);

	pid_t pid = fork();
	assert(pid != -1);

	if (pid == 0) {
		close(fds[R]);
		close(STDOUT_FILENO);
		assert(dup2(fds[W], STDOUT_FILENO) != -1);
		execvp(xs.buf[0], xs.buf);
		assert(!"failed to execute process");
	}

	close(fds[W]);

	struct stat sb;
	assert(fstat(fds[R], &sb) != -1);

	*p = NULL, *n = 0;
	char *buf = malloc(sb.st_blksize);
	assert(buf != NULL);

	for (;;) {
		ssize_t nr;
		if ((nr = read(fds[R], buf, sb.st_blksize)) == 0)
			break;
		assert(nr != -1);

		*p = realloc(*p, *n + nr + 1);
		assert(*p != NULL);

		memcpy(*p + *n, buf, nr);
		*n += nr;
	}

	close(fds[R]);
	free(buf);

	return cmdwait(pid);
}

int
cmdwait(pid_t pid)
{
	int ws;
	assert(waitpid(pid, &ws, 0) != -1);
	if (WIFEXITED(ws))
		return WEXITSTATUS(ws);
	return WIFEXITED(ws) ? WEXITSTATUS(ws) : 256;
}

/*
 * import shlex
 *
 * s = '#define _SHELL_SAFE "'
 * for c in map(chr, range(128)):
 *     if not shlex._find_unsafe(c):
 *         s += c
 * print(s + '"')
 */
#define _SHELL_SAFE                                                            \
	"%+,-./0123456789:=@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"

void
cmdput(struct strs xs)
{
	cmdfput(stdout, xs);
}

void
cmdfput(FILE *fp, struct strs xs)
{
	flockfile(fp);
	for (size_t i = 0; i < xs.len; i++) {
		bool safe = true;
		const char *p = xs.buf[i];

		for (const char *q = p; *q; q++) {
			if (!strchr(_SHELL_SAFE, *q)) {
				safe = false;
				break;
			}
		}

		if (safe)
			fputs(p, fp);
		else {
			putc('\'', fp);
			for (const char *q = p; *q; q++) {
				if (*q == '\'')
					fputs("'\"'\"'", fp);
				else
					putc(*q, fp);
			}
			putc('\'', fp);
		}

		putc(i == xs.len - 1 ? '\n' : ' ', fp);
	}
	funlockfile(fp);
}

bool
pcquery(struct strs *xs, const char *lib, int flags)
{
	struct strs ys = {0};

	strspushl(&ys, "pkg-config", "--silence-errors");
	if (flags & PC_CFLAGS)
		strspushl(&ys, "--cflags");
	if (flags & PC_LIBS)
		strspushl(&ys, "--libs");
	if (flags & PC_SHARED)
		strspushl(&ys, "--shared");
	if (flags & PC_STATIC)
		strspushl(&ys, "--static");
	strspushl(&ys, (char *)lib);

	char *buf;
	size_t bufsz;
	int ec = cmdexec_read(ys, &buf, &bufsz);
	strsfree(&ys);
	if (ec != EXIT_SUCCESS)
		return false;

	/* Remove trailing newline */
	buf[bufsz - 1] = 0;

	wordexp_t we;
	assert(wordexp(buf, &we, WRDE_NOCMD) == 0);

	char **words = malloc(sizeof(char *) * we.we_wordc);
	assert(words != NULL);

	/* TODO: Memory leak! */
	for (size_t i = 0; i < we.we_wordc; i++)
		assert((words[i] = strdup(we.we_wordv[i])) != NULL);

	strspush(xs, words, we.we_wordc);
	wordfree(&we);
	free(words);
	free(buf);
	return true;
}

bool
binexists(const char *s)
{
	const char *path = getenv("PATH");
	assert(path != NULL);

	char *p = strdup(path), *it;
	assert(p != NULL);

	for (it = strtok(p, ":"); it != NULL; it = strtok(NULL, ":")) {
		static char buf[PATH_MAX];
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "%s/%s", it, s);
		if (fexists(buf)) {
			free(p);
			return true;
		}
	}

	free(p);
	return false;
}

int
nproc(void)
{
#ifdef _SC_NPROCESSORS_ONLN
	return (int)sysconf(_SC_NPROCESSORS_ONLN);
#else
	errno = 0;
	return -1;
#endif
}

char *
swpext(const char *file, const char *ext)
{
	const char *p = strrchr(file, '.');
	if (p == NULL) {
		p = strdup(file);
		assert(p != NULL);
		return (char *)p;
	}

	size_t noextlen = p - file;
	char *s = malloc(noextlen + strlen(ext) + 2);
	assert(s != NULL);
	sprintf(s, "%.*s.%s", (int)noextlen, file, ext);
	return s;
}

#ifndef CBS_NO_THREADS
static struct _tqueue *
_tpdeq(tpool *tp)
{
	struct _tqueue *q = tp->head;

	if (q != NULL) {
		tp->head = tp->head->next;
		if (!tp->head)
			tp->tail = NULL;
	}

	return q;
}

static void *
_tpwork(void *arg)
{
	tpool *tp = arg;

	while (!tp->stop) {
		struct _tqueue *q;

		pthread_mutex_lock(&tp->mtx);
		while (!tp->stop && !tp->head)
			pthread_cond_wait(&tp->cnd, &tp->mtx);
		if (tp->stop) {
			pthread_mutex_unlock(&tp->mtx);
			break;
		}

		q = _tpdeq(tp);
		pthread_mutex_unlock(&tp->mtx);

		q->fn(q->arg);
		if (q->free)
			q->free(q->arg);
		free(q);

		pthread_mutex_lock(&tp->mtx);
		tp->left--;
		pthread_cond_broadcast(&tp->cnd);
		pthread_mutex_unlock(&tp->mtx);
	}

	return NULL;
}

void
tpinit(tpool *tp, size_t n)
{
	tp->tcnt = n;
	tp->stop = false;
	tp->left = 0;
	tp->head = tp->tail = NULL;
	tp->thrds = malloc(sizeof(pthread_t) * n);
	assert(tp->thrds != NULL);
	pthread_cond_init(&tp->cnd, NULL);
	pthread_mutex_init(&tp->mtx, NULL);
	for (size_t i = 0; i < n; i++)
		assert(pthread_create(tp->thrds + i, NULL, _tpwork, tp) == 0);
}

void
tpfree(tpool *tp)
{
	tp->stop = true;

	pthread_mutex_lock(&tp->mtx);
	pthread_cond_broadcast(&tp->cnd);
	pthread_mutex_unlock(&tp->mtx);

	for (size_t i = 0; i < tp->tcnt; i++)
		pthread_join(tp->thrds[i], NULL);

	free(tp->thrds);
	while (tp->head != NULL) {
		struct _tqueue *q = _tpdeq(tp);
		if (q->free)
			q->free(q->arg);
		free(q);
	}

	pthread_cond_destroy(&tp->cnd);
	pthread_mutex_destroy(&tp->mtx);
}

void
tpwait(tpool *tp)
{
	pthread_mutex_lock(&tp->mtx);
	while (!tp->stop && tp->left)
		pthread_cond_wait(&tp->cnd, &tp->mtx);
	pthread_mutex_unlock(&tp->mtx);
}

void
tpenq(tpool *tp, tjob *fn, void *arg, tjob_free *free)
{
	struct _tqueue *q = malloc(sizeof(*q));
	assert(q != NULL);
	*q = (struct _tqueue){
		.fn   = fn,
		.arg  = arg,
		.free = free,
	};

	pthread_mutex_lock(&tp->mtx);
	if (tp->tail)
		tp->tail->next = q;
	if (!tp->head)
		tp->head = q;
	tp->tail = q;
	tp->left++;
	pthread_cond_signal(&tp->cnd);
	pthread_mutex_unlock(&tp->mtx);
}
#endif /* !CBS_NO_THREADS */

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif

#ifdef __APPLE__
#	undef st_mtim
#endif

#endif /* !C_BUILD_SYSTEM_H */
