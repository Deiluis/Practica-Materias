#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Vector.h"

// Internas
bool redimensionarVector (Vector* v, int operacion);
int ordenarBurbujeo (Vector* v, Cmp cmp);
int ordenarSeleccion (Vector* v, Cmp cmp);
void ordenarSeleccionDoble (Vector* v, Cmp cmp);
int ordenarInsercion (Vector* v, Cmp cmp);
void intercambiar (void* a, void* b, void* aux, size_t tamElem);
void* buscarMenor (void* ini, void* fin, size_t tamElem, Cmp cmp);

bool vectorCrear (Vector* v, size_t tamElem) {
    v -> tam = 0;
    v -> tamElem = tamElem;
    v -> vec = malloc(CAP_INI * tamElem);

    if (v -> vec == NULL) {
        v -> cap = 0;
        return false;
    }

    v -> cap = CAP_INI;

    return true;
}

int vectorCrearDeArchivo (Vector* v, size_t tamElem, const char* nomArch) {

    FILE* arch = fopen(nomArch, "rb");

    if (!arch)
        return ERR_ARCHIVO;

    fseek(arch, 0, SEEK_END);
    size_t tamArchivo = ftell(arch);

    v -> vec = malloc(tamArchivo);

    if (v -> vec == NULL) {
        fclose(arch);
        v -> cap = 0;
        return SIN_MEM;
    }

    v -> tam = tamArchivo / tamElem;
    v -> cap = v -> tam;
    v -> tamElem = tamElem;

    rewind(arch); // equivalente a fseek desde 0 SEEK_SET

    fread(v -> vec, tamElem, v -> tam, arch);
    fclose(arch);

    return OK;
}

int vectorGrabar(Vector* v, const char* nomArch) {

    FILE* arch = fopen(nomArch, "wb");

    if (!arch)
        return ERR_ARCHIVO;

    fwrite(v -> vec, v -> tamElem, v -> tam, arch);

    fclose(arch);

    return OK;
}

int vectorOrdInsertar(Vector* v, void* elem, Cmp cmp) {

    if (v -> tam == v -> cap) {
        if (!redimensionarVector(v, AUMENTAR))
            return SIN_MEM;
    }

    void *i, *posIns, *ult;
    ult = v -> vec + (v -> tam -1) * v -> tamElem;

    posIns = v -> vec;

    while (posIns <= ult && cmp(posIns, elem) < 0)
        posIns += v -> tamElem;

    if (posIns <= ult && cmp(posIns, elem) == 0)
        return DUPLICADO;

    for (i = ult; i >= posIns; i -= v -> tamElem)
        memcpy(i + v -> tamElem, i, v -> tamElem);

    memcpy(posIns, elem, v -> tamElem);
    v -> tam++;

    return OK;
}

int vectorInsertarAlInicio(Vector* v, void* elem, Cmp cmp) {
    if (v -> tam == TAM)
        return LLENO;

    int pos = vectorDesordBuscar(v, elem, cmp);

    if (pos != -1)
        return DUPLICADO;

    void *i, *posIns, *ult;

    ult = v -> vec + (v -> tam -1) * v -> tamElem;
    posIns = v -> vec;

    for (i = ult; i >= posIns; i -= v -> tamElem)
        memcpy(i + v -> tamElem, i, v -> tamElem);

    memcpy(posIns, elem, v -> tamElem);
    v -> tam++;

    return OK;
}

int vectorInsertarAlFinal(Vector* v, void* elem) {

    if (v -> tam == v -> cap) {
        if (!redimensionarVector(v, AUMENTAR))
            return SIN_MEM;
    }

    void *posIns;
    posIns = v -> vec + v -> tam * v -> tamElem;

    memcpy(posIns, elem, v -> tamElem);
    v -> tam++;

    return OK;
}

