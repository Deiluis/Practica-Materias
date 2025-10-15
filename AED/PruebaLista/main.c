#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../TDAListaD/ListaD.h"

#define CANT_ELEM 20
#define MAX 1000

void mostrarInt (const void* elem);
int compararInt (const void* e1, const void* e2);

int main()
{
    tLista lista;
    int i = 0;
    int dato;
    bool err = false;

    crearLista(&lista);

    srand(time(NULL));

    while (!err && i < CANT_ELEM) {
        dato = rand() % MAX;
        err = !ponerEnListaEnOrden(&lista, &dato, sizeof(int), compararInt, NULL);
        i++;
    }


    printf("Lista: ");
    mostrarListaDesdeElFinal(&lista, mostrarInt);
    printf("\n");

//    if (!sacarDeLista(&lista, &dato, sizeof(int), compararInt)) {
//        printf("\nError al sacar de lista\n");
//    }


    vaciarLista(&lista);

    printf("Lista: ");
    mostrarListaDesdeElFinal(&lista, mostrarInt);
    printf("\n");

    dato = 5;
    ponerEnListaEnOrden(&lista, &dato, sizeof(int), compararInt, NULL);

    printf("Lista: ");
    mostrarListaDesdeElFinal(&lista, mostrarInt);
    printf("\n");


//    if (err) {
//        printf("Error cargando la lista. Vaciando...\n");
//        vaciarLista(&lista);
//    }
//
//    printf("Antes de ordenar:\n");
//    mostrarLista(&lista, mostrarInt);
//    printf("\n\n");
//
//    ordenarLista(&lista, compararInt, SELECCION);
//
//    printf("Despues de ordenar:\n");
//    mostrarLista(&lista, mostrarInt);

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
