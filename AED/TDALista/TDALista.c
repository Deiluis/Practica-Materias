#include "TDALista.h"
#include <string.h>
#include <stdlib.h>

void ordenamientoBurbujeo(tLista* pl, Cmp cmp);
void ordenamientoSeleccion(tLista* pl, Cmp cmp);

void crearLista(tLista* pl) {
    *pl = NULL;
}

bool ponerEnListaAlPipio(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cmp) {

    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));

    if (!conDup && buscarEnLista(pl, info, cmp) != -1)
        return false; // Duplicado

    if (!nue)
        return false;

    nue -> info = malloc(cantB);

    if (!(nue -> info)) {
        free(nue);
        return false;
    }

    nue -> tamInfo = cantB;
    memcpy(nue -> info, info, cantB);

    nue -> sig = *pl;
    *pl = nue;

    return true;
}

bool ponerEnListaAlFinal(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cmp) {

    tNodo* nue;

    if (!conDup && buscarEnLista(pl, info, cmp) != -1)
        return false; // Duplicado

    nue = (tNodo*) malloc(sizeof(tNodo));

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

    while (*pl)
        pl = &(*pl) -> sig;

    *pl = nue;

    return true;
}

// bool ponerEnListaEnPos(tLista* pl, const void* info, unsigned cantB, int pos) {

//     tNodo* nue = (tNodo*) malloc(sizeof(tNodo));
//     int i = 0;

//     if (!nue)
//         return false;

//     nue -> info = malloc(cantB);

//     if (!(nue -> info)) {
//         free(nue);
//         return false;
//     }

//     nue -> tamInfo = cantB;
//     memcpy(nue -> info, info, cantB);

//     while (*pl && i < pos) {
//         pl = &(*pl) -> sig;
//         i++;
//     }

//     if (i != pos)
//         return false;

// }

// Necesita dos funciones de comparacion, una para saber con que criterio buscar por clave en la lista y la otra con como esta ordenada.
bool ponerEnListaEnOrden(tLista* pl, const void* info, unsigned cantB, bool conDup, Cmp cBus, Cmp cIns, Acc accDup) {

    tNodo* nue;
    tLista* pri = pl;

    // No necesariamente la lista esta ordenada según su clave si es una struct (no es muy eficiente).
    if (!conDup) {

        while (*pl && cBus((*pl) -> info, info) != 0)
            pl = &((*pl) -> sig);

        // Se encontró el duplicado
        if (*pl != NULL) {

            if (accDup == NULL)
                return false; // Duplicado sin acción a realizar.

            accDup((*pl) -> info, info);

            // Esto solo sirve si la acción deja la lista desordenada.
            // Podria detectarse que la información del nodo es diferente antes y despues de la accion para luego ordenar.
            ordenamientoSeleccion(pri, cIns);

            return true; // Habiendo realizado la acción sobre el dupplicado.
        }

        // Deja al puntero de la lista al inicio nuevamente para insertar el elemento.
        pl = pri;
    }

    // Busca donde insertar con el criterio en el que este ordenada la lista.
    while (*pl && cIns((*pl) -> info, info) < 0)
        pl = &((*pl) -> sig);

    // if (!conDup && *pl && cmp((*pl) -> info, info) == 0)
    //     return false; // Duplicado

    nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(cantB);

    if (!(nue -> info)) {
        free(nue);
        return false;
    }

    nue -> tamInfo = cantB;
    memcpy(nue -> info, info, cantB);

    nue -> sig = *pl;
    *pl = nue;

    return true;
}

void ordenarLista(tLista* pl, Cmp cmp, int metodo) {
    switch (metodo) {
        case BURBUJEO:
            ordenamientoBurbujeo(pl, cmp);
            break;
        case SELECCION:
            ordenamientoSeleccion(pl, cmp);
            break;
    }
}

int buscarEnLista(tLista* pl, const void* info, Cmp cmp) {

    int pos = 0;

    while (*pl && cmp((*pl) -> info, info) != 0) {
        pl = &((*pl) -> sig);
        pos++;
    }

    if (*pl == NULL)
        return -1;

    // Se podría copiar en caso de que sea una struct.

    return pos;
}

void vaciarLista(tLista* pl) {

    tNodo* elim;

    while (*pl) {
        elim = *pl;

        *pl = elim -> sig; // Sirve para casos frontera, hasta si solo hay 1 nodo, *pl queda en NULL

        free(elim -> info);
        free(elim);
    }
}

void mostrarLista(const tLista* pl, Imp imp) {

    while (*pl) {
        imp((*pl) -> info);
        pl = &(*pl) -> sig;
    }
}

void mostrarListaInvIte(const tLista* pl, Imp imp) {

    while (*pl) {
        // apilar tNodo*
    }




}

void mostrarListaInvRec(const tLista* pl, Imp imp) {
    if (*pl) {
        mostrarListaInvRec(&(*pl) -> sig, imp);
        imp((*pl) -> info);
    }
}

bool listaVacia(const tLista* pl) {
    return *pl == NULL;
}

bool listaLlena(const tLista* pl) {
    return false; // No sabemos si cuando reserve para apilar haya, asi que siempre decimos que esta vacia, por compatibilidad.
}

void ordenamientoBurbujeo(tLista* pl, Cmp cmp) {
    tLista* pri = pl;
    tNodo* aux;
    bool cambio = true;

    if (pl == NULL || *pl == NULL)
        return;

    while (cambio) {
        cambio = false;

        while ((*pl) -> sig) {
            if (cmp((*pl) -> info, (*pl) -> sig -> info) > 0) {
                cambio = true;
                aux = (*pl) -> sig;
                (*pl)->sig = aux -> sig;
                aux -> sig = *pl;
                *pl = aux;
            }
            pl = &((*pl) -> sig);
        }

        pl = pri;
    }
}

void ordenamientoSeleccion(tLista* pl, Cmp cmp) {

    tNodo *nodoP, *nodoM;
    tLista *q, *min;

    if (pl == NULL || *pl == NULL)
        return;

    while ((*pl) -> sig) {
        q = pl;
        min = pl;

        while (*q) {
            if (cmp((*q) -> info, (*min) -> info) < 0)
                min = q;

            q = &((*q) -> sig);
        }

        nodoM = *min;
        *min = nodoM -> sig;
        nodoP = *pl;
        *pl = nodoM;
        nodoM -> sig = nodoP;

        pl = &((*pl) -> sig);
    }
}
