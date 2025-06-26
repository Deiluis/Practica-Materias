#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1


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


int generarProductos(const char* nomArchProductos);
int generarMovimientos(const char* nomArchMovimientos);
int mostrarProductos(const char* nomArchProductos);
int actualizarProductos(const char* nomArchProductos, const char* nomArchMovimientos);
void cambiarExtension(const char* nomArch, const char* ext, char* nomArchCambiado);
void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp);


// Merge.exe Productos.dat Movimientos.dat

int main(int argc, char* argv[])
{
    system("chcp 65001 > nul");

    generarProductos(argv[1]);
    generarMovimientos(argv[2]);

    puts("Productos antes de actualizar:");
    mostrarProductos(argv[1]);

    actualizarProductos(argv[1], argv[2]);

    puts("\nProductos después de actualizar:");
    mostrarProductos(argv[1]);

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
//        {"KIWI", "Kiwi verde", 30},
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
        {"FRESA", -5},
        {"KIWI", 30},
        {"KIWI", 20},
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


int actualizarProductos(const char* nomArchProductos, const char* nomArchMovimientos)
{
    FILE* archProds = fopen(nomArchProductos, "rb");

    if(!archProds)
    {
        puts("Error abriendo productos.");
        return ERR_ARCHIVO;
    }

    FILE* archMovs = fopen(nomArchMovimientos, "rb");

    if(!archMovs)
    {
        fclose(archProds);
        puts("Error abriendo movimientos.");
        return ERR_ARCHIVO;
    }

    char nomArchProdsTemp[51];
    cambiarExtension(nomArchProductos, "tmp", nomArchProdsTemp);

    FILE* archProdsTemp = fopen(nomArchProdsTemp, "wb");

    if(!archProdsTemp)
    {
        fclose(archProds);
        fclose(archMovs);
        puts("Error abriendo productos temporal.");
        return ERR_ARCHIVO;
    }

    Producto prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProds);
    fread(&mov, sizeof(Movimiento), 1, archMovs);
    while(!feof(archProds) && !feof(archMovs))
    {
        comp = strcmp(prod.codigo, mov.codigo);

        if(comp == 0) // Prod con mov
        {
            prod.stock += mov.cantidad;
            fread(&mov, sizeof(Movimiento), 1, archMovs);
        }

        if(comp < 0) // Prod sin mov
        {
            fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
            fread(&prod, sizeof(Producto), 1, archProds);
        }

        if(comp > 0) // Prod nuevo
        {
            procesarProductoNuevo(&mov, archMovs, archProdsTemp);
        }
    }

    while(!feof(archProds)) // Prods sin movs.
    {
        fwrite(&prod, sizeof(Producto), 1, archProdsTemp);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    while(!feof(archMovs)) // Prods nuevos.
    {
        procesarProductoNuevo(&mov, archMovs, archProdsTemp);
    }

    fclose(archProds);
    fclose(archMovs);
    fclose(archProdsTemp);

    remove(nomArchProductos);
    rename(nomArchProdsTemp, nomArchProductos);

    return TODO_OK;
}


void cambiarExtension(const char* nomArch, const char* ext, char* nomArchCambiado)
{
    strcpy(nomArchCambiado, nomArch);
    char* punto = strchr(nomArchCambiado, '.');
    strcpy(punto + 1, ext);
}


void procesarProductoNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsTemp)
{
    Producto prodNuevo;
    strcpy(prodNuevo.codigo, mov->codigo);
    prodNuevo.descripcion[0] = '\0';
    prodNuevo.stock = mov->cantidad;
    fread(mov, sizeof(Movimiento), 1, archMovs);
    while(!feof(archMovs) && strcmp(mov->codigo, prodNuevo.codigo) == 0)
    {
        prodNuevo.stock += mov->cantidad;
        fread(mov, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNuevo, sizeof(Producto), 1, archProdsTemp);
}
