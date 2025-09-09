#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stddef.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef struct {
    tNodo* pri;
    tNodo* ult;
} tCola;

void crearCola(tCola* c);
bool ponerEnCola(tCola* c, const void* info, unsigned cantB);
bool sacarDeCola(tCola* c, void* info, unsigned cantB);
bool verPrimero(const tCola* c, void* info, unsigned cantB);
void vaciarCola(tCola* c);
bool colaVacia(const tCola* c);
bool colaLlena(const tCola* c);


#endif // COLA_H_INCLUDED
