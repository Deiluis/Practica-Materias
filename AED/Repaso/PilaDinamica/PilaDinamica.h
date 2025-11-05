#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"

typedef tNodo* tPila;

void crearPila(tPila* p);
bool apilar(tPila* p, const void* info, unsigned tamInfo);
bool verTope(const tPila* p, void* info, unsigned tamInfo);
bool desapilar(tPila* p, void* info, unsigned tamInfo);
void vaciarPila(tPila* p);
bool pilaVacia(const tPila* p);
bool pilaLlena(const tPila* p, unsigned tamInfo);

#endif // PILADINAMICA_H_INCLUDED
