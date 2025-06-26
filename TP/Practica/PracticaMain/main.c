#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "../TDAFecha/Fecha.h"

size_t longitudStr (const char* str);
bool esPalindromo (const char* str);
char aMayuscula (char c);

int main () {

    int tam = 10;

    char str1[tam +1];
    char str2[] = "Hola que tal me llamo Luis";

    strncpy(str1, str2, tam);

    str1[10] = '\0';

    char* pos = strstr(str1, "que");

    printf("%s\n", str1);
    printf("%Iu\n", strlen(str1));

    if (pos)
        printf("%d\n", (int) (pos - str1));


    char* pal;

    pal = strtok(str2, " ");
    pal = strtok(str1, " ");

    while (pal) {
        printf("%s\n", pal);
        pal = strtok(NULL, " ");
    }

    return 0;
}

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
