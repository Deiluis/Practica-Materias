#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "../comun/comun.h"
#include "../comun/comunListaEnlazada.h"
#include <stddef.h>

#define INORDEN 0
#define PREORDEN 1
#define POSORDEN 2

typedef tNodoA* tArbol;

void crearArbol(tArbol* pa);
int ponerEnArbolI(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp, Acc acc);
int ponerEnArbolR(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp, Acc acc);
int cargarArbolDeArchBin(tArbol* pa, const char* nomArch, unsigned tamReg, Cmp cmp, Acc acc);
void recorrerArbolR(tArbol* pa, int notacion, Acc acc);
bool buscarPorClaveArbol(const tArbol* pa, void* info, unsigned tamInfo, Cmp cmp);
bool buscarPorNoClaveArbol(const tArbol* pa, void* info, unsigned tamInfo, Cmp cmp);
void vaciarArbol(tArbol* pa);
bool arbolVacio(const tArbol* pa);
unsigned cantNodosArbolR(const tArbol* pa);
unsigned cantHojasArbolR(const tArbol* pa);
unsigned cantNoHojasArbolR(const tArbol* pa);
unsigned cantNodosCond(const tArbol* pa, Cond cond);
bool buscarClaveMayorArbol(const tArbol* pa, void* info, unsigned tamInfo);
bool buscarClaveMenorArbol(const tArbol* pa, void* info, unsigned tamInfo);
int alturaArbol(const tArbol* pa);
int nivelArbol(const tArbol* pa);
bool esArbolCompleto(const tArbol* pa);
bool esArbolBalanceado(const tArbol* pa);
bool esArbolAVL(const tArbol* pa);
bool sacarDeArbol(tArbol* pa, void* info, unsigned tamInfo, Cmp cmp);
// int insertarBinEnArbol (tArbol* arbol, const char* nomArch, unsigned tamReg, unsigned tamIdx, Conv conv, Cmp cmp, Acc acc);
int cargarArbolEnBin (tArbol* arbol, const char* nomArch, unsigned tamReg);

#endif // ARBOL_H_INCLUDED
