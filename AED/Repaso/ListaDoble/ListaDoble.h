#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"

typedef tNodoD* tListaD;

void crearListaD(tListaD* pl);
bool ponerEnListaDAlInicio(tListaD* pl, const void* info, unsigned tamInfo);
bool ponerEnListaDAlFinal(tListaD* pl, const void* info, unsigned tamInfo);
int ponerEnListaDEnOrden(tListaD* pl, const void* info, unsigned tamInfo, Cmp cmp, Acc acc);
bool sacarDeListaD(tListaD* pl, void* info, unsigned tamInfo, Cmp cmp);
// bool sacarDeListaAlInicio(tListaD* pl, void* info, unsigned tamInfo);
// bool sacarDeListaAlFinal(tListaD* pl, void* info, unsigned tamInfo);
// tListaD* buscarMenorEnLista(const tListaD* pl, Cmp cmp);
int buscarEnListaD(tListaD* pl, void* info, unsigned tamInfo, Cmp cmp);
void ordenarListaD(tListaD* pl, Cmp cmp);
void recorrerListaDDesdeInicio(tListaD* pl, Acc acc, void* extra);
void recorrerListaDDesdeFinal(tListaD* pl, Acc acc, void* extra);
// void recorrerListaFiltrada(tListaD* pl, Cond cond, Acc acc);
// void filtrarLista(tListaD* pl, Cond cond);
// void cargarListaNoFiltrada(tListaD* pl, tListaD* pnl, Cond cond);
// void reducirLista(tListaD* pl, void* dst, AccRed accRed);
void vaciarListaD(tListaD* pl);
bool listaDVacia(const tListaD* pl);
bool listaDLlena(const tListaD* pl, unsigned tamInfo);

#endif // LISTADOBLE_H_INCLUDED
