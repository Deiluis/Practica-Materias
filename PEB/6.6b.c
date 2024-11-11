#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    float precio;
    char desc[51];
} TProd;

typedef struct {
    int cod;
} TCodEliminado;

int ingIntMayA(int);
void mostrarArchivo(FILE *);
TProd buscarProd(FILE *, int);
TCodEliminado buscarCodEliminado(FILE*, int);
int regCodEliminados(FILE*, FILE*);
void eliminarProd(FILE*, FILE*, FILE*);

int main () {
    FILE *porg, *pnuevo, *pCodEliminado;
    int huboEliminados;

    porg = fopen("Archivos/PRODUCTOS.dat", "rb");
    pnuevo = fopen("Archivos/PRODUCTOS.tmp", "w+b");
    pCodEliminado = fopen("Archivos/CODELIMINADOS.tmp", "w+b");

    if (porg == NULL || pnuevo == NULL || pCodEliminado == NULL) {
        printf("Hubo un error en el manejo de archivos");
        exit(1);
    }

    printf("Eliminacion de productos por codigo.\n\n");

    mostrarArchivo(porg);
    huboEliminados = regCodEliminados(porg, pCodEliminado);

    if (huboEliminados) {
        eliminarProd(porg, pnuevo, pCodEliminado);
        mostrarArchivo(pnuevo);
    }

    fclose(porg);
    fclose(pnuevo);
    fclose(pCodEliminado);

    if (huboEliminados) {
        remove("Archivos/PRODUCTOS.dat");
        remove("Archivos/CODELIMINADOS.tmp");
        rename("Archivos/PRODUCTOS.tmp", "Archivos/PRODUCTOS.dat");
        printf("Se eliminaron los productos con exito.");
    } else {
        remove("Archivos/PRODUCTOS.tmp");
        remove("Archivos/CODELIMINADOS.tmp");
        printf("No se eliminaron productos");
    }

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

void mostrarArchivo(FILE *pf) {
    TProd prod;

    printf("Contenido actual del archivo:\n");

    rewind(pf);
    fread(&prod, sizeof(TProd), 1, pf);

    printf("Codigo\tPrecio\tDescripcion\n");

    while (!feof(pf)) {
        printf("%d\t$%.2f\t%s\n", prod.cod, prod.precio, prod.desc);
        fread(&prod, sizeof(TProd), 1, pf);
    }

    printf("\n\n");
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

TCodEliminado buscarCodEliminado(FILE *pf, int cod) {
    TCodEliminado prodEliminado;
    int encontrado = 0;

    rewind(pf);
    fread(&prodEliminado, sizeof(TCodEliminado), 1, pf);

    while (!feof(pf) && !encontrado) {
        if (prodEliminado.cod == cod)
            encontrado = 1;
        else
            fread(&prodEliminado, sizeof(TCodEliminado), 1, pf);
    }

    if (!encontrado)
        prodEliminado.cod = -1;

    return prodEliminado;
}

int regCodEliminados(FILE *porg, FILE *pCodEliminado) {
    TProd prod;
    TCodEliminado prodEliminado;
    int huboEliminados = 0, cod;

    printf("Ingresa el codigo de un producto a eliminar, 0 para terminar: ");
    cod = ingIntMayA(-1);

    while (cod != 0) {
        prod = buscarProd(porg, cod);

        if (prod.cod != -1) {
            huboEliminados = 1;
            prodEliminado = buscarCodEliminado(pCodEliminado, prod.cod);

            if (prodEliminado.cod == -1) {
                prodEliminado.cod = cod;
                fwrite(&prodEliminado, sizeof(TCodEliminado), 1, pCodEliminado);
            }
                
        } else
            printf("No se encontro el producto a eliminar.\n");

        printf("Ingresa el codigo de un producto a eliminar, 0 para terminar: ");
        cod = ingIntMayA(-1);
    }

    return huboEliminados;
}

void eliminarProd(FILE *porg, FILE *pnuevo, FILE *pCodEliminado) {
    TProd prod;
    TCodEliminado prodEliminado;

    rewind(porg);
    fread(&prod, sizeof(TProd), 1, porg);

    while (!feof(porg)) {
        prodEliminado = buscarCodEliminado(pCodEliminado, prod.cod);

        if (prodEliminado.cod == -1)
            fwrite(&prod, sizeof(TProd), 1, pnuevo);

        fread(&prod, sizeof(TProd), 1, porg);
    }
}