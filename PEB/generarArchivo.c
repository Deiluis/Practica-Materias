#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    float precio;
    char desc[51];
} TPrecio;

// void generarVentas(TVenta[], int);
// void mostrarVentas(TVenta[], int);
void cargarArchivo(TPrecio[]);
void mostrarArchivo();


int main() {
    TPrecio precios[] = {
        { 122, 50.5, "Lorem" },
        { 456, 79.3, "Lorem impsum" },
        { 234, 50.2, "Mandarina aaa aaa" },
        { 406, 60, "Lorem" },
        { 428, 67.6, "Juan sdkas" },
        { 512, 110.4, "asasaas asasas" },
        { 892, 90.2, "holaaaaaaaaaa " },
        { 1122, 30.2, "asasasas" },
        { 999, 64.3, "asssssssss aaaaaaaa" },
    };

    // generarVentas(ventas, 50);
    // mostrarVentas(ventas, 50);
    cargarArchivo(precios);
    mostrarArchivo();

    return 0;
}

// void generarVentas(TVenta ventas[], int n) {
//     for (int i = 0; i < n; i++) {
//         ventas[i].anio = rand() % (2023 - 2014 + 1) + 2014; // Entre 2014 y 2023
//         ventas[i].mes = rand() % 12 + 1;                     // Mes entre 1 y 12
//         ventas[i].dia = rand() % 28 + 1;                     // Día entre 1 y 28 (para simplificar)
//         ventas[i].codp = rand() % 1000 + 1;                  // Código de producto entre 1 y 1000
//         ventas[i].imp = (float)(rand() % 10000) / 100;       // Importe entre 0.00 y 100.00
//     }
// }

// void mostrarVentas(TVenta ventas[], int n) {
//     printf("Ventas del array:\n");

//     for (int i = 0; i < n; i++) {
//         printf("Venta %d: %02d/%02d/%d, Cod: %d, Importe: %.2f\n", i + 1, ventas[i].dia, ventas[i].mes, ventas[i].anio, ventas[i].codp, ventas[i].imp);
//     }
// }

void cargarArchivo(TPrecio precios[]) {
    FILE *fp;
    int cant = 9;

    fp = fopen("Archivos/PRECIOS.DAT", "wb");

    if (fp == NULL) {
        printf("Error al crear PRECIOS.DAT");
        exit(1);
    }

    fwrite(precios, sizeof(TPrecio), cant, fp);

    fclose(fp);
}

void mostrarArchivo() {
    FILE *fp;
    TPrecio precio;

    fp = fopen("Archivos/PRECIOS.DAT", "rb");

    if (fp == NULL) {
        printf("Error al leer PRECIOS.DAT");
        exit(1);
    }

    fread(&precio, sizeof(TPrecio), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%d\t$%.2f\t%s\n", precio.cod, precio.precio, precio.desc);
        fread(&precio, sizeof(TPrecio), 1, fp);
    }
    
    fclose(fp);
}