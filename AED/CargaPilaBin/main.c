#include <stdio.h>
#include <stdlib.h>
#include "../Pila/Pila.h"

#define TAM_COD 4
#define TAM_DESC 15

#define ARG_BIN 1

typedef struct {
    char codigo[TAM_COD +1];
    char descripcion[TAM_DESC +1];
    float precio;
    int stock;
} Producto;

bool generarProductosBin(const char* nomArch);
bool cargarPilaDeArchivoBin (tPila* pila, const char* nomArch, size_t tamReg);

// CargaPilaBin.exe Productos.dat
int main (int argc, char* argv[]) {
    tPila pila;
    Producto dato;
    int i;

    if (!crearPila(&pila)) {
        printf("Error al crear la pila\n");
        return 1;
    }

    // for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    //     if (!apilar(&pila, nums + i, sizeof(int)))
    //         printf("Pila llena\n");
    // }

    // for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    //     if (!desapilar(&pila, &dato, sizeof(int)))
    //         printf("Pila vacia\n");
    // }


    // if (!generarProductosBin("Productos.dat")) {
    //     printf("Error al generar el archivo");
    //     return 1;
    // }

    if (!cargarPilaDeArchivoBin(&pila, argv[ARG_BIN], sizeof(Producto))) {
        printf("Error al cargar la pila");
        return 1;
    }

    for (i = 0; i < 15; i++) {
        if (desapilar(&pila, &dato, sizeof(Producto)))
            printf("%s | %s | $%.2f | %d\n", dato.codigo, dato.descripcion, dato.precio, dato.stock);
        else
            printf("Pila vacia\n");
    }

    // if (verTope(&pila, &dato, sizeof(Producto)))
    //     printf("Tope: %s | %s | $%.2f | %d\n", dato.codigo, dato.descripcion, dato.precio, dato.stock);

    // if (pilaVacia(&pila))
    //     printf("Pila vacia\n");

    destruirPila(&pila);

    return 0;
}

bool generarProductosBin (const char* nomArch) {

    Producto prods[] = {
        { "BANA",   "Banana",    2200.5,  7 },
        { "PERA",   "Pera",      1800.0,  5 },
        { "MANZ",   "Manzana",   2000.0,  6 },
        { "KIWI",   "Kiwi",      2500.5,  3 },
        { "UVA",    "Uvas",      3000.0,  10 },
        { "MELN",   "Melon",     2700.3,  2 },
        { "DURZ",   "Durazno",   2100.9,  4 },
        { "CIRU",   "Ciruela",   2300.0,  8 },
        { "NARA",   "Naranja",   1900.2,  6 },
        { "LIMN",   "Limon",     1600.7,  9 }
    };

    FILE* arch = fopen(nomArch, "wb");

    if (!arch)
        return false;

    fwrite(prods, sizeof(Producto), sizeof(prods) / sizeof(Producto), arch);
    fclose(arch);

    return true;
}

bool cargarPilaDeArchivoBin (tPila* pila, const char* nomArch, size_t tamReg) {

    FILE* archBin = fopen(nomArch, "rb");
    void* reg;

    if (!archBin)
        return false;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(archBin);
        return false;
    }

    while (fread(reg, tamReg, 1, archBin))
        apilar(pila, reg, tamReg);

    fclose(archBin);
    free(reg);

    return true;
}