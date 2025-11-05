#ifndef PILAESTATICA_H_INCLUDED
#define PILAESTATICA_H_INCLUDED

#include "../comun/comun.h"

#define TAM_PILA 100

typedef struct {
    char pila[TAM_PILA];
    unsigned tope;
} tPila;

void crearPila(tPila* p);
bool apilar(tPila* p, const void* info, unsigned tamInfo);
bool verTope(const tPila* p, void* info, unsigned tamInfo);
bool desapilar(tPila* p, void* info, unsigned tamInfo);
void vaciarPila(tPila* p);
bool pilaVacia(const tPila* p);
bool pilaLlena(const tPila* p, unsigned tamInfo);

#endif // PILAESTATICA_H_INCLUDED