int vectorInsertarEnPos(Vector* v, void* elem, int pos, Cmp cmp) {
    if (v -> tam == TAM)
        return LLENO;

    if (pos < 0)
        return FUERA_RANGO;

    int posExistente = vectorDesordBuscar(v, elem, cmp);

    if (posExistente != -1)
        return DUPLICADO;

    void *posIns, *i, *ult;
    posIns = v -> vec + pos * v -> tamElem;
    ult = v -> vec + (v -> tam -1) * v -> tamElem;

    if (posIns > ult)
        return FUERA_RANGO;

    for (i = ult; i >= posIns; i -= v -> tamElem)
        memcpy(i + v -> tamElem, i, v -> tamElem);

    memcpy(posIns, elem, v -> tamElem);
    v -> tam++;

    return OK;
}

int vectorModificarDePos (Vector* v, int pos, void* elem) {

    if (pos < 0 || pos > v -> tam -1)
        return FUERA_RANGO;

    void* posModif = v -> vec + pos * v -> tamElem;

    memcpy(posModif, elem, v -> tamElem);

    return OK;
}

int vectorDesordBuscar (const Vector* v, void* elem, Cmp cmp) {

    int pos = -1;
    void* i = v -> vec;
    void* ult = v -> vec + (v -> tam -1) * v -> tamElem;

    while (pos == -1 && i <= ult) {
        if (cmp(elem, i) == 0)
            pos = (i - v -> vec) / v -> tamElem;
        else
            i += v -> tamElem;
    }

    if (pos != -1)
        memcpy(elem, i, v -> tamElem);

    return pos;
}

int vectorOrdBuscar (const Vector* v, void* elem, Cmp cmp) {

    if (v -> tam == 0)
        return -1;

    void* li = v -> vec;
    void* ls = v -> vec + (v -> tam -1) * v -> tamElem;

    void* m = li + ((ls - li) / (2 * v -> tamElem)) * v -> tamElem;

    while (li <= ls && cmp(elem, m) != 0) {

        if (cmp(elem, m) > 0)
            li = m + v -> tamElem;
        else
            ls = m - v -> tamElem;

        m = li + ((ls - li) / (2 * v -> tamElem)) * v -> tamElem;
    }

    if (li > ls)
        return -1;

    memcpy(elem, m, v -> tamElem);

    return (m - v -> vec) / v -> tamElem;
}

int ordenarBurbujeo (Vector* v, Cmp cmp) {

    void* aux = malloc (v -> tamElem);

    if (!aux)
        return SIN_MEM;

    int i;
    void* j;
    void* ult = v -> vec + (v -> tam -1) * v -> tamElem;

    for (i = 0; i < v -> tam -1; i++) {
        for (j = v -> vec; j < ult - i; j += v -> tamElem) {
            if (cmp(j, j+1) > 0)
                intercambiar(j, j+1, aux, v -> tamElem);
        }
    }

    free(aux);

    return OK;
}

int ordenarSeleccion (Vector* v, Cmp cmp) {

    void* aux = malloc (v -> tamElem);

    if (!aux)
        return SIN_MEM;

    void *i, *m;
    void* ult = v -> vec + (v -> tam -1) * v -> tamElem;

    for (i = v -> vec; i < ult; i += v -> tamElem) {
        m = buscarMenor(i, ult, v -> tamElem, cmp);
        intercambiar(i, m, aux, v -> tamElem);
    }

    free(aux);

    return OK;
}

int ordenarInsercion (Vector* v, Cmp cmp) {

    void* aux = malloc(v -> tamElem);

    if (!aux)
        return SIN_MEM;

    void *i, *j, *ult;
    ult = v -> vec + (v -> tam -1) * v -> tamElem;

    for (i = v -> vec + v -> tamElem; i <= ult; i += v -> tamElem) {

        memcpy(aux, i, v -> tamElem);
        j = i - v -> tamElem;

        while (j >= v -> vec && cmp(j, aux) > 0) {
            memcpy(j + v -> tamElem, j, v -> tamElem);
            j -= v -> tamElem;
        }

        // memmove(j + v -> tamElem * 2, j + v -> tamElem, i - j + v -> tamElem);

        memcpy(j + v -> tamElem, aux, v -> tamElem);
    }

    free(aux);

    return OK;
}


void intercambiar (void* a, void* b, void* aux, size_t tamElem) {
    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);
}

