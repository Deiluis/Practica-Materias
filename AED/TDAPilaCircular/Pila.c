#include "./Pila.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

    nue -> tamInfo = tamInfo;
    memcpy(nue -> info, info, tamInfo);

    if (*p) {
        nue -> sig = (*p) -> sig;
        (*p) -> sig = nue;
    } else {
        nue -> sig = nue;
        *p = nue;
    }

    return true;
}

bool verTope(const tPila* p, void* info, unsigned tamInfo) {
    tNodo* tope;

    if (*p == NULL)
        return false;

    tope = (*p) -> sig;
    memcpy(info, tope -> info, MIN(tope -> tamInfo, tamInfo));

    return true;
}

bool desapilar(tPila* p, void* info, unsigned tamInfo) {

    tNodo* tope;

    if (*p == NULL)
        return false;

    tope = (*p) -> sig;

    if (tope == *p)
        *p = NULL;
    else
        (*p) -> sig = tope -> sig;

    memcpy(info, tope -> info, MIN(tope -> tamInfo, tamInfo));

    free(tope -> info);
    free(tope);

    return true;
}

void vaciarPila(tPila* p) {
    tNodo* elim;

    if (*p != NULL) {
        elim = (*p) -> sig;

        while (elim != *p) {
            (*p) -> sig = elim -> sig;
            free(elim -> info);
            free(elim);
            elim = (*p) -> sig;
        }

        *p = NULL;

        free(elim -> info);
        free(elim);
    }
}

bool pilaVacia(const tPila* p) {
    return *p == NULL;
}

bool pilaLlena(const tPila* p) {
    return false;
}
