#include "./Arbol.h"
#include <stdlib.h>
#include <string.h>

void recorrerArbolInordenR(const tArbol* pa, Acc acc);
void recorrerArbolPreordenR(const tArbol* pa, Acc acc);
void recorrerArbolPosordenR(const tArbol* pa, Acc acc);
void _eliminarRaiz (tArbol* pa);

void crearArbol(tArbol* pa) {
    *pa = NULL;
}

int ponerEnArbolR(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp) {

    tNodo* nue; // No hace falta, se puede usar *pa

    if (*pa == NULL) {
        nue = (tNodo*) malloc(sizeof(tNodo));

        if (!nue)
            return ERR_MEMORIA;

        nue -> info = malloc(tamInfo);

        if (!nue -> info) {
            free(nue);
            return ERR_MEMORIA;
        }

        nue -> tamInfo = tamInfo;
        memcpy(nue -> info, info, tamInfo);
        nue -> izq = NULL;
        nue -> der = NULL;

        *pa = nue;

        return TODO_OK;
    }

    if (cmp(info, (*pa) -> info) == 0) // Duplicado
        return DUPLICADO;

    if (cmp(info, (*pa) -> info) > 0)
        return ponerEnArbolR(&((*pa) -> der), info, tamInfo, cmp);
    else
        return ponerEnArbolR(&((*pa) -> izq), info, tamInfo, cmp);

    // Funcionaria igual sin los return, pero es peligroso. Si hubiese algo despues de la invocacion, lo haria.
}

int ponerEnArbolI(tArbol* pa, const void* info, unsigned tamInfo, Cmp cmp) {

    tNodo* nue;
    bool dup = false;

    while (*pa && !dup) {
        if (cmp(info, (*pa) -> info) == 0)
            dup = true;

        if (cmp(info, (*pa) -> info) > 0)
            pa = &((*pa) -> der);
        else
            pa = &((*pa) -> izq);
    }

    if (dup)
        return DUPLICADO;

    nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return ERR_MEMORIA;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return ERR_MEMORIA;
    }

    nue -> tamInfo = tamInfo;
    memcpy(nue -> info, info, tamInfo);
    nue -> izq = NULL;
    nue -> der = NULL;

    *pa = nue;

    return TODO_OK;
}

void recorrerArbol(const tArbol* pa, int notacion, Acc acc) {

    switch (notacion) {
        case INORDEN:
            recorrerArbolInordenR(pa, acc);
            break;
        case PREORDEN:
            recorrerArbolPreordenR(pa, acc);
            break;
        case POSORDEN:
            recorrerArbolPosordenR(pa, acc);
            break;
    }
}

// Auxiliares

void recorrerArbolInordenR(const tArbol* pa, Acc acc) {

    if (*pa) {
        recorrerArbolInordenR(&((*pa) -> izq), acc);
        acc((*pa) -> info);
        recorrerArbolInordenR(&((*pa) -> der), acc);
    }
}

void recorrerArbolPreordenR(const tArbol* pa, Acc acc) {

    if (*pa) {
        acc((*pa) -> info);
        recorrerArbolPreordenR(&((*pa) -> izq), acc);
        recorrerArbolPreordenR(&((*pa) -> der), acc);
    }
}

int alturaArbol(const tArbol* pa) {

    // Me evita tener que llamar de nuevo a la recursiva mas veces.
    int hi = 0;
    int hd = 0;

    if (*pa == NULL)
        return 0;

    hi = alturaArbol(&((*pa) -> izq));
    hd = alturaArbol(&((*pa) -> der));

    return hi > hd ? hi+1 : hd+1;
}

// hacer el nivel arbol

void recorrerArbolPosordenR(const tArbol* pa, Acc acc) {

    if (*pa) {
        recorrerArbolPosordenR(&((*pa) -> izq), acc);
        recorrerArbolPosordenR(&((*pa) -> der), acc);
        acc((*pa) -> info);
    }
}

void recorrerHastaNivel(const tArbol* pa, int nivel, Acc acc) {

    if (*pa && nivel >= 0) {
        acc((*pa) -> info);
        recorrerHastaNivel(&((*pa) -> izq), nivel - 1, acc);
        recorrerHastaNivel(&((*pa) -> der), nivel - 1, acc);
    }
}

void procesarNivel(const tArbol* pa, int nivel, Acc acc) {

    if (*pa == NULL)
        return;

    if (nivel == 0) {
        acc((*pa) -> info);
        return;
    }

    recorrerHastaNivel(&((*pa) -> izq), nivel - 1, acc);
    recorrerHastaNivel(&((*pa) -> der), nivel - 1, acc);
}

// Hacer el recorrer desde un nivel

void vaciarArbol(tArbol* pa) {
    if (*pa) {
        vaciarArbol(&((*pa) -> izq));
        vaciarArbol(&((*pa) -> der));

        free((*pa) -> info);
        free(*pa);

        *pa = NULL;
    }
}

bool eliminarNodo(tArbol* pa, void* info, unsigned tamInfo, Cmp cmp) {

    int comp = 1;

    while (*pa && comp != 0) {
        comp = cmp(info, (*pa) -> info);

        if (comp > 0)
            pa = &((*pa) -> der);
        else
            pa = &((*pa) -> izq);
    }

    if (*pa == NULL)
        return false;

    memcpy(info, (*pa) -> info, MIN(tamInfo, (*pa) -> tamInfo));
    free((*pa) -> info);

    if (!(*pa) -> der && !(*pa) -> izq) {
        free(*pa);
        *pa = NULL;
    } else
        _eliminarRaiz(pa);

    return true;
}


void _eliminarRaiz (tArbol* pa) {

    int hi, hd;
    tNodo* elim;
    tArbol* raiz = pa;

    hi = alturaArbol(&((*pa) -> izq));
    hd = alturaArbol(&((*pa) -> der));

    if (hi > hd) {

        // Puedo usar clave menor y mayor

        pa = &((*pa) -> izq);

        while ((*pa) -> der)
            pa = &((*pa) -> der);
    } else {

        pa = &((*pa) -> der);

        while ((*pa) -> izq)
            pa = &((*pa) -> izq);
    }

    (*raiz) -> info = (*pa) -> info;
    (*raiz) -> tamInfo = (*pa) -> tamInfo;
    elim = *pa;
    *pa = (*pa) -> der ? (*pa) -> der : (*pa) -> izq;

    free(elim);
}
