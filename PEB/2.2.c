#include <stdio.h>

void cargarMat (int[][4], int, int);
void sumaFilas (int[][4], int, int, int[]);
void sumaCols (int[][4], int, int, int[]);
void mostrarVec (int[], int);

int main () {
    int mat[5][4];
    int vFilas[5] = {0}, vCols[4] = {0};

    cargarMat(mat, 5, 4);
    sumaFilas(mat, 5, 4, vFilas);
    sumaCols(mat, 5, 4, vCols);
    
    printf("Suma de cada fila:\n");
    mostrarVec(vFilas, 5);
    printf("\nSuma de cada columna:\n");
    mostrarVec(vCols, 4);

    return 0;
}

void cargarMat (int mat[][4], int filas, int cols) {
    int i, j, aux;

    printf("Se cargara una matriz de 5 filas por 4 columnas.\n\n");

    for (i = 0; i < filas; i++) {

        printf("Fila %d:\n", i+1);

        for (j = 0; j < cols; j++) {
            printf("Columna %d: ", j+1);
            scanf("%d", &aux);
            mat[i][j] = aux;
        }

        printf("\n");
    }

}

void sumaFilas (int mat[][4], int filas, int cols, int vFilas[]) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++)
            vFilas[i] += mat[i][j];
    }
}

void sumaCols (int mat[][4], int filas, int cols, int vCols[]) {
    int i, j;

    for (i = 0; i < cols; i++) {
        for (j = 0; j < filas; j++)
            vCols[i] += mat[j][i];
    }
}

void mostrarVec (int vec[], int tam) {
    int i;

    for (i = 0; i < tam; i++)
        printf("%d, ", vec[i]);
}
