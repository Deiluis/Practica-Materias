#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stddef.h>

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
bool apilar(tPila* p, const void* info, unsigned cantB);
bool pilaVacia(const tPila* p);


#endif // PILA_H_INCLUDED
