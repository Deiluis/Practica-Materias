#include <stdio.h>
#include <stdlib.h>
// #include "../TDAPilaDinamica/Pila.h"
#include "../TDAColaDinamica/Cola.h"

int main () {

    // tPila pila;
    tCola cola;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int dato;
    int* i;
    bool memLibre = true;

    crearCola(&cola);

    i = nums;
    memLibre = ponerEnCola(&cola, i, sizeof(int));
    i++;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = ponerEnCola(&cola, i, sizeof(int));
        i++;
    }

    if (!memLibre) {
        vaciarCola(&cola);
        printf("Memoria insuficiente");
    }

    while (sacarDeCola(&cola, &dato, sizeof(int)))
        printf("%d\n", dato);

    if (verPrimero(&cola, &dato, sizeof(dato)))
        printf("primero: %d\n", dato);
    else
        printf("cola vacia");

//    crearPila(&pila);
//
//    for (i = nums; i < nums + (sizeof(nums) / sizeof(int)); i++) {
//        if (!apilar(&pila, i, sizeof(*i))) {
//            printf("Memoria insuficiente");
//            // Dejar de apilar y liberar
//        }
//    }
//
//    vaciarPila(&pila);
//
//    i = nums;
//
//    while (i < nums + (sizeof(nums) / sizeof(int)) && desapilar(&pila, &dato, sizeof(dato))) {
//        printf("%d\n", dato);
//        i++;
//    }
//
//    if (verTope(&pila, &dato, sizeof(dato)))
//        printf("Tope: %d\n", dato);
//    else
//        printf("Pila vacia");


    return 0;
}
