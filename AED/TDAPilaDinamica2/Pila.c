#include "Pila.h"
#include <string.h>
#include <stdlib.h>

void crearPila(tPila* p) {
    *p = NULL;
}

bool apilar(tPila* p, const void* info, unsigned cantB) {

    tNodo* nue = malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(cantB);

    if (!(nue -> info)) {
        free(nue);
        return false;
    }

    memcpy(nue -> info, info, cantB);
    memcpy(&nue -> tamInfo, &cantB, sizeof(unsigned));

    nue -> sig = *p;
    *p = nue;

    return true;
}

bool pilaVacia(const tPila* p) {
    return *p == NULL;
}
