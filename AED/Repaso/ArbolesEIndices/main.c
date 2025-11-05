#include <stdio.h>
#include <stdlib.h>

#define TAM_NOM 50
#define TODO_OK 0
#define ERR_ARCHIVO 1

typedef struct {
    int cod;
    char nombre[TAM_NOM +1];
    float sueldo;
} tEmpleado;

int generarArchEmpl (const char* nomArch);

int main() {

    if (generarArchEmpl("empleados.dat") == TODO_OK)
            printf("Archivo creado.\n");
    else
        printf("Error creando el archivo de empleados.\n");

    return 0;
}

int generarArchEmpl (const char* nomArch) {

    FILE* archBin = fopen(nomArch, "wb");

    if (!archBin)
        return ERR_ARCHIVO;

    tEmpleado empls[] = {
        {1, "Juan", 11000},
        {2, "Alberto", 20000},
        {3, "Martin", 3000},
        {4, "Maria", 1000},
        {5, "Luis", 2000},
        {6, "Diego", 7000},
        {7, "Lucio", 3500},
        {8, "Martina", 3000},
        {9, "Daniela", 15000},
        {10, "Josefa", 4700},
    };

    fwrite(empls, sizeof(tEmpleado), sizeof(empls) / sizeof(tEmpleado), archBin);
    fclose(archBin);

    return TODO_OK;
}

