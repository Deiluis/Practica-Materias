#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../TDAVector/Vector.h"

void mostrarVector(Vector* v);

int main () {

    system("chcp 65001 > nul");

    Vector vec;

    if (!vectorCrear(&vec))
        return SIN_MEM;

    vectorOrdInsertar(&vec, 6);
    vectorOrdInsertar(&vec, 8);
    vectorOrdInsertar(&vec, 5);
    vectorOrdInsertar(&vec, 3);
    vectorOrdInsertar(&vec, 10);
    vectorOrdInsertar(&vec, 79);
    vectorOrdInsertar(&vec, 9);
    vectorOrdInsertar(&vec, 11);
    vectorOrdInsertar(&vec, 45);


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

void mostrarVector (Vector* v) {
    int i;

    for (i = 0; i < v -> tam; i++)
        printf("%d, ", v -> vec[i]);
}
