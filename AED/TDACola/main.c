#include <stdio.h>
#include <stdlib.h>
#include "TDACola.h"

int main() {

    tCola cola;
    int nums[] = { 100, 200, 300, 400, 500, 600, 700, 800 };
    int *i = nums, dato;

    crearCola(&cola);

    while (i < nums + (sizeof(nums) / sizeof(int)) && ponerEnCola(&cola, i, sizeof(int))) {
        i++;
    }

    while (sacarDeCola(&cola, &dato, sizeof(int)))
        printf("Dato: %d\n", dato);


    if (verPriDeCola(&cola, &dato, sizeof(int)))
        printf("Primero de cola: %d\n", dato);
    else
        printf("Cola vacia");

    vaciarCola(&cola);

    if (verPriDeCola(&cola, &dato, sizeof(int)))
        printf("Primero de cola: %d\n", dato);
    else
        printf("Cola vacia");

    return 0;
}
