#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#include <stddef.h>

#define BURBUJEO 0
#define SELECCION 1

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tLista;
typedef void (*Imp) (const void* elem);
typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Acc) (const void* e1, const void* e2);

void crearLista(tLista* pl);
bool ponerEnListaAlPipio(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cmp);
// bool ponerEnListaEnPos(tLista* pl, const void* info, unsigned cantB);
bool ponerEnListaEnOrden(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cBus, Cmp cIns, Acc accDup);
bool ponerEnListaAlFinal(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cmp);
void ordenarLista(tLista* pl, Cmp cmp, int metodo);
int buscarEnLista(tLista* pl, const void* info, Cmp cmp);
void vaciarLista(tLista* pl);
void mostrarLista(const tLista* pl, Imp imp);
bool listaVacia(const tLista* pl);
bool listaLlena(const tLista* pl);


#endif // TDALISTA_H_INCLUDED