void* buscarMenor (void* ini, void* fin, size_t tamElem, Cmp cmp) {

    void* j;
    void* m = ini;

    for (j = ini; j <= fin; j += tamElem) {
        if (cmp(j, m) < 0)
            m = j;
    }

    return m;
}








bool vectorOrdEliminar (Vector* v, void* elem, Cmp cmp) {
    int pos = vectorOrdBuscar(v, elem, cmp);

    if (pos == -1)
        return false;

    vectorEliminarDePos(v, pos);

    return true;
}

bool vectorEliminarDePos (Vector* v, int pos) {

    if (pos < 0 || pos >= v -> tam -1)
        return false;

    void *i, *ult;
    ult = v -> vec + v -> tam -1;

    for (i = v -> vec + pos * v -> tamElem; i < ult; i += v -> tamElem)
        memcpy(i, i + v -> tamElem, v -> tamElem);

    v -> tam--;

    if ((float) v -> tam / v -> cap <= FACTOR_OCUP)
        redimensionarVector(v, DISMINUIR);

    return true;
}

void vectorOrdenar (Vector* v, int metodo, Cmp cmp) {

    switch (metodo) {
        case BURBUJEO:
            ordenarBurbujeo(v, cmp);
            break;

        case SELECCION:
            ordenarSeleccion(v, cmp);
            break;

        case SELECCION_DOBLE:
            // ordenarSeleccionDoble(v, cmp);
            break;

        case INSERCION:
            ordenarInsercion(v, cmp);
            break;

        case QUICK_SORT:
            qsort(v -> vec, v -> tam, v -> tamElem, cmp);

    }
}

void vectorVaciar (Vector* v) {
    v -> tam = 0;
}

void vectorDestruir (Vector* v) {
    free(v -> vec);
    v -> tam = 0;
    v -> cap = 0;
    v -> tamElem = 0;
    v -> vec = NULL;
}

void vectorMostrar (const Vector* v, Imp imp) {

    void* i;
    void* ult = v -> vec + (v -> tam -1) * v -> tamElem;

    for (i = v -> vec; i <= ult; i += v -> tamElem)
        imp(i);
}

void vectorRecorrer (const Vector* v, Accion accion, void* datos) {

    void* i;
    void* ult = v -> vec + (v -> tam -1) * v -> tamElem;

    for (i = v -> vec; i <= ult; i += v -> tamElem)
        accion(i, datos);
}

bool redimensionarVector (Vector* v, int operacion) {
    size_t nCap = operacion == AUMENTAR
    ? v -> cap * FACTOR_INCR
    : max(v -> cap * FACTOR_DECR, CAP_INI);

    int* nVec = realloc(v -> vec, nCap * v -> tamElem);

    if (nVec == NULL)
        return false;

    printf("Redimension de %d a %d\n", (int) v -> cap, (int) nCap);

    v -> vec = nVec;
    v -> cap = nCap;

    return true;
}

// void ordenarBurbujeo (Vector* v, Cmp cmp) {

//     int i;
//     void *j, *ult;
//     ult = v -> vec + (v -> tam -1) * v -> tamElem;

//     for (i = 0; i < v -> tam -1; i++) {

//         for (j = v -> vec; j < ult - i * v -> tamElem; j += v -> tamElem) {
//             if (cmp(j, j + v -> tamElem) > 0) {
//                 intercambiar(j, j + v -> tamElem, v -> tamElem);
//             }
//         }
//     }
// }

// void ordenarSeleccion (Vector* v, Cmp cmp) {

//     void *i, *m, *ult;
//     ult = v -> vec + (v -> tam -1) * v -> tamElem;

//     for (i = v -> vec; i < ult; i += v -> tamElem) {
//         m = buscarMenor(i, ult, v -> tamElem, cmp);
//         intercambiar(i, m, v -> tamElem);
//     }

// }

// void ordenarSeleccionDoble (Vector* v, Cmp cmp) {

//     void *i1, *i2, *j, *m, *M;

//     i1 = v -> vec;
//     i2 = v -> vec + (v -> tam -1) * v -> tamElem;

//     while (i1 < i2) {

//         m = i1;
//         M = i2;

//         for (j = i1; j <= i2; j += v -> tamElem) {

//             if (cmp(j, m) < 0)
//                 m = j;

