#include <stdbool.h>
#include "Vector.h"

bool vectorCrear (Vector* v) {
    v -> tam = 0;
    return true;
}

int vectorOrdInsertar(Vector* v, int elem) {

    if (v -> tam == TAM)
        return LLENO;

    int *i, *posIns, *ult;
    ult = v -> vec + v -> tam -1;

    posIns = v -> vec;

    while (posIns <= ult && *posIns < elem)
        posIns++;

    if (posIns <= ult && *posIns == elem)
        return DUPLICADO;

    for (i = ult; i >= posIns; i--)
        *(i+1) = *i;

    *posIns = elem;
    v -> tam++;

    return OK;
}

int vectorInsertarAlInicio(Vector* v, int elem) {
    if (v -> tam == TAM)
        return LLENO;

    int pos = vectorDesordBuscar(v, elem);

    if (pos != -1)
        return DUPLICADO;

    int *i, *posIns, *ult;
    i = v -> vec + 1;
    ult = v -> vec + v -> tam -1;
    posIns = v -> vec;

    for (i = ult; i >= posIns; i--)
        *(i+1) = *i;

    *posIns = elem;
    v -> tam++;

    return OK;
}

int vectorInsertarAlFinal(Vector* v, int elem) {
    if (v -> tam == TAM)
        return LLENO;

    int pos = vectorDesordBuscar(v, elem);

    if (pos != -1)
        return DUPLICADO;

    int *posIns;
    posIns = v -> vec + v -> tam;

    *posIns = elem;
    v -> tam++;

    return OK;
}

int vectorInsertarEnPos(Vector* v, int elem, int pos) {
    if (v -> tam == TAM)
        return LLENO;

    if (pos < 0)
        return FUERA_RANGO;

    int posExistente = vectorDesordBuscar(v, elem);

    if (posExistente != -1)
        return DUPLICADO;

    int *posIns, *i, *ult;
    posIns = v -> vec + pos;
    ult = v -> vec + v -> tam -1;

    if (posIns > ult)
        return FUERA_RANGO;

    for (i = ult; i >= posIns; i--)
        *(i+1) = *i;

    *posIns = elem;
    v -> tam++;

    return OK;
}

int vectorOrdBuscar(const Vector* v, int elem) {

    if (v -> tam == 0)
        return -1;

    const int *li, *ls, *m;

    li = v -> vec;
    ls = v -> vec + v -> tam -1;
    m = li + (ls - li) / 2;

    while (li <= ls && *m != elem) {

        if (elem > *m)
            li = m + 1;
        else
            ls = m - 1;

        m = li + (ls - li) / 2;
    }

    if (*m == elem)
        return m - v -> vec;

    return -1;
}

int vectorDesordBuscar(const Vector* v, int elem) {

    if (v -> tam == 0)
        return -1;

    const int *i, *ult;
    int pos;

    i = v -> vec;
    ult = v -> vec + v -> tam -1;
    pos = -1;

    while (pos == -1 && i <= ult) {
        if (*i == elem)
            pos = i - v -> vec;
        else
            i++;
    }

    return pos;
}

bool vectorOrdEliminar (Vector* v, int elem) {
    int pos = vectorOrdBuscar(v, elem);

    if (pos == -1)
        return false;

    vectorEliminarDePos(v, pos);

    return true;
}

bool vectorEliminarDePos (Vector* v, int pos) {

    if (pos < 0)
        return false;

    int *i, *ult;
    i = v -> vec + pos;
    ult = v -> vec + v -> tam -1;

    if (i > ult)
        return false;

    while (i < ult) {
        *i = *(i + 1);
        i++;
    }

    v -> tam--;

    return true;
}

void vectorOrdenar (Vector* v) {
    if (v -> tam == 0)
        return;

    int aux, i, *j, *ult;
    ult = v -> vec + v -> tam -1;

    for (i = 0; i < v -> tam -1; i++) {
        for (j = v -> vec; j < ult - i; j++) {
            if (*j > *(j+1)) {
                aux = *(j+1);
                *(j+1) = *j;
                *j = aux;
            }
        }
    }
}

void vectorVaciar (Vector* v) {
    v -> tam = 0;
}

void vectorDestruir (Vector* v) {
    v -> tam = 0;
}
