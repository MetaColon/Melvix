#ifndef MELVIX_STDLIB_H
#define MELVIX_STDLIB_H

#include <stdint.h>

#ifndef MELVIX_STRING_H

#include <lib/string.h>

#endif

char *itoa(int n);
char *itoa_base(int value, char *result, int base, int is_signed);

int atoi(char *str);

char *htoa(u32 n);

int htoi(char *str);

#endif