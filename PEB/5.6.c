#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cargar (int[], int);
void mostrar(int[], int);
int* buscarMax(int[], int);

int main () {

    int vNums[10];
    int val, *pMax;

    srand(time(NULL));

    cargar(vNums, 10);
    mostrar(vNums, 10);

    pMax = buscarMax(vNums, 10);

    printf("\n");
    printf("Valor maximo del vector: %d\n", *pMax);
    printf("Posicion de ese valor en el vector: %d", pMax - vNums +1);

    return 0;
}

void cargar (int vec[], int tam) {
    int i;

    for (i = 0; i < tam; i++) {
        *(vec+i) = rand() % 1000;
    }
}

void mostrar(int vec[], int tam) {
    int i;

    printf("Vector cargado:\n");

    for (i = 0; i < tam; i++) {
        printf("%d, ", *(vec+i));
    }
}

int* buscarMax(int vec[], int tam) {
    int i, max = *vec, *pMax = vec;

    for (i = 1; i < tam; i++) {
        if (*(vec+i) > max) {
            max = *(vec+i);
            pMax = vec+i;
        }
    }

    return pMax;
}