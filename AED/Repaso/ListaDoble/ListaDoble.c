#include "./ListaDoble.h"
#include <stdlib.h>
#include <string.h>

void crearListaD(tListaD* pl) {
    *pl = NULL;
}

bool ponerEnListaDAlInicio(tListaD* pl, const void* info, unsigned tamInfo) {
    tNodoD *nue, *act;

    act = *pl;

    if (act) {
        while (act -> ant)
            act = act -> ant;
    }

    nue = (tNodoD*) malloc(sizeof(tNodoD));

    if (!nue)
        return SIN_MEM;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> ant = NULL;
    nue -> sig = act;

    if (act)
        act -> ant = nue;

    *pl = nue;

    return TODO_OK;
}

bool ponerEnListaDAlFinal(tListaD* pl, const void* info, unsigned tamInfo) {
    tNodoD *nue, *act;

    act = *pl;

    if (act) {
        while (act -> sig)
            act = act -> sig;
    }

    nue = (tNodoD*) malloc(sizeof(tNodoD));

    if (!nue)
        return SIN_MEM;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> ant = act;
    nue -> sig = NULL;

    if (act)
        act -> sig = nue;

    *pl = nue;

    return TODO_OK;
}

int ponerEnListaDEnOrden(tListaD* pl, const void* info, unsigned tamInfo, Cmp cmp, Acc acc) {
    tNodoD *nue, *act, *auxAnt, *auxSig;

    act = *pl;

    if (!act) {
        auxAnt = auxSig = NULL;
    } else {

        while (act -> sig && cmp(info, act -> info) > 0)
            act = act -> sig;

        while (act -> ant && cmp(info, act -> info) < 0)
            act = act -> ant;

        if (cmp(info, act -> info) == 0) {
            if (acc) {
                acc(act -> info, NULL);
                return TODO_OK;
            }

            return DUPLICADO;
        }

        if (cmp(info, act -> info) < 0) {
            auxAnt = act -> ant;
            auxSig = act;
        } else {
            auxAnt = act;
            auxSig = act -> sig;
        }
    }

    nue = (tNodoD*) malloc(sizeof(tNodoD));

    if (!nue)
        return SIN_MEM;

    nue -> info = malloc(tamInfo);

    if (!nue -> info) {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue -> info, info, tamInfo);
    nue -> tamInfo = tamInfo;
    nue -> ant = auxAnt;
    nue -> sig = auxSig;

    if (auxAnt)
        auxAnt -> sig = nue;

    if (auxSig)
        auxSig -> ant = nue;

    *pl = nue;

    return TODO_OK;
}

bool sacarDeListaD(tListaD* pl, void* info, unsigned tamInfo, Cmp cmp) {
    tNodoD *act, *auxAnt, *auxSig;

    if (*pl == NULL)
        return false;

    act = *pl;

    while (act -> sig && cmp(info, act -> info) > 0)
            act = act -> sig;

    while (act -> ant && cmp(info, act -> info) < 0)
        act = act -> ant;

    if (cmp(info, act -> info) != 0)
        return false;

    memcpy(info, act -> info, MIN(tamInfo, act -> tamInfo));

    auxAnt = act -> ant;
    auxSig = act -> ant;

    if (auxAnt)
        auxAnt -> sig = act -> sig;

    if (auxSig)
        auxSig -> ant = act -> ant;

    *pl = auxAnt ? auxAnt : auxSig;

    free(act -> info);
    free(act);

    return true;
}

int buscarEnListaD(tListaD* pl, void* info, unsigned tamInfo, Cmp cmp) {

    int pos = 0;
    tNodoD *act = *pl;

    if (!act)
        return -1;

    while (act -> ant)
        act = act -> ant;

    while (act -> sig && cmp(info, act -> info) != 0) {
        act = act -> sig;
        pos++;
    }

    if (cmp(info, act -> info) != 0)
        return -1;

    memcpy(info, act -> info, MIN(tamInfo, act -> tamInfo));
    *pl = act;

    return pos;
}

void ordenarListaD(tListaD* pl, Cmp cmp) {

    tNodoD *act, *m, *ini, *auxAnt, *auxSig;

    if (pl == NULL)
        return;

    act = *pl;

    while (act -> ant)
        act = act -> ant;

    ini = act;

    while (ini && ini -> sig) {

        act = m = ini;

        while (act) {

            if (cmp(act -> info, m -> info) < 0)
                m = act;

            act = act -> sig;
        }

        if (m != ini) {
            auxAnt = m -> ant;
            auxSig = m -> sig;

            if (auxAnt)
                auxAnt -> sig = m -> sig;

            if (auxSig)
                auxSig -> ant = m -> ant;

            auxAnt = ini -> ant;

            if (auxAnt)
                auxAnt -> sig = m;

            m -> ant = auxAnt;
            m -> sig = ini;
            ini -> ant = m;

        } else
            ini = ini -> sig;
    }

    *pl = m;
}

void recorrerListaDDesdeInicio(tListaD* pl, Acc acc, void* extra) {

    tNodoD *act = *pl;

    if (act) {
        while (act -> ant)
            act = act -> ant;

        while (act -> sig) {
            acc(act -> info, extra);
            act = act -> sig;
        }

        acc(act -> info, extra);
        *pl = act;
    }
}

void recorrerListaDDesdeFinal(tListaD* pl, Acc acc, void* extra) {

    tNodoD *act = *pl;

    if (act) {
        while (act -> sig)
            act = act -> sig;

        while (act -> ant) {
            acc(act -> info, extra);
            act = act -> ant;
        }

        acc(act -> info, extra);
        *pl = act;
    }
}

void vaciarListaD(tListaD* pl) {

    tNodoD *act, *elim;

    if (*pl == NULL)
        return;

    act = *pl;

    elim = act -> ant;

    while (elim) {
        act -> ant = elim -> ant;

        free(elim -> info);
        free(elim);
        elim = act -> ant;
    }

    elim = act -> sig;

    while (elim) {
        act -> sig = elim -> sig;

        free(elim -> info);
        free(elim);
        elim = act -> sig;
    }

    free(act -> info);
    free(act);

    *pl = NULL;
}

bool listaDVacia(const tListaD* pl) {
    return *pl == NULL;
}

bool listaDLlena(const tListaD* pl, unsigned tamInfo) {
    return false;
}
