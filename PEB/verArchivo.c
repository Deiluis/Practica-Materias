#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dia, mes, anio;
} TFecha;

typedef struct {
    char nomape[36];
    int dni;
    char loc[41];
    char email[21];
    TFecha fecha;
} TVisitante;

void mostrarArchivo();
// void mostrarArchivo2();
// void mostrarArchivo3();

int main() {
    mostrarArchivo();
    // mostrarArchivo2();
    // mostrarArchivo3();
    return 0;
}

void mostrarArchivo() {
    FILE *fp;
    TVisitante reg;

    fp = fopen("san justo.dat", "rb");

    if (fp == NULL) {
        printf("Error al leer san justo.dat");
        exit(1);
    }

    fread(&reg, sizeof(TVisitante), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%s\t%d\t%s\t%s\t%d/%d/%d\n", reg.nomape, reg.dni, reg.loc, reg.email, reg.fecha.dia, reg.fecha.mes, reg.fecha.anio);
        fread(&reg, sizeof(TVisitante), 1, fp);
    }
    
    fclose(fp);
}

// void mostrarArchivo2() {
//     FILE *fp;
//     TProd reg;

//     fp = fopen("Archivos/PRODUCTOS2.dat", "rb");

//     if (fp == NULL) {
//         printf("Error al leer PRODUCTOS2.dat");
//         exit(1);
//     }

//     fread(&reg, sizeof(TProd), 1, fp);

//     printf("Contenido del archivo:\n");

//     while (!feof(fp)) {
//         printf("%d\t%s\t%.2f\t%d\t%d\t%d\n", reg.cod, reg.desc, reg.precio, reg.stock, reg.pPed, reg.cPed);
//         fread(&reg, sizeof(TProd), 1, fp);
//     }
    
//     fclose(fp);
// }

// void mostrarArchivo3() {
//     FILE *fp;
//     TPed reg;

//     fp = fopen("Archivos/PEDIDOS.dat", "rb");

//     if (fp == NULL) {
//         printf("Error al leer PEDIDOS.dat");
//         exit(1);
//     }

//     fread(&reg, sizeof(TPed), 1, fp);

//     printf("Contenido del archivo:\n");

//     while (!feof(fp)) {
//         printf("%d\t%d\n", reg.cod, reg.cant);
//         fread(&reg, sizeof(TPed), 1, fp);
//     }
    
//     fclose(fp);
// }