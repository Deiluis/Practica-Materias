#include <stdio.h>

void cargar (int[], int);
void mostrar(int[], int);

int main () {

    int vNums[10];

    cargar(vNums, 10);
    mostrar(vNums, 10);

    return 0;
}

void cargar (int vec[], int tam) {
    int i;

    for (i = 0; i < tam; i++) {
        printf("Cargue el entero numero %d: ", i+1);
        scanf("%d", vec+i);
    }
}

void mostrar(int vec[], int tam) {
    int i;

    printf("Vector cargado:\n");

    for (i = 0; i < tam; i++) {
        printf("%d, ", *(vec+i));
    }
}
