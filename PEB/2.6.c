#include <stdio.h>

#define FILAS 12
#define COLS 9

int ingIntEntre (int, int);
int ingIntVal (int, int, int);
void llenarMtx (char[][COLS], int, int, char);
void mostrarMtx (char[][COLS], int[], int, int);
int buscar (int[], int, int);
int cargarRes (char[][COLS], int[], int, int);
void sumaFilas (char[][COLS], int[], int, int);
void sumaCols (char[][COLS], int[], int, int);
void ordenar (int[], int[], int);
int buscarMax (int[], int);
void mostrarPos (int[], int, int);
void listarButs (int[], int[], int);

int main () {
    int ocp = 0, tot = FILAS * COLS, max;
    char mBut[FILAS][COLS];
    int vNBut[] = { 8, 6, 4, 2, 1, 3, 5, 7, 9 };
    int vSumFilas[FILAS] = {0}, vSumCols[COLS] = {0};

    llenarMtx(mBut, FILAS, COLS, 'D');
    ocp = cargarRes(mBut, vNBut, FILAS, COLS);

    sumaFilas(mBut, vSumFilas, FILAS, COLS);
    sumaCols(mBut, vSumCols, FILAS, COLS);

    printf("Cantidad de asientos disponibles: %d\n", tot - ocp);
    printf("Cantidad de asientos ocupados: %d\n\n", ocp);

    printf("Numeros de filas que quedaron vacias:\n");
    mostrarPos(vSumFilas, FILAS, 0);
    printf("\n");

    max = buscarMax(vSumFilas, FILAS);
    printf("Numeros de filas con mayor cantidad de espectadores:\n");
    mostrarPos(vSumFilas, FILAS, max);

    ordenar(vSumCols, vNBut, COLS);

    printf("\n\n");
    listarButs(vSumCols, vNBut, COLS);

    return 0;
}

int ingIntEntre (int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato < limi || dato > lims)
            printf("Dato invalido, reingresar: ");

    } while (dato < limi || dato > lims);

    return dato;
}

int ingIntVal (int limi, int lims, int menA) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato >= menA)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato >= menA);

    return dato;
}

void llenarMtx (char mtx[][COLS], int filas, int cols, char val) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++)
            mtx[i][j] = val;
    }
}

void mostrarMtx (char mtx[][COLS], int vNBut[], int filas, int cols) {
    int i, j;

    printf("\t");

    for (i = 0; i < cols; i++)
        printf("%d ", vNBut[i]);

    printf("\n");

    for (i = 0; i < filas; i++) {

        printf("%d\t", i+1);

        for (j = 0; j < cols; j++)
            printf("%c ", mtx[i][j]);
        
        printf("\n");
    }
}

int buscar (int vec[], int tam, int val) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vec[i] == val)
            pos = i;
        else
            i++;
    }

    return pos;
}

int cargarRes (char mtx[][COLS], int vNBut[], int filas, int cols) {
    int fil, but, pos, ocp = 0;

    printf("Se ingresaran las reservas.\n\n");
    printf("Esquema actual de butacas (D es disponible, R es reservada):\n");
    mostrarMtx(mtx, vNBut, filas, cols);
    printf("\n");

    printf("Ingresa el numero de fila que queres reservar (1 a 12, negativo para terminar): ");
    fil = ingIntVal(1, 12, 0);

    while (fil > 0 && ocp < filas * cols) {
        printf("Ingresa el numero de butaca a resevar (1 a 9): ");
        but = ingIntEntre(1, 9);

        pos = buscar(vNBut, cols, but);

        if (mtx[fil -1][pos] != 'R') {
            mtx[fil -1][pos] = 'R';
            ocp++;
        } else
            printf("La butaca seleccionada ya esta ocupada, por favor selecciona otra.\n\n");

        printf("Esquema actual de butacas (D es disponible, R es reservada):\n");
        mostrarMtx(mtx, vNBut, filas, cols);
        printf("\n");

        printf("Ingresa el numero de fila que queres reservar (1 a 12, negativo para terminar): ");
        fil = ingIntVal(1, 12, 0);
    }

    return ocp;
}

void sumaFilas (char mtx[][COLS], int vSumFilas[], int filas, int cols) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < cols; j++) {
            if (mtx[i][j] == 'R')
                vSumFilas[i]++;
        }
            
    }
}

void sumaCols (char mtx[][COLS], int vSumCols[], int filas, int cols) {
    int i, j;

    for (i = 0; i < cols; i++) {
        for (j = 0; j < filas; j++) {
            if (mtx[j][i] == 'R')
                vSumCols[i]++;
        }
    }
}

void ordenar (int vSumCols[], int vNBut[], int tam) {
    int i, j, aux;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam -1 -i; j++) {
            if (vSumCols[j] < vSumCols[j+1]) {

                aux = vSumCols[j+1];
                vSumCols[j+1] = vSumCols[j];
                vSumCols[j] = aux;

                aux = vNBut[j+1];
                vNBut[j+1] = vNBut[j];
                vNBut[j] = aux;
            }
        }
    }
}

int buscarMax (int vec[], int tam) {
    int i, max = vec[0];

    for (i = 1; i < tam; i++) {
        if (vec[i] > max)
            max = vec[i];
    }

    return max;
}

void mostrarPos (int vec[], int tam, int val) {
    int i;

    for (i = 0; i < tam; i++) {
        if (vec[i] == val)
            printf("%d, ", i+1);
    }
}

void listarButs (int vSumCols[], int vNBut[], int tam) {
    int i;

    printf("Butaca\tCantidad\n");

    for (i = 0; i < tam; i++) {
        printf("%d\t%d\n", vNBut[i], vSumCols[i]);
    }
}