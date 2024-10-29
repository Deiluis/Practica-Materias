#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    float precio;
    char desc[51];
} TProd;

int ingIntMayA(int);
void mostrarArchivo();
void eliminarProd();

int main () {
    printf("Eliminacion de productos por codigo.\n\n");

    mostrarArchivo();
    eliminarProd();

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

void mostrarArchivo() {
    FILE *pf;
    TProd prod;

    pf = fopen("Archivos/PRODUCTOS.dat", "rb");

    if (pf == NULL) {
        printf("Error al abrir PRODUCTOS.dat");
        exit(1);
    }

    printf("Contenido actual del archivo:\n");

    fread(&prod, sizeof(TProd), 1, pf);

    printf("Codigo\tPrecio\tDescripcion\n");

    while (!feof(pf)) {
        printf("%d\t$%.2f\t%s\n", prod.cod, prod.precio, prod.desc);
        fread(&prod, sizeof(TProd), 1, pf);
    }

    fclose(pf);
    printf("\n\n");
}

void eliminarProd() {
    FILE *porg, *pnuevo;
    TProd prod;
    int encontrado = 0, cod;

    porg = fopen("Archivos/PRODUCTOS.dat", "rb");
    pnuevo = fopen("Archivos/PRODUCTOS.tmp", "wb");

    if (porg == NULL || pnuevo == NULL) {
        printf("Hubo un error en el manejo de archivos");
        exit(1);
    }

    printf("Ingresa el codigo del producto a eliminar (mayor a 0): ");
    cod = ingIntMayA(0);

    fread(&prod, sizeof(TProd), 1, porg);

    while (!feof(porg)) {
        if (prod.cod == cod)
            encontrado = 1;
        else
            fwrite(&prod, sizeof(TProd), 1, pnuevo);
        
        fread(&prod, sizeof(TProd), 1, porg);
    }

    fclose(porg);
    fclose(pnuevo);

    if (encontrado) {
        remove("PRODUCTOS.dat");
        rename("PRODUCTOS.tmp", "PRODUCTOS.dat");
        printf("Se elimino el producto con exito.");
    } else {
        remove("PRODUCTOS.tmp");
        printf("No se encontro el producto a eliminar");
    }
}