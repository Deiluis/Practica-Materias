#include <stdio.h>
#define PRODS 3
#define MESES 12

int ingIntEntre (int, int, int);
int ingIntMayA (int);
float ingFloatMayA (float);
int bisiesto (int);
int cantDiasMes (int, int);
int esFechaValida (int, int, int);
int buscar (int[], int, int);
int buscarFloat (float[], int, float);
void ingProds (float[], int[], int);
void ingVentas (int[][12], int[], int, int);
void sumaFila (int[][12], float[], float[], int, int);
void sumaCol (int[][12], float[], float[], int, int);
void mostrarMtx (int[][12], int[], int, int);
void obtenerTrim (float[], float[], int);
void mostrarMax(float[], int[], int);
void mostrarMin(float[], int);

int main () {
    float vPrecio[PRODS];
    int vCod[PRODS];
    int mVentas[PRODS][MESES] = {{0}};
    float vSumRecProds[PRODS] = {0}, vSumRecMeses[MESES] = {0};
    float vTrim[MESES / 3] = {0};

    ingProds(vPrecio, vCod, PRODS);
    ingVentas(mVentas, vCod, PRODS, MESES);
    sumaFila(mVentas, vSumRecProds, vPrecio, PRODS, MESES);
    sumaCol(mVentas, vSumRecMeses, vPrecio, PRODS, MESES);
    obtenerTrim(vSumRecMeses, vTrim, MESES);

    printf("Unidades vendidas de cada producto de los ultimos 12 meses:\n\n");
    mostrarMtx(mVentas, vCod, PRODS, MESES);
    printf("\n");

    printf("Producto del cual se obtuvo la mayor recaudacion: ");
    mostrarMax(vSumRecProds, vCod, PRODS);
    printf("\n");

    printf("Trimestre en el cual se obtuvo la menor recaudacion: ");
    mostrarMin(vTrim, MESES / 3);
    printf("\n");

    return 0;
}

int ingIntEntre (int limi, int lims, int cf) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato != cf)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato != cf);

    return dato;
}

int ingIntMayA (int limi) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

float ingFloatMayA (float limi) {
    float dato;

    do {
        scanf("%f", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

int bisiesto (int anio) {
    int bisiesto = 0;

    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
        bisiesto = 1;

    return bisiesto;
}

int cantDiasMes (int mes, int anio) {
    int dias;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        dias = 30;
    else {
        if (mes == 2)
            dias = 28 + bisiesto(anio);
        else
            dias = 31;
    }

    return dias;
}

int esFechaValida (int dia, int mes, int anio) {
    int fechaValida = 0;

    if (anio >= 1582) {
        if (mes >= 1 && mes <= 12) {
            if (dia >= 1 && dia <= cantDiasMes(mes, anio))
                fechaValida = 1;
        }
    }

    return fechaValida;
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

int buscarFloat (float vec[], int tam, float val) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vec[i] == val)
            pos = i;
        else
            i++;
    }

    return pos;
}

void ingProds (float vPrecio[], int vCod[], int tam) {
    int i, cod, pos;
    float precio;

    printf("Se ingresaran los codigos y precios de los %d productos.\n\n", tam);

    for (i = 0; i < tam; i++) {
        printf("Producto %d:\n", i+1);
        printf("Ingresa el precio del producto: $");
        precio = ingFloatMayA(0);

        printf("Ingresa el codigo del producto (entero, 3 cifras): ");

        do {
            cod = ingIntEntre(100, 999, 999);
            pos = buscar(vCod, i, cod);

            if (pos != -1)
                printf("Ya existe un producto con este codigo, reingresar: ");

        } while (pos != -1);

        vPrecio[i] = precio;
        vCod[i] = cod;
    }
}

void ingVentas (int mVentas[][12], int vCod[], int prods, int meses) {
    int cod, pos, dia, mes, ventas;

    printf("Se ingresaran las ventas efectuadas en el anio.\n\n");

    printf("Ingresa el codigo de producto (3 cifras, 0 para terminar): ");
    cod = ingIntEntre(100, 999, 0);

    while (cod > 0) {
        pos = buscar(vCod, prods, cod);

        if (pos != -1) {
            do {
                printf("Ingresa el dia de la venta: ");
                scanf("%d", &dia);
                printf("Ingresa el mes de la venta: ");
                scanf("%d", &mes);

                if (!esFechaValida(dia, mes, 2024))
                    printf("La fecha de venta ingresada no es valida, reingresar:\n");

            } while (!esFechaValida(dia, mes, 2024));

            printf("Ingresa la cantidad de unidades vendidas (mayor a 0): ");
            ventas = ingIntMayA(0);
            mVentas[pos][mes -1] += ventas;

        } else {
            printf("No se encontro el producto con el codigo ingresado.\n");
        }

        printf("Ingresa el codigo de producto de la siguiente venta (3 cifras, 0 para terminar): ");
        cod = ingIntEntre(100, 999, 0);
    }
}

void sumaFila (int mVentas[][12], float vSum[], float vPrecio[], int prods, int meses) {
    int i, j;

    for (i = 0; i < prods; i++) {
        for (j = 0; j < meses; j++)
            vSum[i] += mVentas[i][j] * vPrecio[i];
    }
}

void sumaCol (int mVentas[][12], float vSum[], float vPrecio[], int prods, int meses) {
    int i, j;

    for (i = 0; i < meses; i++) {
        for (j = 0; j < prods; j++)
            vSum[i] += mVentas[j][i] * vPrecio[j];
    }
}

void mostrarMtx (int mVentas[][12], int vCod[], int prods, int meses) {
    int i, j;

    printf("Codigo/Mes\t");

    for (i = 0; i < meses; i++)
        printf("%d\t", i+1);

    printf("\n");

    for (i = 0; i < prods; i++) {

        printf("%d\t\t", vCod[i]);

        for (j = 0; j < meses; j++) {
            printf("%d\t", mVentas[i][j]);
        }

        printf("\n");
    }
}

void obtenerTrim (float vSum[], float vTrim[], int tam) {
    int i;

    for (i = 0; i < tam; i += 3) {
        vTrim[i/3] += vSum[i] + vSum[i+1] + vSum[i+2];
    }
}

void mostrarMax(float vSum[], int vCod[], int tam) {
    int i, pos;
    float max = vSum[0];

    for (i = 1; i < tam; i++) {
        if (vSum[i] > max)
            max = vSum[i];
    }

    pos = buscarFloat(vSum, tam, max);
    printf("%d", vCod[pos]);
}

void mostrarMin(float vTrim[], int tam) {
    int i, pos;
    float min = vTrim[0];

    for (i = 1; i < tam; i++) {
        if (vTrim[i] < min)
            min = vTrim[i];
    }

    pos = buscarFloat(vTrim, tam, min);
    printf("%d", pos+1);
}