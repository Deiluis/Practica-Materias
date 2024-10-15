#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cargarMtx (int[][8], int, int);
int buscarMax (int[][8], int, int);
void mostrarContarVal (int[][8], int, int, int);
void mostrarMtx (int[][8], int, int);

int main () {
    int max, mtx[5][8];

    cargarMtx(mtx, 5, 8);
    max = buscarMax(mtx, 5, 8);
    mostrarMtx(mtx, 5, 8);
    printf("\n\n");
    printf("Maximo valor encontrado: %d\n", max);
    mostrarContarVal(mtx, 5, 8, max);

    return 0;
}

void cargarMtx (int mtx[][8], int filas, int cols) {
    int i, j;

    srand(time(NULL));

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++)
            mtx[i][j] = (rand() % 90) + 10;
    }
}

int buscarMax (int mtx[][8], int filas, int cols) {
    int i, j, max = mtx[0][0];

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++) {
            if (mtx[i][j] > max)
                max = mtx[i][j];
        }
    }

    return max;
}

void mostrarContarVal (int mtx[][8], int filas, int cols, int val) {
    int i, j, cant = 0;

    printf("El valor %d se encuenta en:\n", val);

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++) {
            if (mtx[i][j] == val) {
                cant++;
                printf("Fila %d, columna %d\n", i+1, j+1);
            }
        }
    }

    printf("Se encontro este valor %d veces en toda la matriz", cant);
}

void mostrarMtx (int mtx[][8], int filas, int cols) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++)
            printf("%d ", mtx[i][j]);

        printf("\n");
    }
}
