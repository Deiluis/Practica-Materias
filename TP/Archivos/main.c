#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Comun/CodigosRet.h"
#include "../TDAVector/Vector.h"

#define ARG_ARCH 1
#define ARG_PORC 2
#define ARG_COD 3
#define CANT_ARG 4

#define ARG_FALTANTES 1

typedef struct {
    char codigo[11];
    char descripcion[51];
    float precio;
    int stock;
} Producto;

typedef struct {
    char codigo[11];
    unsigned int nroReg;
} ProductoIdx;



int generarProductosBin(const char* nomArchProds);
int generarProductosIdx (const char* nomArchProds);
int mostrarProductos(const char* nomArchProds);
int actualizarPrecioProds(const char* nomArchProds, float porc);
int actualizarPrecio1Prod(const char* nomArchProds, float porc, const char* cod);
int cmpProdIdx (const void* a, const void* b);
void cambiarExtension(const char* nomArch, const char* ext, char* nomArchCambiado);

// Archivos.exe Productos.dat 10 UVA
int main(int argc, char* argv[])
{
    if (argc != CANT_ARG)
        return ARG_FALTANTES;

    generarProductosBin(argv[ARG_ARCH]);
    generarProductosIdx(argv[ARG_ARCH]);

    // atof convierte un string a float
    float porc = atof(argv[ARG_PORC]);

    // Validar que en argc se pasan la cantidad de argumentos necesaria

    puts("Antes:");
    mostrarProductos(argv[ARG_ARCH]);

    actualizarPrecioProds(argv[ARG_ARCH], porc);

    puts("Despues:");
    mostrarProductos(argv[ARG_ARCH]);

    //actualizarPrecio1Prod(argv[ARG_ARCH], porc, argv[ARG_COD]);

    //puts("Despues de actualizar 1:");
    //mostrarProductos(argv[ARG_ARCH]);

    return 0;
}

int generarProductosBin(const char* nomArchProds) {

    Producto prods[10] = {
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

    FILE* arch = fopen(nomArchProds, "wb");

    if (!arch)
        return ERR_ARCHIVO;

    fwrite(prods, sizeof(Producto), 10, arch);
    fclose(arch);

    return OK;
}

int generarProductosIdx (const char* nomArchProds) {

    Vector vIdx;
    vectorCrear(&vIdx, sizeof(ProductoIdx));

    FILE* arch = fopen(nomArchProds, "rb");

    if (!arch)
        return ERR_ARCHIVO;

    Producto prod;
    ProductoIdx prodIdx;
    unsigned int cont = 0;

    while (fread(&prod, sizeof(Producto), 1, arch)) {
        strcpy(prodIdx.codigo, prod.codigo);
        prodIdx.nroReg = cont;
        cont++;
        vectorOrdInsertar(&vIdx, &prodIdx, cmpProdIdx);

    }

    fclose(arch);

    char nomProdIdx[51];

    cambiarExtension(nomArchProds, "idx", nomProdIdx);
    vectorGrabar(&vIdx, nomProdIdx);

    vectorDestruir(&vIdx);

    return OK;
}

int mostrarProductos(const char* nomArchProds) {

    FILE* arch = fopen(nomArchProds, "rb");

    if (!arch)
        return ERR_ARCHIVO;

    Producto prod;

    while (fread(&prod, sizeof(Producto), 1, arch)) {
        printf("%-10s%-20s%8.2f%4d\n", prod.codigo, prod.descripcion, prod.precio, prod.stock);
    }

    fclose(arch);

    return OK;
}

int actualizarPrecioProds(const char* nomArchProds, float porc) {

    FILE* arch = fopen(nomArchProds, "r+b");

    if (!arch)
        return ERR_ARCHIVO;

    Producto prod;
    float factorIncr = 1 + porc / 100;

    while (fread(&prod, sizeof(Producto), 1, arch)) {
        prod.precio *= factorIncr;
        fseek(arch, (long) -sizeof(Producto), SEEK_CUR);
        fwrite(&prod, sizeof(Producto), 1, arch);
        fflush(arch); // Se limpia el buffer para que se reflejen los cambios hechos, tambien puedo usar fseek
    }

    fclose(arch);

    return OK;
}

int actualizarPrecio1Prod(const char* nomArchProds, float porc, const char* cod) {

    char nomProdIdx[51];
    cambiarExtension(nomArchProds, "idx", nomProdIdx);

    Vector vIdx;
    vectorCrearDeArchivo(&vIdx, sizeof(ProductoIdx), nomProdIdx);

    ProductoIdx prodIdx;
    strcpy(prodIdx.codigo, cod);

    int pos = vectorOrdBuscar(&vIdx, &prodIdx, cmpProdIdx);

    if (pos == -1) {
        puts("Indice no encontrado");
        vectorDestruir(&vIdx);
        return NO_ENCONTRADO;
    }

    FILE* archProds = fopen(nomArchProds, "r+b");

    if (!archProds) {
        vectorDestruir(&vIdx);
        return ERR_ARCHIVO;
    }

    Producto prod;

    fseek(archProds, prodIdx.nroReg * sizeof(Producto), SEEK_SET);
    fread(&prod, (long) sizeof(Producto), 1, archProds);

    float factorIncr = 1 + porc / 100;
    prod.precio *= factorIncr;
    fseek(archProds, prodIdx.nroReg * sizeof(Producto), SEEK_SET);
    fwrite(&prod, sizeof(Producto), 1, archProds);

    fclose(archProds);
    vectorDestruir(&vIdx);

    return OK;
}

int cmpProdIdx (const void* a, const void* b) {
    ProductoIdx* prodIdx1 = (ProductoIdx*) a;
    ProductoIdx* prodIdx2 = (ProductoIdx*) b;

    return strcmp(prodIdx1 -> codigo, prodIdx2 -> codigo);
}

void cambiarExtension(const char* nomArch, const char* ext, char* nomArchCambiado) {
    strcpy(nomArchCambiado, nomArch);
    char* punto = strchr(nomArchCambiado, '.');

    // validar si el archivo no tine extension
    // retonar error o concatenar extension con punto

    strcpy(punto +1, ext);
}
