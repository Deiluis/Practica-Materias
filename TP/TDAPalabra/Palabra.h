#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED

#include <stdbool.h>
#define TAM 51

typedef struct
{
    char vPal[TAM];
}
Palabra;

void palabraMostrar(Palabra* pal);
void palabraATitulo(Palabra* pal);
bool esLetra(char c);

#endif // PALABRA_H_INCLUDED
