#ifndef COLAESTATICA_H_INCLUDED
#define COLAESTATICA_H_INCLUDED

#include "../comun/comun.h"

#define TAM_COLA 100

typedef struct {
    char cola[TAM_COLA];
    unsigned pri, ult, tDisp;
} tCola;

void crearCola(tCola* c);
bool ponerEnCola(tCola* c, const void* info, unsigned tamInfo);
bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo);
bool sacarDeCola(tCola* c, void* info, unsigned tamInfo);
void vaciarCola(tCola* c);
bool colaVacia(const tCola* c);
bool colaLlena(const tCola* c, unsigned tamInfo);

#endif // COLAESTATICA_H_INCLUDED
