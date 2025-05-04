#ifndef SECUENCIAPALABRAS_H_INCLUDED
#define SECUENCIAPALABRAS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include "Palabra.h"

typedef struct
{
    char *cur;
    bool finSec;
}
SecuenciaPalabras;

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, const char* cad);
bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal);
void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, const Palabra* pal);
void secuenciaPalabrasEscribirCaracter(SecuenciaPalabras* sec, const char c);
bool secuenciaPalabrasFin(const SecuenciaPalabras* sec);
void secuenciaPalabrasCerrar(SecuenciaPalabras* sec);

#endif // SECUENCIAPALABRAS_H_INCLUDED
