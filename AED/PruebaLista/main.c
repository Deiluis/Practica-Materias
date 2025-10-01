#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../TDALista/TDALista.h"

#define CANT_ELEM 20
#define MAX 1000

void mostrarInt (const void* elem);
int compararInt (const void* e1, const void* e2);

int main()
{
    tLista lista;
    int i = 0, dato;
    bool err = false;

    crearLista(&lista);

    srand(time(NULL));

    while (!err && i < CANT_ELEM) {
        dato = rand() % MAX;
        err = !ponerEnListaAlFinal(&lista, &dato, sizeof(int), true, NULL);
        i++;
    }

    if (err) {
        printf("Error cargando la lista. Vaciando...\n");
        vaciarLista(&lista);
    }

    printf("Antes de ordenar:\n");
    mostrarLista(&lista, mostrarInt);
    printf("\n\n");

    ordenarLista(&lista, compararInt, SELECCION);

    printf("Despues de ordenar:\n");
    mostrarLista(&lista, mostrarInt);

    return 0;
}

void mostrarInt (const void* elem) {
    int* num = (int*) elem;
    printf("%d, ", *num);
}

int compararInt (const void* e1, const void* e2) {
    int* n1 = (int*) e1;
    int* n2 = (int*) e2;

    return *n1 - *n2;
}
