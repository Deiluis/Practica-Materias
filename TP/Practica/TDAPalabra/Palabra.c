#include "Palabra.h"
#include <stdio.h>
#include "../TDAString/string.h"
#include <string.h>

bool palabraEsPalindromo (Palabra* pal) {
    return esPalindromo(pal -> vPal);
}

void palabraMostrar (Palabra* pal) {
    printf("%s", pal -> vPal);
}

int palabraComparar (Palabra* pal1, Palabra* pal2) {
    return strcmp(pal1 -> vPal, pal2 -> vPal);
}

int palabraCompararI (Palabra* pal1, Palabra* pal2) {
    return strcmpi(pal1 -> vPal, pal2 -> vPal);
}
