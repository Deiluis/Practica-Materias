#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIN_MEM -1

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
    size_t tam = 5;

    srand(time(NULL));

    if (!reservarMemoria(&vec, tam))
        return SIN_MEM;

    int* ult = vec + tam -1;

    for (int* i = vec; i <= ult; i++) {
        *i = rand();
        printf("%d, ", *i);
    }

    for (Datamix* i = vec; i <= ult; i++) {
        i -> num = rand();
        strcpy(i -> str, "Hola");

        printf("num: %d\n", i -> num);
        printf("str: %s\n", i -> str);
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
