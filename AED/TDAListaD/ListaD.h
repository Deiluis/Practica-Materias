#ifndef LISTAD_H_INCLUDED
#define LISTAD_H_INCLUDED

#define MIN(a,b) ((a)<(b)?(a):(b))

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    struct sNodo* ant;
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef tNodo* tLista;

typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Acc) (void* e1, void* e2);
typedef void (*Imp) (const void* elem);

void crearLista(tLista* pl);
bool ponerEnListaEnOrden(tLista* pl, void* info, unsigned tamInfo, Cmp cmp, Acc acc);
void mostrarListaDesdeElInicio (tLista* pl, Imp imp);
void mostrarListaDesdeElFinal (tLista* pl, Imp imp);
bool sacarDeLista(tLista* pl, void* info, unsigned tamInfo, Cmp cmp);
void vaciarLista(tLista* pl);

#endif // LISTAD_H_INCLUDED
