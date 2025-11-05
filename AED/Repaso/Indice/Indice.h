#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"
#include <stddef.h>

typedef tNodoA* tIndice;

typedef bool (*Conv) (void* idx, const void* reg, int pos);

void crearIndice(tIndice* indice);
int generarIndice(tIndice* indice, const char* nomArchOr, const char* nomArchIdx, unsigned tamOr, unsigned tamIdx, Conv conv, Cmp cmp);
int guardarIndice(const tIndice* indice, const char* nomArch, unsigned tamReg);
int cargarIndice(tIndice* indice, const char* nomArch, unsigned tamReg);
bool buscarIndice(const tIndice* indice, void* info, unsigned tamInfo, Cmp cmp);
int ponerEnIndice(tIndice* indice, const void* info, unsigned tamInfo, Cmp cmp);
bool sacarDeIndice(tIndice* indice, void* info, unsigned tamInfo, Cmp cmp);
void vaciarIndice(tIndice* indice);
void mostrarIndice(const tIndice* indice, Acc acc);

#endif // INDICE_H_INCLUDED
