#ifndef TDAPILA_H_INCLUDED
#define TDAPILA_H_INCLUDED

#include <stddef.h>
#define TAM_PILA 100
#define TODO_OK 0
#define LLENO 1
#define VACIO -1
#define NO_VACIO 2
#define NO_LLENO 3


typedef struct {
    char pila[TAM_PILA];
    size_t tope;
} tPila;

void crearPila(tPila* pila);
int apilar(tPila* pila, const void* elem, size_t tamElem);
int verTope(const tPila* pila, void* elem, size_t tamElem);
int desapilar(tPila* pila, void* elem, size_t tamElem);
void vaciarPila(tPila* pila);
int pilaVacia(const tPila* pila);
int pilaLlena(const tPila* pila, size_t tamElem);

#endif // TDAPILA_H_INCLUDED
