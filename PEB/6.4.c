#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cod;
    float precio;
    char desc[51];
} TPrecio;

float ingFloatMayA(float);
void mostrarArch(FILE *);
void actualizarArch(float, FILE *);

int main () {
    float porc;
    FILE *fp;

    printf("Actualizador de precios por incremento.\n\n");
    printf("Ingresa el porcentaje de incremento (mayor a 0%): ");
    porc = ingFloatMayA(0);

    fp = fopen("Archivos/PRECIOS.dat", "r+b");

    if (fp == NULL) {
        printf("Error al abrir PRECIOS.DAT");
        exit(1);
    }

    printf("Archivo antes de la actualizacion:\n");
    mostrarArch(fp);
    rewind(fp);
    actualizarArch(porc, fp);
    rewind(fp);

    printf("\nArchivo luego de la actualizacion:\n");
    mostrarArch(fp);

    fclose(fp);
    return 0;
}

float ingFloatMayA(float limi) {
    float dato;

    do {
        scanf("%f", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

void mostrarArch(FILE *fp) {
    TPrecio precio;

    printf("Codigo\tPrecio\tDescripcion\n");

    fread(&precio, sizeof(TPrecio), 1, fp);

    while (!feof(fp)) {
        printf("%d\t$%.2f\t%s\n", precio.cod, precio.precio, precio.desc);
        fread(&precio, sizeof(TPrecio), 1, fp);
    }    
}

void actualizarArch(float porc, FILE *fp) {
    TPrecio precio;

    fread(&precio, sizeof(TPrecio), 1, fp);

    while (!feof(fp)) {
        fseek(fp, -sizeof(TPrecio), SEEK_CUR);
        precio.precio = precio.precio * (porc / 100) + precio.precio;
        fwrite(&precio, sizeof(TPrecio), 1, fp);
        fflush(fp);
        fread(&precio, sizeof(TPrecio), 1, fp);
    }    

}