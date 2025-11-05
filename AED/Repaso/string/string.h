#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <stddef.h>
#include <stdio.h>

#define ABS(x) ((x)>=0?(x):-(x))

size_t strlen(const char* str);
void readStr(char* str, size_t len, FILE* iostream);
void intToStr(char* str, int num);
int parseInt(const char* str);

#endif // STRING_H_INCLUDED
