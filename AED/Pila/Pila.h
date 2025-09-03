#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#define CAP_INI 20
#define FACTOR_OCUP 0.25
#define FACTOR_DECR 0.5

#define INCREMENTAR 0
#define DECREMENTAR 1

// Para más claridad.
#define bool int
#define true 1
#define false 0

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#include <stddef.h>

typedef struct {
    void* cont;
    int tope;
    size_t cap;
} tPila;

bool crearPila (tPila* pila);
bool apilar (tPila* pila, const void* elem, size_t tamElem);
bool verTope (tPila* pila, void* elem, size_t tamElem);
bool desapilar (tPila* pila, void* elem, size_t tamElem);
void vaciarPila (tPila* pila);
bool pilaVacia (const tPila* pila);
bool pilaLlena (const tPila* pila, size_t tamElem);
void destruirPila (tPila* pila);

#endif // PILA_H_INCLUDED