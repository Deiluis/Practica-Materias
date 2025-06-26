#ifndef SECUENCIAPALABRAS_H_INCLUDED
#define SECUENCIAPALABRAS_H_INCLUDED

#include "./Palabra.h"

typedef struct {
    char* cur;
    bool fin;
} SecuenciaPalabras;

void secuenciaPalabrasCargar (SecuenciaPalabras* sec, const char* cad);
bool secuenciaPalabrasLeer (SecuenciaPalabras* sec, Palabra* pal);
bool secuenciaPalabrasFin (SecuenciaPalabras* sec);
bool esLetra (char c);

#endif // SECUENCIAPALABRAS_H_INCLUDED