#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Repaso/Arbol/Arbol.h"

#define TAM_NOM 50

typedef struct {
    int cod;
    char nombre[TAM_NOM +1];
    float sueldo;
} tEmpleado;

typedef struct {
    int cod;
    int pos;
} tEmpleadoIdx;

int generarArchEmpl (const char* nomArch);
void mostrarEmpl (void* elem);
void mostrarEmplIdx (void* elem);
void sumarSueldoEmpl (const void* elem, void* dst);
int compararEmpl (const void* e1, const void* e2);
int compararNomEmpl (const void* e1, const void* e2);
void convCodEmplAIdx (void* idx, const void* reg, int pos);

int main () {

    tArbol aCreacion;

    crearArbol(&aCreacion);

    if (generarArchEmpl("empleados.dat") == TODO_OK)
        printf("Archivo creado.\n");
    else
        printf("Error creando el archivo de empleados.\n");

    if (insertarBinEnArbol(&aCreacion, "empleados.dat", sizeof(tEmpleado), sizeof(tEmpleadoIdx), convCodEmplAIdx, compararEmpl, NULL) == TODO_OK) {
        recorrerArbolR(&aCreacion, INORDEN, mostrarEmplIdx);
    }

    vaciarArbol(&aCreacion);



    return 0;
}

int generarArchEmpl (const char* nomArch) {

    FILE* archBin = fopen(nomArch, "wb");

    if (!archBin)
        return ERR_ARCHIVO;

    tEmpleado empls[] = {
        {7, "Lucio", 3500},
        {10, "Josefa", 4700},
        {3, "Martin", 3000},
        {4, "Maria", 1000},
        {9, "Daniela", 15000},
        {6, "Diego", 7000},
        {1, "Juan", 11000},
        {8, "Martina", 3000},
        {2, "Alberto", 20000},
        {5, "Luis", 2000},
    };

    fwrite(empls, sizeof(tEmpleado), sizeof(empls) / sizeof(tEmpleado), archBin);
    fclose(archBin);

    return TODO_OK;
}




void mostrarEmpl (void* elem) {
    tEmpleado* empl = (tEmpleado*) elem;
    printf("%d\t%s\t$%.2f\n", empl -> cod, empl -> nombre, empl -> sueldo);
}

void mostrarEmplIdx (void* elem) {
    tEmpleadoIdx* idx = (tEmpleadoIdx*) elem;
    printf("%d\t%d\n", idx -> cod, idx -> pos);
}

void sumarSueldoEmpl (const void* elem, void* dst) {
    tEmpleado* empl = (tEmpleado*) elem;
    float* sueldo = (float*) dst;
    *sueldo += empl -> sueldo;
}

int compararEmpl (const void* e1, const void* e2) {
    tEmpleado* empl1 = (tEmpleado*) e1;
    tEmpleado* empl2 = (tEmpleado*) e2;

    return empl1 -> cod - empl2 -> cod;
}

int compararNomEmpl (const void* e1, const void* e2) {
    tEmpleado* empl1 = (tEmpleado*) e1;
    tEmpleado* empl2 = (tEmpleado*) e2;
    return strcmpi(empl1 -> nombre, empl2 -> nombre);
}

void convCodEmplAIdx (void* idx, const void* reg, int pos) {
    tEmpleadoIdx* emplIdx = (tEmpleadoIdx*) idx;
    tEmpleado* empl = (tEmpleado*) reg;

    emplIdx -> cod = empl -> cod;
    emplIdx -> pos = pos;
}
