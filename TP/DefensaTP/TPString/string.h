#ifndef STRING_H
#define STRING_H
#include "../TPComun/TPComun.h"

#include <stddef.h>

char* buscarEnString (const char* str, char c);
char* buscarEnStringReversa (const char* str, char c);
char* reemplazarCharEnString (char* str, char orig, char reemp);
char* removerCharEnString (char* str, char c);
char* copiarString (char* dest, const char* orig, size_t lim);
int compararString (const void* str1, const void* str2);
char* concatenarString (char* str1, const char* str2, size_t lim);
char* revertirString (char* str);
char* capitalizarString (char* str);
size_t longitudString (const char* str);
bool esLetra (char c);
char aMayuscula(char c);

#endif
