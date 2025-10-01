#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#define MIN(a,b) ((a)<(b)?(a):(b))

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tCola;

void crearCola(tCola* c);
bool ponerEnCola(tCola* c, const void* info, unsigned tamInfo);
bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo);
bool sacarDeCola(tCola* c, void* info, unsigned tamInfo);
void vaciarCola(tCola* c);
bool colaVacia(const tCola* c);
bool colaLlena(const tCola* c);

#endif // COLA_H_INCLUDED
