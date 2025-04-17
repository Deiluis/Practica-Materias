#include <stdio.h>
#include "../TDAVector/Vector.h"

void mostrarVector(Vector* v);

int main () {

    Vector vec;

    vectorCrear(&vec);

    vectorOrdInsertar(&vec, 6);
    vectorOrdInsertar(&vec, 8);
    vectorOrdInsertar(&vec, 5);
    vectorOrdInsertar(&vec, 3);
    vectorOrdInsertar(&vec, 10);
    vectorOrdInsertar(&vec, 79);

    vectorInsertarAlInicio(&vec, 37);
    vectorInsertarAlFinal(&vec, -4);

    vectorOrdenar(&vec);

    vectorInsertarEnPos(&vec, 92, 5);

    vectorOrdEliminar(&vec, 5);
    vectorEliminarDePos(&vec, 3);

    mostrarVector(&vec);

    return 0;
}

void mostrarVector (Vector* v) {
    int i;

    for (i = 0; i < v -> tam; i++)
        printf("%d, ", v -> vec[i]);
}
