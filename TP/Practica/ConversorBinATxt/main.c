#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define ARG_ARCH_BIN 1
#define ARG_ARCH_TXT 2
#define ARG_TIPO_TXT 3

#define TAM_APYN 20

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define SIN_MEM 2

typedef struct {
    int d;
    int m;
    int a;
} Fecha;

typedef struct {
    int dni;
    char apyn[TAM_APYN +1];
    char sexo;
    Fecha fIngr;
    float sueldo;
} Empleado;

typedef void (*BinATxt) (void* reg, FILE* archTxt);

int generarArchivoBin (const char* nomArch);
int mostrarArchivoBin (const char* nomArch);
int convBinATxt (const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt);
void empleadoBinATxtF (void* reg, FILE* archTxt);
void empleadoBinATxtV (void* reg, FILE* archTxt);

// ConversorBinATxt.exe Empleados.dat EmpleadosV.txt V
int main (int argc, char* argv[]) {

    int cod;

    cod = generarArchivoBin(argv[ARG_ARCH_BIN]);

    if (cod != TODO_OK)
        return cod;

    cod = mostrarArchivoBin(argv[ARG_ARCH_BIN]);

    if (cod != TODO_OK)
        return cod;

    BinATxt conv = argv[ARG_TIPO_TXT][0] == 'V' ? empleadoBinATxtV : empleadoBinATxtF;

    cod = convBinATxt(argv[ARG_ARCH_BIN], argv[ARG_ARCH_TXT], sizeof(Empleado), conv);

    if (cod != TODO_OK)
        return cod;

    return TODO_OK;
}

int generarArchivoBin (const char* nomArch) {

    Empleado empleados[] = {
        {12345678, "Juan Perez",      'M', {15, 3, 2015}, 85000.50},
        {23456789, "Maria Gomez",     'F', {1, 7, 2018}, 92000.75},
        {34567890, "Luis Fernandez",  'M', {23, 11, 2020}, 78000.00},
        {45678901, "Ana Torres",      'F', {5, 5, 2019}, 88000.25},
        {56789012, "Carlos Diaz",     'M', {10, 1, 2021}, 80000.10},
        {67890123, "Sofia Ruiz",      'F', {3, 8, 2017}, 91000.40},
        {78901234, "Pedro Sanchez",   'M', {12, 2, 2016}, 86000.00},
        {89012345, "Laura Ortega",    'F', {28, 9, 2022}, 79500.65},
        {90123456, "Diego Ramirez",   'M', {7, 4, 2014}, 87000.30},
        {11223344, "Lucia Herrera",   'F', {19, 6, 2020}, 94000.90}
    };

    FILE* archBin = fopen(nomArch, "wb");

    if (archBin == NULL)
        return ERR_ARCHIVO;

    fwrite(empleados, sizeof(Empleado), sizeof(empleados) / sizeof(Empleado), archBin);
    fclose(archBin);

    return TODO_OK;
}

int mostrarArchivoBin (const char* nomArch) {

    FILE* archBin = fopen(nomArch, "rb");
    Empleado empl;

    if (archBin == NULL)
        return ERR_ARCHIVO;

    while (fread(&empl, sizeof(Empleado), 1, archBin)) {
        printf("%d %-20s %c %02d/%02d/%d %.2f\n", empl.dni, empl.apyn, empl.sexo, empl.fIngr.d, empl.fIngr.m, empl.fIngr.a, empl.sueldo);
    }

    fclose(archBin);

    return TODO_OK;
}

int convBinATxt (const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt) {

    void* reg = malloc(tamReg);

    if (reg == NULL)
        return SIN_MEM;

    FILE* archBin = fopen(nomArchBin, "rb");

    if (archBin == NULL) {
        free(reg);
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "wt");

    if (archTxt == NULL) {
        free(reg);
        fclose(archBin);
        return ERR_ARCHIVO;
    }

    while (fread(reg, sizeof(Empleado), 1, archBin))
        binATxt(reg, archTxt);

    free(reg);
    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

void empleadoBinATxtF (void* reg, FILE* archTxt) {

    Empleado* empl = reg;

    fprintf(archTxt, "%08d%-20s%c%02d/%02d/%4d%05.2f\n",
        empl -> dni, empl -> apyn, empl -> sexo, empl -> fIngr.d, empl -> fIngr.m, empl -> fIngr.a, empl -> sueldo);
}

void empleadoBinATxtV (void* reg, FILE* archTxt) {

    Empleado* empl = reg;

    fprintf(archTxt, "%d|%s|%c|%d/%d/%d|%f\n",
        empl -> dni, empl -> apyn, empl -> sexo, empl -> fIngr.d, empl -> fIngr.m, empl -> fIngr.a, empl -> sueldo);
}
