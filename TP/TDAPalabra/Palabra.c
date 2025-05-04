#include "Palabra.h"
#include <stdio.h>
#include <ctype.h>

void palabraMostrar(Palabra* pal) {
    puts(pal -> vPal);
}

void palabraATitulo(Palabra* pal) {

    char *iPal = pal -> vPal;
    *iPal = toupper(*iPal);
    iPal++;

    while (*iPal != '\0') {
        *iPal = tolower(*iPal);
        iPal++;
    }
}

bool esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
