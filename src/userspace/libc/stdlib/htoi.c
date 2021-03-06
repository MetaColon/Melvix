#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int htoi(char *str)
{
	u32 s_str = strlen(str);

	u32 i = 0;
	int ret = 0;
	for (; i < s_str; i++) {
		char c = str[i];
		int aux = 0;
		if (c >= '0' && c <= '9')
			aux = c - '0';
		else if (c >= 'A' && c <= 'F')
			aux = (c - 'A') + 10;

		ret += aux * pow(16, (int)((s_str - i) - 1));
	}

	return ret;
}