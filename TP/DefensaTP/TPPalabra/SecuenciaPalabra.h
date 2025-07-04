#ifndef SECUENCIAPALABRA_H_INCLUDED
#define SECUENCIAPALABRA_H_INCLUDED
#include "../TPComun/TPComun.h"
#include "../TPString/string.h"

#include "Palabra.h"

typedef struct {
    char* cur;
    bool finSec;
} SecuenciaPalabras;

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, const char* cad);
bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal);
void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, Palabra* pal);
void secuenciaPalabrasEscribirCaracter(SecuenciaPalabras* sec, char c);
bool secuenciaPalabrasFin(SecuenciaPalabras* sec);
void secuenciaPalabrasCerrar(SecuenciaPalabras* sec);

#endif