//             if (cmp(j, M) > 0)
//                 M = j;
//         }

//         intercambiar(i1, m, v -> tamElem);

//         if (i1 == M)
//             M = m;

//         intercambiar(i2, M, v -> tamElem);

//         i1 += v -> tamElem;
//         i2 -= v -> tamElem;
//     }
// }

// void ordenarInsercion (Vector* v, Cmp cmp) {

//     void *i, *j, *ult, *elem;
//     ult = v -> vec + (v -> tam -1) * v -> tamElem;

//     elem = malloc(v -> tamElem);

//     for (i = v -> vec + v -> tamElem; i <= ult; i += v -> tamElem) {

//         memcpy(elem, i, v -> tamElem);
//         j = i - v -> tamElem;

//         while (j >= v -> vec && cmp(j, elem) > 0) { // Podría mover todo el bloque con memmove
//             memcpy(j + v -> tamElem, j, v -> tamElem);
//             j -= v -> tamElem;
//         }

//         memcpy(j + v -> tamElem, elem, v -> tamElem);
//     }

//     free(elem);
// }

// void* buscarMenor (void* ini, void* fin, size_t tamElem, Cmp cmp) {

//     void *m, *j;
//     m = ini;

//     for (j = ini + tamElem; j <= fin; j += tamElem) {

//         if (cmp(j, m) < 0)
//             m = j;
//     }

//     return m;
// }

// void ordenarBurbujeo (Vector* v) {

//     int i, *j, *ult;
//     ult = v -> vec + v -> tam -1;

//     for (i = 0; i < v -> tam -1; i++) {

//         for (j = v -> vec; j < ult - i; j++) {
//             if (*j > *(j+1)) {
//                 intercambiar(j, j+1);
//             }
//         }
//     }
// }

// void ordenarSeleccion (Vector* v) {

//     int *i, *m, *ult;
//     ult = v -> vec + v -> tam -1;

//     for (i = v -> vec; i < ult; i++) {
//         m = buscarMenor(i, ult);
//         intercambiar(i, m);
//     }
// }

// void ordenarInsercion (Vector* v) {

//     int *i, *j, *ult;
//     ult = v -> vec + v -> tam -1;
//     int elemAIns;

//     for (i = v -> vec +1; i <= ult; i++) {
//         elemAIns = *i;

//         j = i -1;

//         while (j >= v -> vec && elemAIns < *j) {
//             *(j + 1) = *j;
//             j--;
//         }

//         *(j + 1) = elemAIns;
//     }

// }

// int* buscarMenor(int* ini, int* fin) {
//     int* m = ini;
//     int* j;

//     for (j = ini + 1; j <= fin; j++) {
//         if (*j < *m)
//             m = j;
//     }

//     return m;
// }

// void intercambiar (void* a, void* b, size_t tamElem) {

//     void* aux = malloc(tamElem);

//     memcpy(aux, a, tamElem);
//     memcpy(a, b, tamElem);
//     memcpy(b, aux, tamElem);

//     free(aux);
// }

size_t max (size_t a, size_t b) {
    return a >= b ? a : b;
}


// Vector iterador

void vectorIteradorCrear (VectorIterador* it, const Vector* v) {
    it -> act = NULL;
    it -> ult = NULL;
    it -> finIter = true;
    it -> vector = (Vector*) v;
}

void* vectorIteradorPrimero (VectorIterador* it) {
    Vector* v = it -> vector;

    if (v -> tam == 0) {
        it -> act = NULL;
        it -> ult = NULL;
        it -> finIter = true;
        return NULL;
    }

    it -> act = v -> vec;
    it -> ult = v -> vec + (v -> tam -1) * v -> tamElem;
    it -> finIter = false;

    return it -> act;
}

void* vectorIteradorSiguiente (VectorIterador* it) {

    Vector* v = it -> vector;

    void* siguiente = it -> act + v -> tamElem;

    if (siguiente > it -> ult) {
        it -> finIter = true;
        return NULL;
    }

    it -> act = siguiente;

    return siguiente;
}

bool vectorIteradorFin (VectorIterador* it) {
    return it -> finIter;
}
