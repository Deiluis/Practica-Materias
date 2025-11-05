#include "./Arbol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int _cargarArbolDeArchBin(tArbol* pa, FILE* archBin, int limi, int lims, unsigned tamReg, Cmp cmp, Acc acc);
void _recorrerArbolInordenR(tArbol* pa, Acc acc);
void _recorrerArbolPreordenR(tArbol* pa, Acc acc);
void _recorrerArbolPosordenR(tArbol* pa, Acc acc);
bool _esArbolCompletoSegunNivel(const tArbol* pa, int nivel);
void _eliminarRaiz(tArbol* pa);

void crearArbol(tArbol* pa) {
    *pa = NULL;
}

int ponerEnArbolI(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp, Acc acc) {

    tNodoA* nue;
    int comp = 1;

    while (*pa != NULL && comp != 0) {
        comp = cmp(info, (*pa) -> info);

        if (comp < 0)
            pa = &((*pa) -> izq);
        else if (comp > 0)
            pa = &((*pa) -> der);
    }

    if (comp == 0) {
        if (acc) {
            acc((*pa) -> info, NULL);
            return TODO_OK;
        }

        return DUPLICADO;
    }

    nue = malloc(sizeof(tNodoA));

    if (!nue)
        return SIN_MEM;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> izq = nue -> der = NULL;

    *pa = nue;

    return TODO_OK;
}

int ponerEnArbolR(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp, Acc acc) {

    tNodoA* nue;
    int comp;

    if (*pa == NULL) {
        nue = malloc(sizeof(tNodoA));

        if (!nue)
            return SIN_MEM;

        nue -> info = malloc(tamInfo);

        if (!nue -> info) {
            free(nue);
            return SIN_MEM;
        }

        memcpy(nue -> info, info, tamInfo);
        nue -> tamInfo = tamInfo;
        nue -> izq = nue -> der = NULL;

        *pa = nue;

        return TODO_OK;
    }

    comp = cmp(info, (*pa) -> info);

    if (comp == 0) {
        if (acc) {
            acc((*pa) -> info, NULL);
            return TODO_OK;
        }

        return DUPLICADO;
    }

    if (comp < 0)
        return ponerEnArbolR(&((*pa) -> izq), info, tamInfo, cmp, acc);
    else
        return ponerEnArbolR(&((*pa) -> der), info, tamInfo, cmp, acc);
}

int cargarArbolDeArchBin(tArbol* pa, const char* nomArch, unsigned tamReg, Cmp cmp, Acc acc) {

    FILE* archBin = fopen(nomArch, "rb");
    int lims, cod;

    if (archBin == NULL)
        return ERR_ARCHIVO;

    fseek(archBin, 0, SEEK_END);
    lims = (ftell(archBin) / tamReg) -1;

    cod = _cargarArbolDeArchBin(pa, archBin, 0, lims, tamReg, cmp, acc);

    fclose(archBin);

    return cod;
}

int _cargarArbolDeArchBin(tArbol* pa, FILE* archBin, int limi, int lims, unsigned tamReg, Cmp cmp, Acc acc) {

    int m, cod;
    void* reg;

    if (limi > lims)
        return TODO_OK;

    reg = malloc(tamReg);

    if (!reg)
        return SIN_MEM;

    m = (limi + lims) / 2;

    fseek(archBin, m * tamReg, SEEK_SET);
    fread(reg, tamReg, 1, archBin);

    cod = ponerEnArbolI(pa, reg, tamReg, cmp, acc);

    free(reg);

    if (cod != TODO_OK)
        return cod;

    cod = _cargarArbolDeArchBin(pa, archBin, limi, m -1, tamReg, cmp, acc);

    if (cod != TODO_OK)
        return cod;

    return _cargarArbolDeArchBin(pa, archBin, m +1, lims, tamReg, cmp, acc);
}

void recorrerArbolR(tArbol* pa, int notacion, Acc acc) {
    switch (notacion) {
        case INORDEN:
            _recorrerArbolInordenR(pa, acc);
            break;
        case PREORDEN:
            _recorrerArbolPreordenR(pa, acc);
            break;
        case POSORDEN:
            _recorrerArbolPosordenR(pa, acc);
            break;
    }
}

void _recorrerArbolInordenR(tArbol* pa, Acc acc) {

    if (*pa == NULL)
        return;

    _recorrerArbolInordenR(&((*pa) -> izq), acc);
    acc((*pa) -> info, NULL);
    _recorrerArbolInordenR(&((*pa) -> der), acc);
}

