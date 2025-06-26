#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

/*
#define PI 3.1415926
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define P_ENTERA(x) ((int) (x))
#define P_DECIMAL(x) ((x) - (int) (x))
#define ES_MAYUSCULA(c) ((c) >= 'A' && (c) <= 'Z')
#define ES_MINUSCULA(c) ((c) >= 'a' && (c) <= 'z')
#define ES_LETRA(c) (ES_MAYUSCULA(c) || ES_MINUSCULA(c))
#define ES_NUMERO(c) ((c) >= '0' && (c) <= '9')
#define A_MAYUSCULA(c) (ES_LETRA(c) ? (ES_MAYUSCULA(c) ? (c) : (c) - ('a' - 'A')) : (c))
#define A_MINUSCULA(c) (ES_LETRA(c) ? (ES_MINUSCULA(c) ? (c) : (c) + ('a' - 'A')) : (c))
#define FACTORIAL(x) ({\
    int fact = 1;\
    int i;\
    for (i = x; i > 1; i--)\
        fact *= i;\
    (fact);\
})
*/

#define FILAS 4
#define COLUMNAS 4
#define ORDEN 4

void** crearMatriz (size_t tamElem, int filas, int columnas);
void destruirMatriz (void** mtx, int filas);

void inicializarMatriz(int filas, int columnas, int** mtx);
void mostrarMatriz (int filas, int columnas, int** mtx);
void mostrarDPrincipal (int orden, int** mtx);
void mostrarDSecundaria (int orden, int** mtx);
int sumaDPrincipal (int orden, int** mtx);
int sumaTriangularSuperiorDPrincipal (int orden, int** mtx);
int sumaTriangularInferiorDPrincipal (int orden, int** mtx);
int sumaTriangularSuperiorDSecundaria (int orden, int** mtx);
int sumaTriangularInferiorDSecundaria (int orden, int** mtx);
bool esMatrizDiagonal (int orden, int** mtx);
void trasponerCuadInSitu (int orden, int** mtx);
void trasponerMatriz (int fOrig, int cOrig, int trasp[cOrig][fOrig], int orig[][cOrig]);

int main () {

    int a = 2048;
    char* p = (char*) &a;

    p += 1;

    printf("Direccion de a: %p\n", &a);
    printf("Direccion del 2do byte de a: %p\n", p);
    printf("Valor de p: %d\n", *p);


    // int mtx[][COLUMNAS] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {9, 10, 11, 12},
    //     {13, 14, 15, 16},
    // };

    // int (*mtx)[ORDEN] = malloc(sizeof(int) * ORDEN * ORDEN);

    // int** mtx = (int**) crearMatriz(sizeof(int), ORDEN, ORDEN);

    // if (mtx == NULL)
    //     return -1;

    // inicializarMatriz(FILAS, COLUMNAS, mtx);

    // printf("Matriz:\n");
    // mostrarMatriz(FILAS, COLUMNAS, mtx);
    // printf("\nDiagonal principal:\n");
    // mostrarDPrincipal(ORDEN, mtx);
    // printf("\nDiagonal secundaria:\n");
    // mostrarDSecundaria(ORDEN, mtx);

    // printf("\nSuma d. principal: %d", sumaDPrincipal(ORDEN, mtx));
    // printf("\n");

    // printf("\nSuma triangular superior d. principal: %d", sumaTriangularSuperiorDPrincipal(ORDEN, mtx));
    // printf("\nSuma triangular inferior d. principal: %d", sumaTriangularInferiorDPrincipal(ORDEN, mtx));
    // printf("\nSuma triangular superior d. secundaria: %d", sumaTriangularSuperiorDSecundaria(ORDEN, mtx));
    // printf("\nSuma triangular inferior d. secundaria: %d", sumaTriangularInferiorDSecundaria(ORDEN, mtx));
    // printf("\n");

    // printf("\nEs matriz diagonal? %s\n", esMatrizDiagonal(ORDEN, mtx) ? "Si" : "No");
    // printf("\n");

    // trasponerCuadInSitu(ORDEN, mtx);

    // printf("Matriz:\n");
    // mostrarMatriz(FILAS, COLUMNAS, mtx);

    return 0;
}

