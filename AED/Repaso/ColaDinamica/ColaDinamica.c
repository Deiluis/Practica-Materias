#include "./ColaDinamica.h"
#include <string.h>
#include <stdlib.h>

void crearCola(tCola* c) {
    c -> pri = NULL;
    c -> ult = NULL;
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

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> sig = NULL;

    if (c -> pri)
        c -> ult -> sig = nue;
    else
        c -> pri = nue;

    c -> ult = nue;

    return true;
}

bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo) {

    if (c -> pri == NULL)
        return false;

    memcpy(info, c -> pri -> info, MIN(c -> pri -> tamInfo, tamInfo));

    return true;
}

bool sacarDeCola(tCola* c, void* info, unsigned tamInfo) {

    tNodo* elim;

    if (c -> pri == NULL)
        return false;

    elim = c -> pri;
    c -> pri = c -> pri -> sig;

    if (c -> pri == NULL)
        c -> ult = NULL;

    memcpy(info, elim -> info, MIN(elim -> tamInfo, tamInfo));
    free(elim -> info);
    free(elim);

    return true;
}

void vaciarCola(tCola* c) {

    tNodo* elim;

    while (c -> pri) {
        elim = c -> pri;
        c -> pri = c -> pri -> sig;
        free(elim -> info);
        free(elim);
    }

    c -> ult = NULL;
}

bool colaVacia(const tCola* c) {
    return c -> pri == NULL;
}

bool colaLlena(const tCola* c, unsigned tamInfo) {
    return false;
}