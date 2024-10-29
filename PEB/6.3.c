#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int mes, anio, dia, codp;
    float imp;
} TVenta;

int ingIntEntre(int, int);
void cargarDatos(int, int, int, int[][12], float[][12]);
void mostrarCant(int, int, int, int[][12]);
void mostrarImp(int, int, int, float[][12]);

int main () {
    char op = 'C';
    int anio1, anio2, cantAnios, mCant[10][12] = {{0}};
    float mImp[10][12] = {{0}};

    printf("Visor de ventas\n\n");

    printf("Ingresa el anio 1 del rango (2014 a 2023): ");
    anio1 = ingIntEntre(2014, 2023);
    printf("Ingresa el anio 2 del rango (%d a 2023): ", anio1);
    anio2 = ingIntEntre(anio1, 2023);
    cantAnios = anio2 - anio1 +1;

    cargarDatos(anio1, anio2, 12, mCant, mImp);

    while (op != 'F') {
        if (op == 'C')
            mostrarCant(cantAnios, 12, anio1, mCant);
        else
            mostrarImp(cantAnios, 12, anio1, mImp);

        printf("Ingresa la opcion de visualizacion preferida\n");
        printf("C: Cant. ventas por mes, I: Importe por mes, F: Terminar programa: ");
        do {
            fflush(stdin);
            scanf("%c", &op);
            
            op = toupper(op);

            if (op != 'C' && op != 'I' && op != 'F')
                printf("Dato invalido, reingresar: ");

        } while (op != 'C' && op != 'I' && op != 'F');
    }

    return 0;
}

int ingIntEntre(int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato < limi || dato > lims)
            printf("Dato invalido, reingresar: ");

    } while (dato < limi || dato > lims);

    return dato;
}

void cargarDatos(int anio1, int anio2, int meses, int mCant[][12], float mImp[][12]) {
    TVenta venta;
    FILE *fp;

    fp = fopen("Archivos/VENTAS.DAT", "rb");

    if (fp == NULL) {
        printf("Error al abrir VENTAS.DAT");
        exit(1);
    }

    fread(&venta, sizeof(TVenta), 1, fp);

    while (!feof(fp)) {
        if (venta.anio >= anio1 && venta.anio <= anio2) {
            mCant[venta.anio - anio1][venta.mes -1]++;
            mImp[venta.anio - anio1][venta.mes -1] += venta.imp;
        }

        fread(&venta, sizeof(TVenta), 1, fp);
    }

    fclose(fp);
}

void mostrarCant(int cantAnios, int meses, int anio1, int mCant[][12]) {
    int i, j;

    printf("Cantidad de ventas por mes:\n");
    printf("\t");

    for (i = 0; i < meses; i++)
        printf("Mes %d\t", i+1);

    printf("\n");

    for (i = 0; i < cantAnios; i++) {
        printf("%d\t", anio1 + i);

        for (j = 0; j < meses; j++) {
            printf("%d\t", mCant[i][j]);
        }

        printf("\n");
    }
}

void mostrarImp(int cantAnios, int meses, int anio1, float mImp[][12]) {
    int i, j;

    printf("Importe total de ventas por mes:\n");
    printf("\t");

    for (i = 0; i < meses; i++)
        printf("Mes %d\t", i+1);

    printf("\n");

    for (i = 0; i < cantAnios; i++) {
        printf("%d\t", anio1 + i);

        for (j = 0; j < meses; j++) {
            printf("$%.2f\t", mImp[i][j]);
        }

        printf("\n");
    }
}