#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char suc[16];
    int cod;
    int cant;
} TVenta;

typedef struct {
    int cod;
    char desc[21];
    float precio;
    int stock;
    int pPed;
    int cPed;
} TProd;

typedef struct {
    int cod;
    int cant;
} TPed;

void mostrarArchivo();
void mostrarArchivo2();
void mostrarArchivo3();

int main() {
    mostrarArchivo();
    mostrarArchivo2();
    mostrarArchivo3();
    return 0;
}

void mostrarArchivo() {
    FILE *fp;
    TVenta reg;

    fp = fopen("Archivos/VENTAS2.dat", "rb");

    if (fp == NULL) {
        printf("Error al leer VENTAS2.dat");
        exit(1);
    }

    fread(&reg, sizeof(TVenta), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%s\t%d\t%d\n", reg.suc, reg.cod, reg.cant);
        fread(&reg, sizeof(TVenta), 1, fp);
    }
    
    fclose(fp);
}

void mostrarArchivo2() {
    FILE *fp;
    TProd reg;

    fp = fopen("Archivos/PRODUCTOS2.dat", "rb");

    if (fp == NULL) {
        printf("Error al leer PRODUCTOS2.dat");
        exit(1);
    }

    fread(&reg, sizeof(TProd), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%d\t%s\t%.2f\t%d\t%d\t%d\n", reg.cod, reg.desc, reg.precio, reg.stock, reg.pPed, reg.cPed);
        fread(&reg, sizeof(TProd), 1, fp);
    }
    
    fclose(fp);
}

void mostrarArchivo3() {
    FILE *fp;
    TPed reg;

    fp = fopen("Archivos/PEDIDOS.dat", "rb");

    if (fp == NULL) {
        printf("Error al leer PEDIDOS.dat");
        exit(1);
    }

    fread(&reg, sizeof(TPed), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%d\t%d\n", reg.cod, reg.cant);
        fread(&reg, sizeof(TPed), 1, fp);
    }
    
    fclose(fp);
}