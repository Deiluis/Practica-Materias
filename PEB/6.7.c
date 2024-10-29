#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    char desc[51];
    int stock;
} TProd;

typedef struct {
    int cod, cant;
} TFaltante;

int ingIntMayA(int);
TProd buscarProd(FILE *, int);
TFaltante buscarFaltante(FILE *, int);
void ingVentas();

int main () {
    ingVentas();
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

TProd buscarProd(FILE *pf, int cod) {
    TProd prod;
    int encontrado = 0;

    rewind(pf);
    fread(&prod, sizeof(TProd), 1, pf);

    while (!feof(pf) && !encontrado) {
        if (prod.cod == cod)
            encontrado = 1;
        else
            fread(&prod, sizeof(TProd), 1, pf);
    }

    if (!encontrado)
        prod.cod = -1;

    return prod;
}

TFaltante buscarFaltante(FILE *pf, int cod) {
    TFaltante falt;
    int encontrado = 0;

    rewind(pf);
    fread(&falt, sizeof(TFaltante), 1, pf);

    while (!feof(pf) && !encontrado) {
        if (falt.cod == cod)
            encontrado = 1;
        else
            fread(&falt, sizeof(TFaltante), 1, pf);
    }

    if (!encontrado)
        falt.cod = -1;

    return falt;
}

void ingVentas() {
    FILE *pProd, *pFalt;
    TProd prod;
    TFaltante falt;
    int cod, cant;

    pProd = fopen("Archivos/STOCK.DAT", "r+b");
    pFalt = fopen("Archivos/FALTANTES.DAT", "r+b");

    if (pProd == NULL || pFalt == NULL) {
        printf("Error en el manejo de archivos");
        exit(1);
    }

    printf("Carga de ventas.\n\n");

    printf("Ingrese el codigo del producto vendido (mayor a 0, 0 para terminar): ");
    cod = ingIntMayA(-1);

    while (cod != 0) {
        prod = buscarProd(pProd, cod);

        if (prod.cod != -1) {
            printf("Ingresa la cantidad vendida: ");
            cant = ingIntMayA(0);

            fseek(pProd, -sizeof(TProd), SEEK_CUR);

            if (prod.stock >= cant) {
                prod.stock -= cant;
            } else {
                falt = buscarFaltante(pFalt, cod);

                if (falt.cod != -1)
                    fseek(pFalt, -sizeof(TFaltante), SEEK_CUR);
                else {
                    falt.cod = cod;
                    falt.cant = 0;
                }

                falt.cant += cant - prod.stock;
                fwrite(&falt, sizeof(TFaltante), 1, pFalt);

                prod.stock = 0;     
            }

            fwrite(&prod, sizeof(TProd), 1, pProd);

        } else {
            printf("No se encontro el producto con el codigo especificado");
        }

        printf("Ingrese el codigo del producto vendido (mayor a 0, 0 para terminar): ");
        cod = ingIntMayA(-1);
    }

    fclose(pProd);
    fclose(pFalt);
}