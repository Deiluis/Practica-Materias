#include "./ListaD.h"
#include <stdlib.h>
#include <string.h>

void crearLista(tLista* pl) {
    *pl = NULL;
}

bool ponerEnListaEnOrden(tLista* pl, void* info, unsigned tamInfo, Cmp cmp, Acc acc) {
    tNodo *nue, *act, *auxAnt, *auxSig;

    act = *pl;

    if (!act) {
        auxAnt = NULL;
        auxSig = NULL;
    } else {

        while (act -> sig && cmp(info, act -> info) > 0)
            act = act -> sig;

        while (act -> ant && cmp(info, act -> info) < 0)
            act = act -> ant;

         if (cmp(info, act -> info) == 0) {
            if (acc) {
                acc(act -> info, info);
                return true;
            } else
                return false;
        }

        if (cmp(info, act -> info) > 0) {
            auxAnt = act;
            auxSig = act -> sig;
        } else {
            auxAnt = act -> ant;
            auxSig = act;
        }
    }

    nue = (tNodo*) malloc(sizeof(tNodo));

    if (!nue)
        return false;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return false;
    }

    nue -> tamInfo = tamInfo;
    memcpy(nue -> info, info, tamInfo);

    nue -> ant = auxAnt;
    nue -> sig = auxSig;

    if (auxAnt)
        auxAnt -> sig = nue;

    if (auxSig)
        auxSig -> ant = nue;

    *pl = nue;

    return true;
}

bool sacarDeLista(tLista* pl, void* info, unsigned tamInfo, Cmp cmp) {
    tNodo *act, *auxAnt, *auxSig;

    if (*pl == NULL)
        return false;

    act = *pl;

    while (act -> sig && cmp(info, act -> info) > 0)
        act = act -> sig;

    while (act -> ant && cmp(info, act -> info) < 0)
        act = act -> ant;

    if (cmp(info, act -> info) != 0)
        return false;

    auxAnt = act -> ant;
    auxSig = act -> sig;

    *pl = NULL;

    if (auxAnt) {
        auxAnt -> sig = auxSig;
        *pl = auxAnt;
    }

    if (auxSig) {
        auxSig -> ant = auxAnt;
        *pl = auxSig;
    }

    memcpy(info, act -> info, MIN(tamInfo, act -> tamInfo));

    free(act -> info);
    free(act);

    return true;
}

void vaciarLista(tLista* pl) {

    tNodo *act, *elim;

    if (*pl != NULL) {

        act = *pl;
        elim = act -> sig;

        while (elim) {
            act -> sig = elim -> sig;

            if (elim -> sig)
                elim -> sig -> ant = act;

            free(elim -> info);
            free(elim);

            elim = act -> sig;
        }

        elim = act -> ant;

        while (elim) {
            act -> ant = elim -> ant;

            if (elim -> ant)
                elim -> ant -> sig = act;

            free(elim -> info);
            free(elim);

            elim = act -> ant;
        }

        free(act -> info);
        free(act);

        *pl = NULL;
    }
}

void mostrarListaDesdeElInicio (tLista* pl, Imp imp) {

    tNodo *act = *pl;

    if (act) {

        while (act -> ant)
            act = act -> ant;

        imp(act -> info);

        while (act -> sig) {
            act = act -> sig;
            imp(act -> info);
        }

        *pl = act;
    }
}

void mostrarListaDesdeElFinal (tLista* pl, Imp imp) {

    tNodo *act = *pl;

    if (act) {

        while (act -> sig)
            act = act -> sig;

        imp(act -> info);

        while (act -> ant) {
            act = act -> ant;
            imp(act -> info);
        }

        *pl = act;
    }
}
