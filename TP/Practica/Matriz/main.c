#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define FILAS 5
#define COLUMNAS 5

#define SIN_MEM 1

void** crearMatriz (size_t tamElem, size_t filas, size_t columnas);
void destruirMatriz (void** matriz, size_t filas);
void mostrarMatriz (int matriz[][COLUMNAS], size_t filas, size_t columnas);
void inicializarMatriz (int matriz[][COLUMNAS], size_t filas, size_t columnas);
int recorrerEspiral (int** matriz, size_t filas, size_t columnas);
void trasponerCuadradaInSitu (int** matriz, size_t orden);
void imprimirInt (const void* elem);

int main () {

    //int** matriz = (int**) crearMatriz(sizeof(int), FILAS, COLUMNAS);

    int (*matriz)[] = malloc(FILAS * COLUMNAS * sizeof(int));

    if (!matriz)
        return SIN_MEM;

    inicializarMatriz(matriz, FILAS, COLUMNAS);

    mostrarMatriz(matriz, FILAS, COLUMNAS);

    // trasponerCuadradaInSitu(matriz, FILAS);

    // mostrarMatriz(matriz, FILAS, COLUMNAS);

    // destruirMatriz((void**) matriz, FILAS);

    return 0;
}

void** crearMatriz (size_t tamElem, size_t filas, size_t columnas) {

    void** matriz = malloc(filas * sizeof(void*));

    if (!matriz)
        return NULL;

    void** i = matriz;
    void** ult = matriz + (filas -1);

    bool memInsuficiente = false;

    while (!memInsuficiente && i <= ult) {

        *i = malloc(columnas * tamElem);

        if (*i)
            i++;
        else {
            destruirMatriz(matriz, i - matriz);
            matriz = NULL;
            memInsuficiente = true;
        }
    }

    return matriz;
}

void destruirMatriz (void** matriz, size_t filas) {

    void** i;
    void** ult = matriz + (filas -1);

    for (i = matriz; i <= ult; i++)
        free(*i);

    free(matriz);
}

void mostrarMatriz (int matriz[][COLUMNAS], size_t filas, size_t columnas) {

    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++)
            printf("%3d", matriz[i][j]);

        printf("\n");
    }
}

void inicializarMatriz (int matriz[][COLUMNAS], size_t filas, size_t columnas) {

    int i, j;
    int valor = 1;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            matriz[i][j] = valor;
            valor++;
        }
    }
}

int recorrerEspiral (int** matriz, size_t filas, size_t columnas) {

    int i, suma = 0;
    int arriba = 0, abajo = filas -1, izquierda = 0, derecha = columnas -1;

    while (arriba <= abajo && izquierda <= derecha) {

        for (i = izquierda; i <= derecha; i++) {
            suma += matriz[arriba][i];
        }

        arriba++;

        for (i = arriba; i <= abajo; i++) {
            suma += matriz[i][derecha];
        }

        derecha--;


        for (i = derecha; i >= izquierda; i--) {
            suma += matriz[abajo][i];
        }

        abajo--;

        for (i = abajo; i >= arriba; i--) {
            suma += matriz[i][izquierda];
        }

        izquierda++;
    }

    return suma;
}

void trasponerCuadradaInSitu (int** matriz, size_t orden) {

    int i, j, temp;

    for (i = 0; i < orden; i++) {
        for (j = i + 1; j < orden; j++) {
            temp = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = temp;
        }
    }
}

void imprimirInt (const void* elem) {
    const int* n = elem;

    printf("%3d", *n);
}
