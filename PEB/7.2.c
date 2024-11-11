#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TProd buscarProd(FILE *, int);
void procVentas(FILE *, FILE *);
void genPedidos(FILE *, FILE *);

int main () {
    FILE *pvent, *pprod, *pped;
    
    pvent = fopen("Archivos/VENTAS2.dat", "rb");
    pprod = fopen("Archivos/PRODUCTOS2.dat", "r+b");
    pped = fopen("Archivos/PEDIDOS.dat", "wb");

    if (pvent == NULL || pprod == NULL || pped == NULL) {
        printf("Hubo un error en el manejo de archivos.");
        exit(1);
    }

    procVentas(pvent, pprod);
    genPedidos(pprod, pped);

    fclose(pvent);
    fclose(pprod);
    fclose(pped);

    return 0;
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

void procVentas(FILE *pvent, FILE *pprod) {
    TVenta venta;
    TProd prod;
    float totXSuc, totEmp = 0;
    int cantVend, maxCantVend = 0;
    char antSuc[16], maxSuc[16];

    fread(&venta, sizeof(TVenta), 1, pvent);

    while (!feof(pvent)) {

        strcpy(antSuc, venta.suc);
        cantVend = 0;
        totXSuc = 0;

        do {
            prod = buscarProd(pprod, venta.cod);

            if (prod.cod != -1) {
                totXSuc += prod.precio * venta.cant;
                cantVend += venta.cant;

                if (venta.cant <= prod.stock) {
                    fseek(pprod, -sizeof(TProd), SEEK_CUR);
                    prod.stock -= venta.cant;
                    fwrite(&prod, sizeof(TProd), 1, pprod);
                } else
                    printf("No se puso realizar la venta del producto %d, stock insuficiente.\n", prod.cod);
            } else
                printf("No se encontro el producto de codigo %d.\n", venta.cod);

            fread(&venta, sizeof(TVenta), 1, pvent);

        } while (!feof(pvent) && strcmpi(antSuc, venta.suc) == 0);

        printf("Importe total en sucursal %s: $%.2f\n", antSuc, totXSuc);
        
        if (cantVend > maxCantVend) {
            strcpy(maxSuc, antSuc);
            maxCantVend = cantVend;
        }

        totEmp += totXSuc;
    }

    printf("Recaudacion total de la empresa en el mes: $%.2f\n", totEmp);
    printf("Sucursal con mayor cantidad de productos vendidos: %s\n", maxSuc);
}

void genPedidos(FILE *pprod, FILE *pped) {
    TPed ped;
    TProd prod;

    rewind(pprod);
    fread(&prod, sizeof(TProd), 1, pprod);

    while (!feof(pprod)) {
        if (prod.stock < prod.pPed) {
            ped.cod = prod.cod;
            ped.cant = prod.cPed;
            fwrite(&ped, sizeof(TPed), 1, pped);
        }

        fread(&prod, sizeof(TProd), 1, pprod);
    }
}