void _recorrerArbolPreordenR(tArbol* pa, Acc acc) {

    if (*pa == NULL)
        return;

    acc((*pa) -> info, NULL);
    _recorrerArbolPreordenR(&((*pa) -> izq), acc);
    _recorrerArbolPreordenR(&((*pa) -> der), acc);
}

void _recorrerArbolPosordenR(tArbol* pa, Acc acc) {

    if (*pa == NULL)
        return;

    _recorrerArbolPosordenR(&((*pa) -> izq), acc);
    _recorrerArbolPosordenR(&((*pa) -> der), acc);
    acc((*pa) -> info, NULL);
}

bool buscarPorClaveArbol(const tArbol* pa, void* info, unsigned tamInfo, Cmp cmp) {

    int comp = 1;

    while (*pa != NULL && comp != 0) {
        comp = cmp(info, (*pa) -> info);

        if (comp < 0)
            pa = &((*pa) -> izq);
        else if (comp > 0)
            pa = &((*pa) -> der);
    }

    if (*pa == NULL)
        return false;

    memcpy(info, (*pa) -> info, MIN((*pa) -> tamInfo, tamInfo));

    return true;
}

bool buscarPorNoClaveArbol(const tArbol* pa, void* info, unsigned tamInfo, Cmp cmp) {

    if (*pa == NULL)
        return false;

    if (cmp(info, (*pa) -> info) == 0) {
        memcpy(info, (*pa) -> info, MIN((*pa) -> tamInfo, tamInfo));
        return true;
    }

    if (buscarPorNoClaveArbol(&((*pa) -> izq), info, tamInfo, cmp))
        return true;

    return buscarPorNoClaveArbol(&((*pa) -> der), info, tamInfo, cmp);
}

void vaciarArbol(tArbol* pa) {

    if (*pa == NULL)
        return;

    vaciarArbol(&((*pa) -> izq));
    vaciarArbol(&((*pa) -> der));

    free((*pa) -> info);
    free(*pa);
    *pa = NULL;
}

bool arbolVacio(const tArbol* pa) {
    return *pa == NULL;
}

unsigned cantNodosArbolR(const tArbol* pa) {

    unsigned n = 0;

    if (*pa == NULL)
        return n;

    n += 1;
    n += cantNodosArbolR(&((*pa) -> izq));
    n += cantNodosArbolR(&((*pa) -> der));
    return n;
}

unsigned cantHojasArbolR(const tArbol* pa) {

    unsigned n = 0;

    if (*pa == NULL)
        return n;

    if (!(*pa) -> izq && !(*pa) -> der)
        return n + 1;

    n += cantHojasArbolR(&((*pa) -> izq));
    n += cantHojasArbolR(&((*pa) -> der));
    return n;
}

unsigned cantNoHojasArbolR(const tArbol* pa) {

    unsigned n = 0;

    if (*pa == NULL)
        return n;

    if ((*pa) -> izq || (*pa) -> der) {
        n += 1;
        n += cantNoHojasArbolR(&((*pa) -> izq));
        n += cantNoHojasArbolR(&((*pa) -> der));
    }

    return n;
}

unsigned cantNodosCond(const tArbol* pa, Cond cond) {
    unsigned n = 0;

    if (*pa == NULL)
        return n;

    if (cond((*pa) -> info))
        n += 1;

    n += cantNodosCond(&((*pa) -> izq), cond);
    n += cantNodosCond(&((*pa) -> der), cond);
    return n;
}

bool buscarClaveMayorArbol(const tArbol* pa, void* info, unsigned tamInfo) {

    if (*pa == NULL)
        return false;

    while ((*pa) -> der)
        pa = &((*pa) -> der);

    memcpy(info, (*pa) -> info, MIN((*pa) -> tamInfo, tamInfo));

    return true;
}

bool buscarClaveMenorArbol(const tArbol* pa, void* info, unsigned tamInfo) {

    if (*pa == NULL)
        return false;

    while ((*pa) -> izq)
        pa = &((*pa) -> izq);

    memcpy(info, (*pa) -> info, MIN((*pa) -> tamInfo, tamInfo));

    return true;
}

int alturaArbol(const tArbol* pa) {

    int hi, hd;

    if (*pa == NULL)
        return 0;

    hi = alturaArbol(&((*pa) -> izq));
    hd = alturaArbol(&((*pa) -> der));

    return hi > hd ? hi +1 : hd +1;
}

