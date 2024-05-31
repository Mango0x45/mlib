#if 0
cd "${0%/*}/../.."
trap 'rm -f /tmp/wdth' EXIT
cc -Iinclude -std=c23 -Wno-attributes -fsanitize=address,undefined \
	-lunistring -o /tmp/wdth gen/prop/wdth.c libmlib.a
/tmp/wdth
exit 0
#endif

/* Cheating slightly because I am lazy; using libunistring to figure out the
   values here */

#include <stdio.h>
#include <stdlib.h>

#include <rune.h>
#include <uniwidth.h>

int
main(void)
{
	for (ucs4_t ch = 0; ch <= RUNE_MAX; ch++)
		printf("%04" PRIXRUNE " %d\n", ch, uc_width(ch, "UTF-8"));
	return EXIT_SUCCESS;
}
