#include "./ListaSimple.h"
#include <string.h>
#include <stdlib.h>
#include "../PilaDinamica/PilaDinamica.h"

void crearLista(tLista* pl) {
    *pl = NULL;
}

bool ponerEnListaAlFinal(tLista* pl, const void* info, unsigned tamInfo) {

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

    while (*pl)
        pl = &((*pl) -> sig);

    *pl = nue;

    return true;
}

bool ponerEnListaAlInicio(tLista* pl, const void* info, unsigned tamInfo) {

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
    nue -> sig = *pl;
    *pl = nue;

    return true;
}

int ponerEnListaEnOrden(tLista* pl, const void* info, unsigned tamInfo, Cmp cmp, Acc acc) {

    tNodo* nue;

    while (*pl && cmp((*pl) -> info, info) < 0)
        pl = &((*pl) -> sig);

    if (*pl && cmp((*pl) -> info, info) == 0) {
        if (acc) {
            acc((*pl) -> info, NULL);
            return TODO_OK;
        }

        return DUPLICADO;
    }

    nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return false;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> sig = *pl;
    *pl = nue;

    return TODO_OK;
}

bool sacarDeListaAlInicio(tLista* pl, void* info, unsigned tamInfo) {

    tNodo* elim;

    if (*pl == NULL)
        return false;

    elim = *pl;
    *pl = elim -> sig;

    memcpy(info, elim -> info, MIN(elim -> tamInfo, tamInfo));

    free(elim -> info);
    free(elim);

    return true;
}

bool sacarDeListaAlFinal(tLista* pl, void* info, unsigned tamInfo) {

    tNodo* elim;

    if (*pl == NULL)
        return false;

    while ((*pl) -> sig)
        pl = &((*pl) -> sig);

    elim = *pl;
    *pl = elim -> sig;

    memcpy(info, elim -> info, MIN(elim -> tamInfo, tamInfo));

    free(elim -> info);
    free(elim);

    return true;
}

int buscarEnLista(const tLista* pl, void* info, unsigned tamInfo, Cmp cmp) {

    int pos = 0;

    while (*pl && cmp((*pl) -> info, info) != 0) {
        pl = &((*pl) -> sig);
        pos++;
    }

    if (*pl) {
        memcpy(info, (*pl) -> info, MIN((*pl) -> tamInfo, tamInfo));
        return pos;
    }

    return -1;
}

tLista* buscarMenorEnLista(const tLista* pl, Cmp cmp) {

    tLista* m;

    if (*pl == NULL)
        return NULL;

    m = (tLista*) pl;

    while (*pl) {

        if (cmp((*pl) -> info, (*m) -> info) < 0)
            m = (tLista*) pl;

        pl = &((*pl) -> sig);
    }

    return m;
}

void ordenarLista(tLista* pl, Cmp cmp) {

    tLista* m;
    tNodo* desenganchado;

    if (*pl == NULL)
        return;

    while ((*pl) -> sig) {
        m = buscarMenorEnLista(pl, cmp);

        if (m != pl) {
            desenganchado = *m;
            *m = desenganchado -> sig;
            desenganchado -> sig = *pl;
            *pl = desenganchado;
        }

        pl = &((*pl) -> sig);
    }
}

void recorrerLista(tLista* pl, Acc acc) {
    while (*pl) {
        acc((*pl) -> info, NULL);
        pl = &((*pl) -> sig);
    }
}

void recorrerListaDesdeFinal(tLista* pl, Acc acc) {
    tPila nodos;
    crearPila(&nodos);

    while (*pl) {
        apilar(&nodos, pl, sizeof(tNodo*));
        pl = &((*pl) -> sig);
    }

    while (desapilar(&nodos, pl, sizeof(tNodo*)))
        acc((*pl) -> info, NULL);
}

void recorrerListaFiltrada(tLista* pl, Cond cond, Acc acc) {
    while (*pl) {
        if (cond((*pl) -> info))
            acc((*pl) -> info, NULL);
        pl = &((*pl) -> sig);
    }
}

void filtrarLista(tLista* pl, Cond cond) {

    tNodo* elim;

    while (*pl) {
        if (!cond((*pl) -> info)) {
            elim = *pl;
            *pl = elim -> sig;
            free(elim -> info);
            free(elim);
        } else
            pl = &((*pl) -> sig);
    }
}

void cargarListaNoFiltrada(tLista* pl, tLista* pnl, Cond cond) {

    tNodo* desenganchado;

    while (*pl) {
        if (!cond((*pl) -> info)) {
            desenganchado = *pl;
            *pl = desenganchado -> sig;
            *pnl = desenganchado;
            desenganchado -> sig = NULL;
            pnl = &((*pnl) -> sig);
        } else
            pl = &((*pl) -> sig);
    }
}

void reducirLista(tLista* pl, void* dst, Acc acc) {
    while (*pl) {
        acc((*pl) -> info, dst);
        pl = &((*pl) -> sig);
    }
}

void vaciarLista(tLista* pl) {

    tNodo* elim;

    while (*pl) {
        elim = *pl;
        *pl = elim -> sig;
        free(elim -> info);
        free(elim);
    }
}

bool listaVacia(const tLista* pl) {
    return *pl == NULL;
}

bool listaLlena(const tLista* pl, unsigned tamInfo) {
    return false;
}