int nivelArbol(const tArbol* pa) {

    int ni, nd;

    if (*pa == NULL)
        return -1;

    ni = nivelArbol(&((*pa) -> izq));
    nd = nivelArbol(&((*pa) -> der));

    return ni > nd ? ni +1 : nd +1;
}

bool esArbolCompleto(const tArbol* pa) {
    return _esArbolCompletoSegunNivel(pa, nivelArbol(pa));
}

bool esArbolBalanceado(const tArbol* pa) {
    return _esArbolCompletoSegunNivel(pa, nivelArbol(pa) -1);
}

bool _esArbolCompletoSegunNivel(const tArbol* pa, int nivel) {

    if (*pa == NULL)
        return false;

    // Verifica hasta el nivel n.
    if (nivel == 0)
        return true;

    if (!(*pa) -> izq || !(*pa) -> der)
        return false;

    return (
        _esArbolCompletoSegunNivel(&((*pa) -> izq), nivel -1) &&
        _esArbolCompletoSegunNivel(&((*pa) -> der), nivel -1)
    );
}

bool esArbolAVL(const tArbol* pa) {

    int hi, hd;
    bool avlIzq = true, avlDer = true;

    if (*pa == NULL)
        return false;

    hi = alturaArbol(&((*pa) -> izq));
    hd = alturaArbol(&((*pa) -> der));

    if (ABS(hi-hd) <= 1) {

        if (hi > 0)
            avlIzq = esArbolAVL(&((*pa) -> izq));

        if (hd > 0)
            avlDer = esArbolAVL(&((*pa) -> der));

        return avlIzq && avlDer;
    }

    return false;
}

bool sacarDeArbol(tArbol* pa, void* info, unsigned tamInfo, Cmp cmp) {

    int comp = 1;

    while (*pa != NULL && comp != 0) {
        comp = cmp(info, (*pa) -> info);

        if (comp < 0)
            pa = &((*pa) -> izq);
        else if (comp > 0)
            pa = &((*pa) -> der);
    }

    if (*pa == NULL)
        return false;

    memcpy(info, (*pa) -> info, MIN((*pa) -> tamInfo, tamInfo));
    free((*pa) -> info);

    if (!(*pa) -> izq && !(*pa) -> der) {
        free((*pa));
        *pa = NULL;
    } else
        _eliminarRaiz(pa);

    return true;
}

void _eliminarRaiz(tArbol* pa) {

    int hi, hd;
    tArbol* reemp = pa;
    tNodoA* elim;

    hi = alturaArbol(&((*pa) -> izq));
    hd = alturaArbol(&((*pa) -> der));

    if (hi > hd) {
        pa = &((*pa) -> izq);

        while ((*pa) -> der)
            pa = &((*pa) -> der);

    } else {

        pa = &((*pa) -> der);

        while ((*pa) -> izq)
            pa = &((*pa) -> izq);
    }

    (*reemp) -> info = (*pa) -> info;
    (*reemp) -> tamInfo = (*pa) -> tamInfo; // No olvidar jamas. Pueden ser elementos de distinto tamanio.
    elim = *pa;
    *pa = (*pa) -> izq ? (*pa) -> izq : (*pa) -> der;

    free(elim);
}

// int insertarBinEnArbol (tArbol* arbol, const char* nomArch, unsigned tamReg, unsigned tamIdx, Conv conv, Cmp cmp, Acc acc) {

//     FILE* archBin = fopen(nomArch, "rb");
//     void *reg, *idx;
//     int cod = TODO_OK, pos = 0;

//     if (!archBin)
//         return ERR_ARCHIVO;

//     reg = malloc(tamReg);

//     if (!reg) {
//         fclose(archBin);
//         return SIN_MEM;
//     }

//     idx = malloc(tamReg);

//     if (!idx) {
//         fclose(archBin);
//         free(reg);
//         return SIN_MEM;
//     }

//     fread(reg, tamReg, 1, archBin);

//     while (cod == TODO_OK && !feof(archBin)) {
//         conv(idx, reg, pos);

//         cod = ponerEnArbolI(arbol, idx, tamIdx, cmp, acc);
//         fread(reg, tamReg, 1, archBin);
//         pos++;
//     }

//     free(reg);
//     free(idx);
//     fclose(archBin);

//     return cod;
// }

int cargarArbolEnBin (tArbol* arbol, const char* nomArch, unsigned tamReg) {

    FILE* archBin = fopen(nomArch, "wb");
    void *reg;
    int cod = TODO_OK;

    if (!archBin)
        return ERR_ARCHIVO;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(archBin);
        return SIN_MEM;
    }



    free(reg);
    fclose(archBin);

    return cod;
}