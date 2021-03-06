#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char HTOA_TABLE[] = "0123456789ABCDEF";

char *htoa(u32 n)
{
	char *ret = (char *)malloc(10);

	int i = 0;
	while (n) {
		ret[i++] = HTOA_TABLE[n & 0xF];
		n >>= 4;
	}

	if (!i) {
		ret[0] = '0';
		i++;
	}

	for (; i <= 9; i++)
		ret[i] = 0;

	char *aux = strdup(ret);
	free(ret);
	ret = aux;

	strinv(ret);
	return ret;
}