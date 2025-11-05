#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"

typedef tNodo* tLista;

void crearLista(tLista* pl);
bool ponerEnListaAlFinal(tLista* pl, const void* info, unsigned tamInfo);
bool ponerEnListaAlInicio(tLista* pl, const void* info, unsigned tamInfo);
int ponerEnListaEnOrden(tLista* pl, const void* info, unsigned tamInfo, Cmp cmp, Acc acc);
bool sacarDeListaAlInicio(tLista* pl, void* info, unsigned tamInfo);
bool sacarDeListaAlFinal(tLista* pl, void* info, unsigned tamInfo);
tLista* buscarMenorEnLista(const tLista* pl, Cmp cmp);
int buscarEnLista(const tLista* pl, void* info, unsigned tamInfo, Cmp cmp);
void ordenarLista(tLista* pl, Cmp cmp);
void recorrerLista(tLista* pl, Acc acc);
void recorrerListaDesdeFinal(tLista* pl, Acc acc);
void recorrerListaFiltrada(tLista* pl, Cond cond, Acc acc);
void filtrarLista(tLista* pl, Cond cond);
void cargarListaNoFiltrada(tLista* pl, tLista* pnl, Cond cond);
void reducirLista(tLista* pl, void* dst, Acc acc);
void vaciarLista(tLista* pl);
bool listaVacia(const tLista* pl);
bool listaLlena(const tLista* pl, unsigned tamInfo);

#endif // LISTASIMPLE_H_INCLUDED
