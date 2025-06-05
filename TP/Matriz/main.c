#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define FILAS 4
#define COLUMNAS 4
#define ORDEN 4

void** crearMatriz (size_t tamElem, int filas, int columnas);
void destruirMatriz (void** mat, int filas);

void inicializarMatriz(int filas, int columnas, int** mat);
void mostrarMatriz(int** mat, int filas);
int sumaDiagonalPrincipal(int orden, int** mat);
int sumaDiagonalSecundaria(int orden, int** mat);
int sumaTInferiorDPrincipal(int orden, int** mat);
int sumaTSuperiorDSecundaria(int orden, int** mat);

int main()
{
    // int matriz[FILAS][COLUMNAS] =
    // {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {9, 10, 11, 12},
    //     {13, 14, 15, 16},
    // };

    //int (*matriz)[ORDEN] = malloc (sizeof(int) * ORDEN * ORDEN);
    int suma;

    int** matriz = (int**) crearMatriz(sizeof(int), ORDEN, ORDEN);

    if (!matriz)
        return 1;

    inicializarMatriz(ORDEN, ORDEN, matriz);

    suma = sumaDiagonalPrincipal(ORDEN, matriz);

    mostrarMatriz(matriz, FILAS);
    printf("Suma diagonal principal: %d\n", suma);

    suma = sumaDiagonalSecundaria(ORDEN, matriz);
    printf("Suma diagonal secundaria: %d\n", suma);

    suma = sumaTInferiorDPrincipal(ORDEN, matriz);
    printf("Suma triangular inferior diagonal principal: %d\n", suma);

    suma = sumaTSuperiorDSecundaria(ORDEN, matriz);
    printf("Suma triangular superior diagonal secundaria: %d\n", suma);

    //free(matriz);
    destruirMatriz ((void**) matriz, ORDEN);

    return 0;
}

void** crearMatriz (size_t tamElem, int filas, int columnas) {

    void** matriz = malloc (filas * sizeof(void*));

    if (!matriz)
        return NULL;

    void** ult = matriz + filas -1;

    for (void** i = matriz; i <= ult; i++) {
        *i = malloc (tamElem * columnas);

        if (!*i)
            destruirMatriz(matriz, i - matriz);
    }

    return matriz;
}

void destruirMatriz (void** mat, int filas) {

    void** ult = mat + filas -1;

    for (void** i = mat; i <= ult; i++)
        free(*i);

    free(mat);
}

void inicializarMatriz(int filas, int columnas, int** mat) {
    int i, j, cont = 1;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            mat[i][j] = cont++;
        }
    }
}

void mostrarMatriz(int** mat, int filas) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            printf("%3d", mat[i][j]);
        }

        printf("\n");
    }
}

int sumaDiagonalPrincipal(int orden, int** mat) {

    int i, suma = 0;

    for (i = 0; i < orden; i++)
        suma += mat[i][i];

    return suma;
}

int sumaDiagonalSecundaria(int orden, int** mat) {

    int i, suma = 0;

    for (i = 0; i < orden; i++)
        suma += mat[i][orden - i - 1];

    return suma;
}

int sumaTInferiorDPrincipal(int orden, int** mat) {

    int i, j, suma = 0;

    for (i = 1; i < orden; i++) {
        for (j = 0; j < i; j++) {
            suma += mat[i][j];
        }
    }

    return suma;
}

int sumaTSuperiorDSecundaria(int orden, int** mat) {
    int i, j, suma = 0;
    int limi = orden - 1;
    int limj = limi;

    for (i = 0; i < limi; i++, limj--) {
        for (j = 0; j < limj; j++) {
            suma += mat[i][j];
        }
    }

    return suma;
}
