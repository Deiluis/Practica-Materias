#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILAS 2
#define COLUMNAS 3

void mostrarMatriz (int filas, int columnas, int mtx[][columnas]);
void matrizProducto (
    int fmtx1, 
    int cmtx1, 
    int prod[fmtx1][fmtx1], 
    int mtx1[fmtx1][cmtx1], 
    int mtx2[cmtx1][fmtx1]
);

int main () {

    int mtx1[][COLUMNAS] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    int mtx2[][FILAS] = {
        {1, 4},
        {2, 5},
        {3, 6},
    };

    int prod[FILAS][FILAS];

    printf("Matriz 1:\n");
    mostrarMatriz(FILAS, COLUMNAS, mtx1);
    printf("\n");

    printf("Matriz 2:\n");
    mostrarMatriz(COLUMNAS, FILAS, mtx2);
    printf("\n");

    matrizProducto(FILAS, COLUMNAS, prod, mtx1, mtx2);

    printf("Matriz producto:\n");
    mostrarMatriz(FILAS, FILAS, prod);
    printf("\n");

    return 0;
}

void mostrarMatriz (int filas, int columnas, int mtx[][columnas]) {

    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++)
            printf("%3d", mtx[i][j]);

        putchar('\n');
    }
}

void matrizProducto (
    int fmtx1, 
    int cmtx1, 
    int prod[fmtx1][fmtx1], 
    int mtx1[fmtx1][cmtx1], 
    int mtx2[cmtx1][fmtx1]
) {

    int i, j, k, val;

    for (i = 0; i < fmtx1; i++) {

        for (j = 0; j < fmtx1; j++) {

            val = 0;

            for (k = 0; k < cmtx1; k++)
                val += mtx1[i][k] * mtx2[k][j];

            prod[i][j] = val;
        }
    }
}
