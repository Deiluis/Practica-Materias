#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Pila/Pila.h"

#define TAM_COD 4
#define TAM_DESC 15
#define TAM_PRECIO 7
#define TAM_STOCK 2

#define ARG_TXT 1
#define ARG_TIPO 2

#define TAM_LINEA 512

typedef struct {
    char codigo[TAM_COD +1];
    char descripcion[TAM_DESC +1];
    float precio;
    int stock;
} Producto;

typedef bool (*TxtABin) (const char* buffer, void* reg);

bool ProductoTxtFABin (const char* buffer, void* reg);
bool ProductoTxtVABin (const char* buffer, void* reg);

bool generarProductosBin(const char* nomArch);
bool cargarPilaDeArchivoBin (tPila* pila, const char* nomArch, size_t tamReg);
bool cargarPilaDeArchivoTxt (tPila* pila, const char* nomArch, size_t tamReg, TxtABin txtABin);

// CargPilaTxt.exe ProductosV.txt V
int main (int argc, char* argv[]) {
    tPila pila;
    Producto dato;
    int i;
    char tipoTxt = argv[ARG_TIPO][0];

    if (!crearPila(&pila)) {
        printf("Error al crear la pila\n");
        return 1;
    }

    if (!cargarPilaDeArchivoTxt(&pila, argv[ARG_TXT], sizeof(Producto), tipoTxt == 'V' ? ProductoTxtVABin : ProductoTxtFABin)) {
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

    // if (!cargarPilaDeArchivoBin(&pila, "Productos.dat", sizeof(Producto))) {
    //     printf("Error al cargar la pila");
    //     return 1;
    // }

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

bool cargarPilaDeArchivoTxt (tPila* pila, const char* nomArch, size_t tamReg, TxtABin txtABin) {

    FILE* archTxt = fopen(nomArch, "rt");
    void* reg;
    char* buffer;
    char* pos;
    bool errorFatal = false;

    if (!archTxt)
        return false;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(archTxt);
        return false;
    }

    buffer = malloc(TAM_LINEA +1);

    if (!buffer) {
        free(reg);
        fclose(archTxt);
        return false;
    }

    pos = fgets(buffer, TAM_LINEA, archTxt);

    while (!errorFatal && pos != NULL) {
        errorFatal = !txtABin(buffer, reg);

        if (!errorFatal)
            apilar(pila, reg, tamReg);

        pos = fgets(buffer, TAM_LINEA, archTxt);
    }

    fclose(archTxt);
    free(reg);
    free(buffer);

    return errorFatal;
}

bool ProductoTxtFABin (const char* buffer, void* reg) {

    char* act = strrchr(buffer, '\n');
    Producto* prod = reg;

    if (!act)
        return false;

    *act = '\0';
    act -= TAM_STOCK;
    sscanf(act, "%d", &(prod -> stock));

    *act = '\0';
    act -= TAM_PRECIO;
    sscanf(act, "%f", &(prod -> precio));

    *act = '\0';
    act -= TAM_DESC;
    strcpy(prod -> descripcion, act);

    *act = '\0';
    strcpy(prod -> codigo, buffer);

    return true;
}

bool ProductoTxtVABin (const char* buffer, void* reg) {

    char* act = strrchr(buffer, '\n');
    Producto* prod = reg;

    if (!act)
        return false;

    *act = '\0';
    act = strrchr(buffer, '|');
    sscanf(act +1, "%d", &(prod -> stock));

    *act = '\0';
    act = strrchr(buffer, '|');
    sscanf(act +1, "%f", &(prod -> precio));

    *act = '\0';
    act = strrchr(buffer, '|');
    strcpy(prod -> descripcion, act +1);

    *act = '\0';
    strcpy(prod -> codigo, buffer);

    return true;
}
