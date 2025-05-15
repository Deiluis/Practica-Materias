#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

bool reservarMemoria (int** vec, size_t tam);
void liberarMemoria (int** vec);

int main () {

    int *vec, i;
    size_t tam = 10;

    srand(time(NULL));

    if (!reservarMemoria(&vec, tam))
        return -1;

    for (i = 0; i < tam; i++) {
        *(vec + i) = rand();
        printf("%d, ", *(vec + i));
    }

    liberarMemoria(&vec);

    return 0;
}

bool reservarMemoria (int** vec, size_t tam) {
    *vec = malloc(tam * sizeof(int));
    return *vec != NULL;
}

void liberarMemoria (int** vec) {
    free(*vec);
    *vec = NULL;
}
