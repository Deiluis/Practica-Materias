#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    float precio;
    char desc[51];
} TProd;

int ingIntMayA(int);
float ingFloatMayA(float);
TProd buscarProd(FILE *, int);
void modificarPrecios(FILE *);
void exportar(FILE *, FILE *);

int main () {
    FILE *pProd, *pExp;

    pProd = fopen("Archivos/productos.dat", "r+b");
    pExp = fopen("Archivos/productos.csv", "wt");

    if (pProd == NULL || pExp == NULL) {
        printf("Hubo un error en el manejo de archivos");
        exit(1);
    }

    printf("Actualizacion de precios.\n");
    printf("Al terminar de actualizar los precios, se exportaran todos en un archivo csv.\n\n");

    modificarPrecios(pProd);
    exportar(pProd, pExp);

    fclose(pProd);
    fclose(pExp);

    printf("Precios actualizados y exportados con exito.");

    return 0;
}

int ingIntMayA(int limi) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

float ingFloatMayA(float limi) {
    float dato;

    do {
        scanf("%f", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

TProd buscarProd(FILE *pProd, int cod) {
    TProd prod;
    int encontrado = 0;

    rewind(pProd);

    fread(&prod, sizeof(TProd), 1, pProd);

    while (!feof(pProd) && !encontrado) {
        if (prod.cod == cod)
            encontrado = 1;
        else
            fread(&prod, sizeof(TProd), 1, pProd);
    }

    if (!encontrado)
        prod.cod = -1;

    return prod;
}

void modificarPrecios(FILE *pProd) {
    TProd prod;
    int cod;

    printf("Ingrese el codigo del producto a actualizar el precio, mayor a 0, o 0 para terminar: ");
    cod = ingIntMayA(-1);

    while (cod != 0) {
        prod = buscarProd(pProd, cod);

        if (prod.cod != -1) {
            printf("Ingrese el nuevo precio: $");
            prod.precio = ingFloatMayA(0);

            fseek(pProd, -sizeof(TProd), SEEK_CUR);
            fwrite(&prod, sizeof(TProd), 1, pProd);
            fflush(pProd);
        } else {
            printf("No se encontro el producto con el codigo ingresado.\n");
        }

        printf("Ingrese el codigo del producto a actualizar el precio, mayor a 0, o 0 para terminar: ");
        cod = ingIntMayA(-1);
    }
}

void exportar(FILE *pProd, FILE *pExp) {
    TProd prod;

    rewind(pProd);
    fprintf(pExp, "Codigo;Precio;Descripcion\n");

    fread(&prod, sizeof(TProd), 1, pProd);

    while (!feof(pProd)) {
        fprintf(pExp, "%d;$%.2f;%s\n", prod.cod, prod.precio, prod.desc);
        fread(&prod, sizeof(TProd), 1, pProd);
    }
}