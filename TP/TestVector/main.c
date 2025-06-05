#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../TDAVector/Vector.h"

int compararInt (const void* a, const void* b);
void imprimirInt (const void* a);

int main () {

    system("chcp 65001 > nul");

    Vector vec;

    if (!vectorCrear(&vec, sizeof(int)))
        return SIN_MEM;

    srand(time(NULL));

    // for (int i = 0; i < 10; i++) {
    //     int elem = rand() % 100;
    //     vectorInsertarAlFinal(&vec, &elem);
    // }

    // puts("Antes de ordenar:");
    // vectorMostrar(&vec, imprimirInt);
    // printf("\n");

    // time_t segIni = time(NULL);

    // vectorOrdenar(&vec, INSERCION, compararInt);

    // time_t segFin = time(NULL);

    // printf("Tiempo de ordenamiento: %Ids\n", segFin - segIni);

    // puts("Despues de ordenar:");
    // vectorMostrar(&vec, imprimirInt);
    // printf("\n");



    for (int i = 0; i < 6; i++) {
        int elem = i;
        vectorOrdInsertar(&vec, &elem, compararInt);
    }

    int busqueda = 6, pos;

    pos = vectorOrdBuscar(&vec, &busqueda, compararInt);

    vectorMostrar(&vec, imprimirInt);
    printf("\n");
    printf("Posicion: %d", pos);


    //vectorOrdInsertar(&vec, 333);

    // vectorInsertarAlInicio(&vec, 37);
    // vectorInsertarAlFinal(&vec, -4);

    // vectorOrdenar(&vec);

    // vectorInsertarEnPos(&vec, 92, 5);

    // vectorOrdEliminar(&vec, 5);
    // vectorEliminarDePos(&vec, 3);

    //mostrarVector(&vec);

    vectorDestruir(&vec);

    return 0;
}

int compararInt (const void* a, const void* b) {
    int* elem1 = (int*) a;
    int* elem2 = (int*) b;

    return *elem1 - *elem2;
}

void imprimirInt (const void* elem) {
    int* elemInt = (int*) elem;
    printf("%3d", *elemInt);
}
