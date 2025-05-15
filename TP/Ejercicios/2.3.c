#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    char str[11];
    int num;
    char c;
    float f;
} Datamix;

bool reservarMemoria (Datamix** vec, size_t tam);
void liberarMemoria (Datamix** vec);

int main () {

    Datamix *vec;
    int i;
    size_t tam = 5;

    srand(time(NULL));

    if (!reservarMemoria(&vec, tam))
        return -1;

    for (i = 0; i < tam; i++) {
        (vec + i) -> num = rand();
        strcpy((vec + i) -> str, "Hola");

        printf("num: %d\n", (vec + i) -> num);
        printf("str: %s\n", (vec + i) -> str);
    }

    liberarMemoria(&vec);

    return 0;
}

bool reservarMemoria (Datamix** vec, size_t tam) {
    *vec = malloc(tam * sizeof(Datamix));
    return *vec != NULL;
}

void liberarMemoria (Datamix** vec) {
    free(*vec);
    *vec = NULL;
}
