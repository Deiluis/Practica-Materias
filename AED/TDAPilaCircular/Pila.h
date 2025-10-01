#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#define MIN(a,b) ((a)<(b)?(a):(b))

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tPila;

void crearPila(tPila* p);
bool apilar(tPila* p, const void* info, unsigned tamInfo);
bool verTope(const tPila* p, void* info, unsigned tamInfo);
bool desapilar(tPila* p, void* info, unsigned tamInfo);
void vaciarPila(tPila* p);
bool pilaVacia(const tPila* p);
bool pilaLlena(const tPila* p);

#endif // PILA_H_INCLUDED
