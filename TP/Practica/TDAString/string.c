#include "string.h"

size_t longitudStr (const char* str) {

    const char* letraActual = str;

    while (*letraActual != '\0')
        letraActual++;

    return letraActual - str;
}

bool esPalindromo (const char* str) {

    const char* i1 = str;
    const char* i2 = str + longitudStr(str) -1;

    while (i1 < i2 && aMayuscula(*i1) == aMayuscula(*i2)) {
        i1++;
        i2--;
    }

    return i1 >= i2;
}

char aMayuscula (char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');

    return c;
}
