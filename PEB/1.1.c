#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cargarVecRandom (int[], int, int);
int buscarMin (int[], int);
int buscarMax (int[], int);
int contValIgualA (int[], int, int);
void mostrarPosDeVal (int[], int, int);

int main () {
    int min, max, cantMin, vNums[20], i;

    cargarVecRandom(vNums, 20, 1000);
    min = buscarMin(vNums, 20);
    max = buscarMax(vNums, 20);
    cantMin = contValIgualA(vNums, 20, min);

    for (i = 0; i < 20; i++)
        printf("%d, ", vNums[i]);

    printf("\n");

    printf("El valor minimo del vector es %d y aparece %d veces.\n", min, cantMin);
    printf("El valor maximo del vector es %d.\n", max);

    mostrarPosDeVal(vNums, 20, max);

    return 0;
}

void cargarVecRandom (int vNums[], int tam, int max) {
    int i;

    srand(time(NULL));

    for (i = 0; i < tam; i++)
        vNums[i] = (rand() % (max - (max / 10))) + (max / 10);
}

int buscarMin (int vNums[], int tam) {
    int i, min = vNums[0];

    for (i = 0; i < tam; i++) {
        if (vNums[i] < min)
            min = vNums[i];
    }

    return min;
}

int buscarMax (int vNums[], int tam) {
    int i, max = vNums[0];

    for (i = 0; i < tam; i++) {
        if (vNums[i] > max)
            max = vNums[i];
    }

    return max;
}

int contValIgualA (int vNums[], int tam, int val) {
    int i, cant = 0;

    for (i = 0; i < tam; i++) {
        if (vNums[i] == val)
            cant++;
    }

    return cant;
}

void mostrarPosDeVal (int vNums[], int tam, int val) {
    int i;

    printf("El valor %d se encuentra en las siguientes posiciones:\n", val);

    for (i = 0; i < tam; i++) {
        if (vNums[i] == val)
            printf("%d, ", i);
    }
}