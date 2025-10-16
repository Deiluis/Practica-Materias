#include "./Arbol.h"
#include <stdlib.h>
#include <string.h>

void recorrerArbolInordenR(const tArbol* pa, Acc acc);
void recorrerArbolPreordenR(const tArbol* pa, Acc acc);
void recorrerArbolPosordenR(const tArbol* pa, Acc acc);

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

void recorrerArbolPosordenR(const tArbol* pa, Acc acc) {

    if (*pa) {
        recorrerArbolPosordenR(&((*pa) -> izq), acc);
        recorrerArbolPosordenR(&((*pa) -> der), acc);
        acc((*pa) -> info);
    }
}
