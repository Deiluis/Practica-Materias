#include <stdio.h>
#include <stdlib.h>

int parsearEntero(const char* str);

int main () {

    char pal[] = "12345";
    int parseado;

    parseado = parsearEntero(pal);

    printf("Parseado: %d", parseado);

    return 0;
}

int parsearEntero(const char* str) {

    char* c = (char*) str;
    int res = 0, dig;

    while (*c != '\0') {
        dig = *c - '0';
        res = res * 10 + dig;
        c++;
    }

    return res;
}