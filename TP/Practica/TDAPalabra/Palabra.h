#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED
#include <stdbool.h>

#define PALABRA_TAM 51

typedef struct {
    char vPal[PALABRA_TAM];
} Palabra;

bool palabraEsPalindromo (Palabra* pal);
void palabraMostrar (Palabra* pal);
int palabraComparar (Palabra* pal1, Palabra* pal2);
int palabraCompararI (Palabra* pal1, Palabra* pal2);

#endif // PALABRA_H_INCLUDED