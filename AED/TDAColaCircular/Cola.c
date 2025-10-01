#include "./Cola.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void crearCola(tCola* c) {
    *c = NULL;
}

bool ponerEnCola(tCola* c, const void* info, unsigned tamInfo) {

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return false;
    }

    nue -> tamInfo = tamInfo;
    memcpy(nue -> info, info, tamInfo);

    if (*c) {
        nue -> sig = (*c) -> sig;
        (*c) -> sig = nue;
    } else
        nue -> sig = nue;

    *c = nue;

    return true;
}

bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo) {

    tNodo* pri;

    if (*c == NULL)
        return false;

    pri = (*c) -> sig;
    memcpy(info, pri -> info, MIN(pri -> tamInfo, tamInfo));

    return true;
}

bool sacarDeCola(tCola* c, void* info, unsigned tamInfo) {

    tNodo* pri;

    if (*c == NULL)
        return false;

    pri = (*c) -> sig;

    if (pri == *c)
        *c = NULL;
    else
        (*c) -> sig = pri -> sig;

    memcpy(info, pri -> info, MIN(pri -> tamInfo, tamInfo));

    free(pri -> info);
    free(pri);

    return true;
}

void vaciarCola(tCola* c) {

    tNodo* elim;

    if (*c != NULL) {
        elim = (*c) -> sig;

        while (elim != *c) {
            (*c) -> sig = elim -> sig;
            free(elim -> info);
            free(elim);
            elim = (*c) -> sig;
        }

        *c = NULL;

        free(elim -> info);
        free(elim);
    }
}

bool colaVacia(const tCola* c) {
    return *c == NULL;
}

bool colaLlena(const tCola* c) {
    return false;
}
