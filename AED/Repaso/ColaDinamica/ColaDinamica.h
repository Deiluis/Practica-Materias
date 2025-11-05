#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"

typedef struct {
    tNodo *pri, *ult;
} tCola;

void crearCola(tCola* c);
bool ponerEnCola(tCola* c, const void* info, unsigned tamInfo);
bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo);
bool sacarDeCola(tCola* c, void* info, unsigned tamInfo);
void vaciarCola(tCola* c);
bool colaVacia(const tCola* c);
bool colaLlena(const tCola* c, unsigned tamInfo);

#endif // COLADINAMICA_H_INCLUDED
