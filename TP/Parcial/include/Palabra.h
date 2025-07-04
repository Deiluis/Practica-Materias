#ifndef PALABRA_H
#define PALABRA_H

#include <stddef.h>


#define TAM_PAL 51


typedef struct
{
    char vPal[TAM_PAL];
    size_t longitud;
    int cantApariciones;
}
Palabra;


int palabraCmp(const void* p1, const void* p2);
int palabraCmpXCantAparicionesDesc(const void* p1, const void* p2);
void palabraATitulo(Palabra* pal);
void imprimirPalabra(void* p, void* extra);


#endif // PALABRA_H
