#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1

#define ARG_ARCH_PRODUCTOS 1
#define ARG_ARCH_MOVIMIENTOS 2
#define ARG_ARCH_DESCRIPCIONES 3

typedef struct
{
    char codigo[11];
    char descripcion[21];
    int stock;
}
Producto;


typedef struct
{
    char codigo[11];
    int cantidad;
}
Movimiento;

typedef struct
{
    char codigo[11];
    char descripcion[21];
}
Descripcion;


int generarProductos(const char* nomArchProductos);
int generarMovimientos(const char* nomArchMovimientos);
int generarDescripciones(const char* nomArchDescripciones);
int mostrarProductos(const char* nomArchProductos);
int actualizarStockProductos(const char* nomArchProductos, const char* nomArchMovimientos);
int actualizarDescProductos(const char* nomArchProductos, const char* nomArchDescripciones);
void cambiarExtension(const char* nomArchOr, char* nomArchNuevo, const char* ext);
void procesarProdNuevo(Producto* prodNuevo, Movimiento* mov, FILE* archMov, FILE* archTmp);

// Merge.exe Productos.dat Movimientos.dat Descripciones.dat
int main (int argc, char* argv[]) {

    system("chcp 65001 > nul");


    generarProductos(argv[ARG_ARCH_PRODUCTOS]);
    generarMovimientos(argv[ARG_ARCH_MOVIMIENTOS]);
    generarDescripciones(argv[ARG_ARCH_DESCRIPCIONES]);

    mostrarProductos(argv[ARG_ARCH_PRODUCTOS]);
    printf("\n");

    actualizarStockProductos(argv[ARG_ARCH_PRODUCTOS], argv[ARG_ARCH_MOVIMIENTOS]);

    mostrarProductos(argv[ARG_ARCH_PRODUCTOS]);
    printf("\n");

    actualizarDescProductos(argv[ARG_ARCH_PRODUCTOS], argv[ARG_ARCH_DESCRIPCIONES]);

    mostrarProductos(argv[ARG_ARCH_PRODUCTOS]);
    printf("\n");

    return 0;
}

int generarProductos(const char* nomArchProductos)
{
    // Generar productos ordenadoas por código.
    Producto vProductos[] =
    {
        {"ANANA", "Ananá amarilla", 100},
        {"BANANA", "Banana orgánica", 50},
        {"CEREZA", "Cereza roja", 60},
        {"FRESA", "Fresa dulce", 75},
        {"MANZANA", "Manzana roja", 200},
        {"NARANJA", "Naranja jugosa", 150},
        {"PERA", "Pera Williams", 80},
        {"UVA", "Uva sin semillas", 120},
        {"ZANAHORIA", "Zanahoria fresca", 90}
    };

    FILE* archivo = fopen(nomArchProductos, "wb");

    if(!archivo)
    {
        perror("Error al abrir el archivo de productos");
        return ERR_ARCHIVO;
    }

    fwrite(vProductos, sizeof(Producto), sizeof(vProductos) / sizeof(Producto), archivo);

    fclose(archivo);
    return 0;
}

int generarMovimientos(const char* nomArchMovimientos)
{
    // Generar movimientos de stock, ordenados por código.
    Movimiento vMovimientos[] =
    {
        {"ANANA", 20},
        {"BANANA", -10},
        {"CEREZA", 15},
        {"CEREZA", 20},
        {"CIRUELA", 10},
        {"FRESA", -5},
        {"KIWI", 30},
        {"KIWI", 20},
        {"LECHUGA", 15},
        {"LECHUGA", -5},
        {"LECHUGA", 20},
        {"MANZANA", -20},
        {"UVA", 25}
    };

    FILE* archivo = fopen(nomArchMovimientos, "wb");

    if(!archivo)
    {
        perror("Error al abrir el archivo de movimientos");
        return ERR_ARCHIVO;
    }

    fwrite(vMovimientos, sizeof(Movimiento), sizeof(vMovimientos) / sizeof(Movimiento), archivo);

    fclose(archivo);
    return 0;
}

int generarDescripciones(const char* nomArchDescripciones)
{
    // Generar descripciones, ordenados por código.
    Descripcion vDescripcion[] =
    {

        {"CIRUELA", "Ciruela gota de miel"},
        {"KIWI", "Kiwi de la patagonia"},
        {"LECHUGA", "Lechuga mantecosa"},
    };

    FILE* archivo = fopen(nomArchDescripciones, "wb");

    if(!archivo)
    {
        perror("Error al abrir el archivo de descripciones");
        return ERR_ARCHIVO;
    }

    fwrite(vDescripcion, sizeof(Descripcion), sizeof(vDescripcion) / sizeof(Descripcion), archivo);

    fclose(archivo);
    return 0;
}

