#if 0
cd "${0%/*}/../.."
trap 'rm -f /tmp/cm' EXIT
cc -Iinclude -std=c23 -Wno-attributes -fsanitize=address,undefined \
	-o /tmp/cm gen/prop/cm.c libmlib.a
/tmp/cm
exit 0
#endif

#include <assert.h>
#include <inttypes.h>
#include <stdbit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <alloc.h>
#include <dynarr.h>
#include <mbstring.h>
#include <rune.h>
#include <unicode/prop.h>

constexpr int N = 1;

struct mapping {
	uint64_t k;
	rune v;
};

struct ht {
	struct mapping *ht;
	size_t len;
};

static uint32_t lookup(uint64_t, int, uint32_t);
static uint64_t hash(uint64_t);

int
main(void)
{
	dynarr(struct mapping) maps = {.alloc = alloc_heap};

	for (rune ch = 0; ch <= RUNE_MAX; ch++) {
		if (uprop_get_dt(ch) != DT_CAN || uprop_is_comp_ex(ch))
			continue;
		struct rview rv = uprop_get_dm(ch);
		if (rv.len == 1 && rv.p[0] == ch)
			continue;
		assert(rv.len == 2);

		/* Sanity check */
		int n, m;
		char8_t buf[U8_LEN_MAX];
		n = m = 0;
		n += rtoucs(buf, sizeof(buf), rv.p[0]);
		n += rtoucs(buf, sizeof(buf), rv.p[1]);
		m += rtoucs(buf, sizeof(buf), ch);
		assert(n >= m);

		DAPUSH(&maps, ((struct mapping){
			.k = (uint64_t)rv.p[0] << 32 | rv.p[1],
			.v = ch,
		}));
	}

	struct ht t = {};
	size_t sz = (size_t)1 << (SIZE_WIDTH - stdc_leading_zeros(maps.len) + N);
	int e = stdc_trailing_zeros(sz);
	t.ht = bufalloc(nullptr, sizeof(*t.ht), sz);
	memset(t.ht, 0, sizeof(*t.ht) * sz);
	assert(sz == ((size_t)1 << e));

	/* Build up hashtable */
	da_foreach (maps, m) {
		uint64_t h = hash(m->k);
		uint32_t i = h;
		for (;;) {
			i = lookup(h, e, i);
			if (t.ht[i].k == 0) {
				t.ht[i] = *m;
				t.len++;
				break;
			}
		}
	}

	stdout = fopen("include/unicode/_cm.h", "w");
	assert(stdout != nullptr);

	puts("/* This file is autogenerated by gen/prop/cm.c; DO NOT EDIT. */\n");
	puts("#include <inttypes.h>\n\n"
	     "#include \"_attrs.h\"\n"
	     "#include \"rune.h\"\n");
	printf("constexpr int HT_EXP = %d;\n\n", e);
	puts("static const struct {\n"
	     "\tuint64_t k;\n"
	     "\trune v;\n"
	     "} uprop_cm_ht[] = {");

	for (size_t i = 0; i < sz; i++) {
		if (t.ht[i].k != 0) {
			printf("\t[%4zu] = {UINT64_C(0x%016" PRIX64
			       "), RUNE_C(0x%06" PRIXRUNE ")},\n",
			       i, t.ht[i].k, t.ht[i].v);
		}
	}

	puts("};\n");

	puts("[[_mlib_pure, _mlib_inline]]\n"
	     "static uint64_t\n"
	     "hash(uint64_t x)\n"
	     "{\n"
	     "\tx ^= x >> 30;\n"
	     "\tx *= 0xbf58476d1ce4e5b9U;\n"
	     "\tx ^= x >> 27;\n"
	     "\tx *= 0x94d049bb133111ebU;\n"
	     "\tx ^= x >> 31;\n"
	     "\treturn x;\n"
	     "}\n");

	puts("[[_mlib_pure, _mlib_inline]]\n"
	     "static unsigned int\n"
	     "lookup(uint64_t hash, unsigned int idx)\n"
	     "{\n"
	     "\tunsigned int mask = (1U << HT_EXP) - 1;\n"
	     "\tunsigned int step = (hash >> (64 - HT_EXP)) | 1;\n"
	     "\treturn (idx + step) & mask;\n"
	     "}\n");

	puts("static rune\n"
	     "uprop_get_cm(rune a, rune b)\n"
	     "{\n"
	     "\tuint64_t k, h;\n"
	     "\tk = (uint64_t)a << 32 | b;\n"
	     "\th = hash(k);\n"
	     "\tfor (unsigned int i = h;;) {\n"
	     "\t\ti = lookup(h, i);\n"
	     "\t\tauto e = uprop_cm_ht[i];\n"
	     "\t\tif (e.k == 0 || e.k == k)\n"
	     "\t\t\treturn e.v;\n"
	     "\t}\n"
	     "}");

	free(t.ht);
	free(maps.buf);
}

uint32_t
lookup(uint64_t hash, int exp, uint32_t idx)
{
	uint32_t mask = ((uint32_t)1 << exp) - 1;
	uint32_t step = (hash >> (64 - exp)) | 1;
	return (idx + step) & mask;
}

uint64_t
hash(uint64_t x)
{
	x ^= x >> 30;
	x *= 0xbf58476d1ce4e5b9U;
	x ^= x >> 27;
	x *= 0x94d049bb133111ebU;
	x ^= x >> 31;
	return x;
}