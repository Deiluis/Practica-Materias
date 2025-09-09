#include "Pila.h"
#include <string.h>
#include <stdlib.h>

void crearPila(tPila* p) {
    *p = NULL;
}

bool apilar(tPila* p, const void* info, unsigned cantB) {

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

    nue -> sig = *p;
    *p = nue;

    return true;
}


bool desapilar(tPila* p, void* info, unsigned cantB) {

    tNodo* elim;

    if (*p == NULL)
        return false;

    elim = *p;

    memcpy(info, elim -> info, MIN(cantB, elim -> tamInfo));

    *p = elim -> sig;

    free(elim -> info);
    free(elim);

    return true;
}

bool verTope(const tPila* p, void* info, unsigned cantB) {

    if (*p == NULL)
        return false;

    memcpy(info, (*p) -> info, MIN(cantB, (*p) -> tamInfo));

    return true;
}

void vaciarPila(tPila* p) {

    tNodo* elim;

    while (*p) {
        elim = *p;

        *p = elim -> sig; // Sirve para casos frontera, hasta si solo hay 1 nodo, *p queda en NULL

        free(elim -> info);
        free(elim);
    }
}

bool pilaVacia(const tPila* p) {
    return *p == NULL;
}

bool pilaLlena(const tPila* p) {
    return false; // No sabemos si cuando reserve para apilar haya, asi que siempre decimos que esta vacia, por compatibilidad.
}