int mostrarProductos(const char* nomArchProductos)
{
    FILE* archivo = fopen(nomArchProductos, "rb");

    if(!archivo)
    {
        perror("Error al abrir el archivo de productos");
        return ERR_ARCHIVO;
    }

    Producto producto;

    printf("%-11s %-21s %s\n", "Código", "Descripción", "Stock");
    printf("%-11s %-21s %s\n", "-------", "-----------", "-----");

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1)
    {
        printf("%-11s %-21s %3d\n", producto.codigo, producto.descripcion, producto.stock);
    }

    fclose(archivo);
    return 0;
}

int actualizarStockProductos(const char* nomArchProductos, const char* nomArchMovimientos) {

    FILE* archProd = fopen(nomArchProductos, "rb");

    if (!archProd)
        return ERR_ARCHIVO;

    FILE* archMov = fopen(nomArchMovimientos, "rb");

    if (!archMov) {
        fclose(archProd);
        return ERR_ARCHIVO;
    }

    char nomArchTmp[255];
    cambiarExtension(nomArchProductos, nomArchTmp, "tmp");

    FILE* archTmp = fopen(nomArchTmp, "wb");

    if (!archProd) {
        fclose(archProd);
        fclose(archMov);
        return ERR_ARCHIVO;
    }

    Producto prod, prodNuevo;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Movimiento), 1, archMov);

    while (!feof(archProd) && !feof(archMov)) {

        comp = strcmp(prod.codigo, mov.codigo);

        if (comp == 0) {
            prod.stock += mov.cantidad;
            fread(&mov, sizeof(Movimiento), 1, archMov);
        }

        else if (comp < 0) {
            fwrite(&prod, sizeof(Producto), 1, archTmp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        else
            procesarProdNuevo(&prodNuevo, &mov, archMov, archTmp);
    }

    while (!feof(archProd)) {
        fwrite(&prod, sizeof(Producto), 1, archTmp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    while (!feof(archMov))
        procesarProdNuevo(&prodNuevo, &mov, archMov, archTmp);

    fclose(archProd);
    fclose(archMov);
    fclose(archTmp);

    remove(nomArchProductos);
    rename(nomArchTmp, nomArchProductos);

    return TODO_OK;
}

int actualizarDescProductos(const char* nomArchProductos, const char* nomArchDescripciones) {

    FILE* archProd = fopen(nomArchProductos, "r+b");

    if (!archProd)
        return ERR_ARCHIVO;

    FILE* archDesc = fopen(nomArchDescripciones, "rb");

    if (!archDesc) {
        fclose(archProd);
        return ERR_ARCHIVO;
    }

    Producto prod;
    Descripcion desc;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&desc, sizeof(Descripcion), 1, archDesc);

    while (!feof(archProd) && !feof(archProd)) {

        if (strcmp(prod.codigo, desc.codigo) == 0) {
            strcpy(prod.descripcion, desc.descripcion);

            fseek(archProd, (long) -sizeof(Producto), SEEK_CUR);
            fwrite(&prod, sizeof(Producto), 1, archProd);

            fflush(archProd);

            fread(&prod, sizeof(Producto), 1, archProd);
            fread(&desc, sizeof(Descripcion), 1, archDesc);
        } else
            fread(&prod, sizeof(Producto), 1, archProd);
    }

    fclose(archProd);
    fclose(archDesc);

    return TODO_OK;
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

void procesarProdNuevo(Producto* prodNuevo, Movimiento* mov, FILE* archMov, FILE* archTmp) {

    strcpy(prodNuevo -> codigo, mov -> codigo);
    *(prodNuevo -> descripcion) = '\0';
    prodNuevo -> stock = mov -> cantidad;

    fread(mov, sizeof(Movimiento), 1, archMov);

    while (!feof(archMov) && strcmp(prodNuevo -> codigo, mov -> codigo) == 0) {
        prodNuevo -> stock += mov -> cantidad;
        fread(mov, sizeof(Movimiento), 1, archMov);
    }

    fwrite(prodNuevo, sizeof(Producto), 1, archTmp);
}
