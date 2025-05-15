#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

bool vectorCrear (Vector* v) {
    v -> tam = 0;
    v -> vec = malloc(CAP_INI * sizeof(int));

    if (v -> vec == NULL) {
        v -> cap = 0;
        return false;
    }

    v -> cap = CAP_INI;

    return true;
}

int vectorOrdInsertar(Vector* v, int elem) {

    if (v -> tam == v -> cap) {
        if (!redimensionarVector(v, AUMENTAR))
            return SIN_MEM;
    }

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

    if (pos < 0 || pos >= v -> tam -1)
        return false;

    int *i, *ult;
    ult = v -> vec + v -> tam -1;

    for (i = v -> vec + pos; i < ult; i++)
        *i = *(i + 1);

    v -> tam--;

    if ((float) v -> tam / v -> cap <= FACTOR_OCUP)
        redimensionarVector(v, DISMINUIR);

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
    free(v -> vec);
    v -> tam = 0;
    v -> cap = 0;
    v -> vec = NULL;
}

bool redimensionarVector (Vector* v, int operacion) {
    size_t nCap = operacion == AUMENTAR
    ? v -> cap * FACTOR_INCR
    : max(v -> cap * FACTOR_DECR, CAP_INI);

    int* nVec = realloc(v -> vec, nCap * sizeof(int));

    if (nVec == NULL)
        return false;

    printf("Redimension de %Iu a %Iu\n", v -> cap, nCap);

    v -> vec = nVec;
    v -> cap = nCap;

    return true;
}

size_t max (size_t a, size_t b) {
    return a >= b ? a : b;
}