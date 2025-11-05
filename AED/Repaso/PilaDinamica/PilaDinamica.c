#include "./PilaDinamica.h"
#include <string.h>
#include <stdlib.h>

void crearPila(tPila* p) {
    *p = NULL;
}

bool apilar(tPila* p, const void* info, unsigned tamInfo) {

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return false;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> sig = *p;

    *p = nue;

    return true;
}

bool verTope(const tPila* p, void* info, unsigned tamInfo) {

    if (*p == NULL)
        return false;

    memcpy(info, (*p) -> info, MIN((*p) -> tamInfo, tamInfo));

    return true;
}

bool desapilar(tPila* p, void* info, unsigned tamInfo) {

    tNodo* elim;

    if (*p == NULL)
        return false;

    elim = *p;
    *p = (*p) -> sig;
    memcpy(info, elim -> info, MIN(elim -> tamInfo, tamInfo));
    free(elim -> info);
    free(elim);

    return true;
}

void vaciarPila(tPila* p) {

    tNodo* elim;

    while (*p) {
        elim = *p;
        *p = (*p) -> sig;
        free(elim -> info);
        free(elim);
    }
}

bool pilaVacia(const tPila* p) {
    return *p == NULL;
}

bool pilaLlena(const tPila* p, unsigned tamInfo) {
    return false;
}
