#include <stdio.h>
#include <stdlib.h>

#define FILAS 4
#define COLUMNAS 3

void mostrarMatriz (int filas, int columnas, int mtx[][columnas]);
void trasponerMatriz (int fOrig, int cOrig, int trasp[cOrig][fOrig], int orig[][cOrig]);

int main () {

    int mtx[][COLUMNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
    };

    int trasp[COLUMNAS][FILAS];

    printf("Matriz:\n");
    mostrarMatriz(FILAS, COLUMNAS, mtx);

    trasponerMatriz(FILAS, COLUMNAS, trasp, mtx);

    printf("Matriz traspuesta:\n");
    mostrarMatriz(COLUMNAS, FILAS, trasp);

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

void trasponerMatriz (int fOrig, int cOrig, int trasp[cOrig][fOrig], int orig[][cOrig]) {

    int i, j;

    for (i = 0; i < fOrig; i++) {
        for (j = 0; j < cOrig; j++) 
            trasp[j][i] = orig[i][j];
    }
}