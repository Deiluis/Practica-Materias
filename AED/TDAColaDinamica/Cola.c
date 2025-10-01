#include "Cola.h"
#include <string.h>
#include <stdlib.h>

void crearCola(tCola* c) {
    c -> pri = NULL;
    c -> ult = NULL;
}

bool ponerEnCola(tCola* c, const void* info, unsigned cantB) {

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(cantB);

    if (!(nue -> info)) {
        free(nue);
        return false;
    }

    nue -> tamInfo = cantB;
    memcpy(nue -> info, info, cantB);
    nue -> sig = NULL;

    if (c -> pri == NULL)
        c -> pri = nue;
    else
        (c -> ult) -> sig = nue;

    c -> ult = nue;

    return true;
}

bool sacarDeCola(tCola* c, void* info, unsigned cantB) { // Verificar que funque

    tNodo* elim;

    if (c -> pri == NULL)
        return false;

    memcpy(info, (c -> pri) -> info, MIN(cantB, (c -> pri) -> tamInfo));
    elim = c -> pri;

    if (c -> pri == c -> ult)
        c -> ult = NULL;

    c -> pri = elim -> sig;

    free(elim -> info);
    free(elim);

    return true;
}

bool verPriDeCola(const tCola* c, void* info, unsigned cantB) {

    if (c -> pri == NULL)
        return false;

    memcpy(info, (c -> pri) -> info, MIN(cantB, (c -> pri) -> tamInfo));

    return true;
}

void vaciarCola(tCola* c) {

    tNodo* elim;

    while (c -> pri) {
        elim = c -> pri;

        c -> pri = elim -> sig;

        free(elim -> info);
        free(elim);
    }

    c -> ult = NULL;
}

bool colaVacia(const tCola* c) {
    return c -> pri == NULL;
}

bool colaLlena(const tCola* c) {
    return false; // No sabemos si cuando reserve para encolar haya, asi que siempre decimos que esta vacia, por compatibilidad.
}