void** crearMatriz (size_t tamElem, int filas, int columnas) {

    void** mtx = malloc (filas * sizeof(void*));

    if (mtx == NULL)
        return NULL;

    void** i = mtx;
    void** ult = mtx + filas -1;

    bool mallocOk = true;

    while (mallocOk && i <= ult) {

        *i = malloc(tamElem * columnas);

        if (*i == NULL) {
            destruirMatriz(mtx, i - mtx);
            mallocOk = false;
            mtx = NULL;
        }

        i++;
    }

    return mtx;
}

void destruirMatriz (void** mtx, int filas) {

    void** ult = mtx + filas -1;

    for (void** i = mtx; i <= ult; i++)
        free(*i);

    free(mtx);
}

void inicializarMatriz (int filas, int columnas, int** mtx) {
    int i, j, cont = 1;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            mtx[i][j] = cont++;
        }
    }
}

void mostrarMatriz (int filas, int columnas, int** mtx) {

    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++)
            printf("%3d", mtx[i][j]);

        putchar('\n');
    }
}

void mostrarDPrincipal (int orden, int** mtx) {

    int i;

    for (i = 0; i < orden; i++) {
        printf("%3d", mtx[i][i]);
    }

    putchar('\n');
}

void mostrarDSecundaria (int orden, int** mtx) {

    int i;

    for (i = orden -1; i >= 0; i--) {
        printf("%3d", mtx[orden -1 - i][i]);
    }

    putchar('\n');
}

int sumaDPrincipal (int orden, int** mtx) {

    int i, suma = 0;

    for (i = 0; i < orden; i++)
        suma += mtx[i][i];

    return suma;
}

int sumaTriangularSuperiorDPrincipal (int orden, int** mtx) {

    int i, j, suma = 0;

    for (i = 0; i < orden; i++) {
        for (j = i; j < orden; j++)
            suma += mtx[i][j];
    }

    return suma;
}

int sumaTriangularInferiorDPrincipal (int orden, int** mtx) {

    int i, j, suma = 0;

    for (i = 0; i < orden; i++) {
        for (j = 0; j <= i; j++)
            suma += mtx[i][j];
    }

    return suma;
}

int sumaTriangularSuperiorDSecundaria (int orden, int** mtx) {

    int i, j, suma = 0;

    for (i = 0; i < orden; i++) {
        for (j = 0; j < orden - i; j++)
            suma += mtx[i][j];
    }

    return suma;
}

int sumaTriangularInferiorDSecundaria (int orden, int** mtx) {

    int i, j, suma = 0;

    for (i = 0; i < orden; i++) {
        for (j = orden -1; j >= orden -1 - i; j--)
            suma += mtx[i][j];
    }

    return suma;
}

bool esMatrizDiagonal (int orden, int** mtx) {

    int i = 0, j = 0;
    bool mtxDiagonal = true;

    while (mtxDiagonal && i < orden) {

        while (mtxDiagonal && j < orden) {

            if ((i != j && mtx[i][j] != 0) || (i == j && mtx[i][j] == 0))
                mtxDiagonal = false;

            j++;
        }

        i++;
    }

    return mtxDiagonal;
}

void trasponerCuadInSitu (int orden, int** mtx) {

    int i, j, aux;

    for (i = 0; i < orden -1; i++) {
        for (j = i +1; j < orden; j++) {
            aux = mtx[i][j];
            mtx[i][j] = mtx[j][i];
            mtx[j][i] = aux;
        }
    }
}

void trasponerMatriz (int fOrig, int cOrig, int trasp[cOrig][fOrig], int orig[][cOrig]) {

    int i, j;

    for (i = 0; i < fOrig; i++) {
        for (j = 0; j < cOrig; j++)
            trasp[j][i] = orig[i][j];
    }
}
