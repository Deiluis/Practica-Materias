#include <stdio.h>
#include <stdlib.h>
#include "../TDALista/TDALista.h"

void imprimirInt(const void* e);
bool tautologia(bool* elem, unsigned cantElem);

int main() {

    tLista lista;
    int dato;
    bool arr[] = {true, true, true, true, true};

    crearLista(&lista);

    dato = 5;
    ponerEnListaAlFinal(&lista, &dato, sizeof(dato), true, NULL);

    dato = 7;
    ponerEnListaAlFinal(&lista, &dato, sizeof(dato), true, NULL);

    mostrarListaInv(&lista, imprimirInt);

    printf("%d", tautologia(arr, 5));

    return 0;
}

void imprimirInt(const void* e) {
    int* n = (int*) e;
    printf("%d, ", *n);
}

bool tautologia(bool* elem, unsigned cantElem) {
    if (cantElem == 0)
        return true;

    return *elem ? tautologia(elem +1, cantElem -1) : false;
}

