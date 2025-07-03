#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../TDAVector/Vector.h"

#define STOCK_INVALIDO 7

typedef struct {
    char cod[11];
    char desc[51];
    size_t stock;
} Producto;

typedef struct {
    char cod[11];
    unsigned int nroReg;
} ProductoIdx;

typedef void (*Mos) (void* elem);

int generarArchivoFuente (const char* nomArch);
int generarArchivoIdx (const char* nomArch);
void cambiarExtension(const char* nomArchOr, char* nomArchNuevo, const char* ext);
int mostrarArchivo (const char* nomArch, size_t regTam, Mos mos);
void mostrarProducto (void* elem);
void mostrarProductoIdx (void* elem);
int compararProductosIdx (const void* a, const void* b);
int actualizarStockProducto (const char* nomArch, const char* cod, size_t sumaStock);


int main() {

    system("chcp 65001 > nul");

    //generarArchivoFuente("./Productos.dat");
    //mostrarArchivo("Productos.dat", sizeof(Producto), mostrarProducto);

    // printf("\n");

    // generarArchivoIdx("Productos.dat");
    // mostrarArchivo("Productos.idx", sizeof(ProductoIdx), mostrarProductoIdx);

    mostrarArchivo("Productos.dat", sizeof(Producto), mostrarProducto);

    printf("\n");

    actualizarStockProducto("Productos.dat", "P0011", 20);

    printf("\n");

    mostrarArchivo("Productos.dat", sizeof(Producto), mostrarProducto);

    return 0;
}

int generarArchivoFuente (const char* nomArch) {

    FILE* arch = fopen(nomArch, "wb");

    if (!arch)
        return ERR_ARCHIVO;

    Producto productos[] = {
        { "P0009", "Ciruela",      140 },
        { "P0001", "Banana",       150 },
        { "P0011", "Sandía",       80  },
        { "P0004", "Naranja",      170 },
        { "P0005", "Limón",        130 },
        { "P0019", "Mango",        110 },
        { "P0016", "Pomelo",       155 },
        { "P0020", "Papaya",       95  },
        { "P0007", "Uva",          220 },
        { "P0018", "Higo",         45  },
        { "P0008", "Durazno",      160 },
        { "P0010", "Melón",        100 },
        { "P0002", "Manzana",      200 },
        { "P0014", "Cereza",       65  },
        { "P0015", "Mandarina",    190 },
        { "P0012", "Frutilla",     240 },
        { "P0013", "Arándano",     75  },
        { "P0003", "Pera",         180 },
        { "P0006", "Kiwi",         90  },
        { "P0017", "Granada",      50  },
    };

    fwrite(productos, sizeof(Producto), sizeof(productos) / sizeof(Producto), arch);
    fclose(arch);

    return OK;
}

int generarArchivoIdx (const char* nomArch) {

    FILE* archFuente = fopen(nomArch, "rb");

    if (!archFuente)
        return ERR_ARCHIVO;

    Vector idx;
    char nomArchIdx[255];

    Producto prod;
    ProductoIdx prodIdx;

    size_t nroReg = 0;

    if (!vectorCrear(&idx, sizeof(ProductoIdx)))
        return SIN_MEM;

    while (fread(&prod, sizeof(Producto), 1, archFuente)) {
        strcpy(prodIdx.cod, prod.cod);
        prodIdx.nroReg = nroReg;

        vectorOrdInsertar(&idx, &prodIdx, compararProductosIdx);

        nroReg++;
    }

    fclose(archFuente);

    cambiarExtension(nomArch, nomArchIdx, "idx");

    vectorGrabar(&idx, nomArchIdx);

    vectorDestruir(&idx);

    return OK;
}

int actualizarStockProducto (const char* nomArch, const char* cod, size_t sumaStock) {

    char nomArchIdx[255];
    cambiarExtension(nomArch, nomArchIdx, "idx");

    Vector idx;

    vectorCrearDeArchivo(&idx, sizeof(ProductoIdx), nomArchIdx);

    ProductoIdx prodIdx;
    strcpy(prodIdx.cod, cod);

    int pos = vectorOrdBuscar(&idx, &prodIdx, compararProductosIdx);

    if (pos == -1) {
        printf("Indice no encontrado");
        return NO_ENCONTRADO;
    }

    vectorDestruir(&idx);

    FILE* archFuente = fopen(nomArch, "r+b");

    if (!archFuente)
        return ERR_ARCHIVO;

    Producto prod;
    size_t nStock;


    fseek(archFuente, (long) sizeof(Producto) * prodIdx.nroReg, SEEK_SET);
    fread(&prod, sizeof(Producto), 1, archFuente);

    nStock = prod.stock;
    nStock += sumaStock;

    if (nStock < 0) {
        printf("Nuevo stock invalido");
        fclose(archFuente);
        return STOCK_INVALIDO;
    }

    prod.stock = nStock;

    fseek(archFuente, (long) sizeof(Producto) * prodIdx.nroReg, SEEK_SET);
    fwrite(&prod, sizeof(Producto), 1, archFuente);

    fclose(archFuente);

    return OK;
}


int mostrarArchivo (const char* nomArch, size_t regTam, Mos mos) {

    FILE* arch = fopen(nomArch, "rb");

    if (!arch)
        return ERR_ARCHIVO;

    void* reg = malloc(regTam);

    if (!reg) {
        fclose(arch);
        return SIN_MEM;
    }

    while (fread(reg, regTam, 1, arch))
        mos(reg);

    fclose(arch);
    free(reg);

    return OK;
}

void mostrarProducto (void* elem) {

    Producto* prod = elem;
    printf("%-5s %-10s %Iu\n", prod -> cod, prod -> desc, prod -> stock);
}

void mostrarProductoIdx (void* elem) {

    ProductoIdx* prodIdx = elem;
    printf("%-5s %u\n", prodIdx -> cod, prodIdx -> nroReg);
}

void cambiarExtension(const char* nomArchOr, char* nomArchNuevo, const char* ext) {

    strcpy(nomArchNuevo, nomArchOr);

    char* punto = strrchr(nomArchNuevo, '.');

    if (punto)
        strcpy(punto +1, ext);
    else {
        int longStr = strlen(nomArchNuevo);

        *(nomArchNuevo + longStr) = '.';
        strcat(nomArchNuevo + longStr +1, ext);
    }
}

int compararProductosIdx (const void* a, const void* b) {

    const ProductoIdx* prod1 = a;
    const ProductoIdx* prod2 = b;

    return strcmp(prod1 -> cod, prod2 -> cod);
}
