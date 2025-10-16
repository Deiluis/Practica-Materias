#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#define TODO_OK 0
#define ERR_MEMORIA 1
#define DUPLICADO 2

#define INORDEN 0
#define PREORDEN 1
#define POSORDEN 2

#define true 1
#define false 0

typedef int bool;

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo *izq, *der;
} tNodo;

typedef tNodo* tArbol;

typedef int (*Cmp) (const void* e1, const void* e2);
typedef void (*Imp) (const void* e1);
typedef void (*Acc) (void* e1);

void crearArbol(tArbol* pa);
int ponerEnArbolR(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp);
int ponerEnArbolI(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp);
void recorrerArbol(const tArbol* pa, int notacion, Acc acc);
void buscarEnArbol(const tArbol* pa, void* info, unsigned tamInfo);

#endif // ARBOL_H_INCLUDED
