#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#define SIN_MEM -1

bool reservarMemoria (int** vec, size_t tam);
void liberarMemoria (int** vec);

int main () {

    int *vec;
    size_t tam;

    printf("Cantidad de elementos que tendrá el array: ");
    scanf("%Iu", &tam);

    srand(time(NULL));

    if (!reservarMemoria(&vec, tam))
        return SIN_MEM;

    int* ult = vec + tam -1;

    for (int* i = vec; i <= ult; i++) {
        *i = rand();
        printf("%d, ", *i);
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
