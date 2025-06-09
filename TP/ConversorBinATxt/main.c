#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_BIN 1
#define ARG_TXT 2
#define ARG_TIPO_TXT 3

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2

#define TAM_APYN 20

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

typedef void (*BinATxt) (const void* reg, FILE* archTxt);

int convBinATxt (const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt);
void empleadoBinATxtV (const void* reg, FILE* archTxt);
void empleadoBinATxtF (const void* reg, FILE* archTxt);
int generarEmpleadosBin(const char* nomArchBin);

// ConversorBinATxt Empleados.dat EmpleadosV.txt V

int main(int argc, char* argv[])
{
    system("chcp 65000 > nul");


    int ret = generarEmpleadosBin(argv[ARG_BIN]);

    char tipoTxt = argv[ARG_TIPO_TXT][0];
    BinATxt conv = tipoTxt == 'V' ? empleadoBinATxtV : empleadoBinATxtF;

    ret = convBinATxt(argv[ARG_BIN], argv[ARG_TXT], sizeof(Empleado), conv);

    char c = -31;

    printf("%c", c);

    return ret;
}

int convBinATxt (const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt) {

    void* reg = malloc(tamReg);

    if (reg == NULL)
        return ERR_MEMORIA;

    FILE* archBin = fopen(nomArchBin, "rb");

    if (archBin == NULL) {
        free(reg);
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "wt");

    if (archTxt == NULL) {
        fclose(archBin);
        free(reg);
        return ERR_ARCHIVO;
    }

    fread(reg, tamReg, 1, archBin);

    while (!feof(archBin)) { // Tambien puedo hacer while (fread(reg, tamReg, 1, archBin))
       binATxt(reg, archTxt); // Estaria mal que esta funcion abra y cierre el archivo todo el tiempo solo para guardar un archivo
       fread(reg, tamReg, 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    free(reg);

    return TODO_OK;
}

void empleadoBinATxtV (const void* reg, FILE* archTxt) {

    const Empleado* empl = reg;

    fprintf(
        archTxt, "%d|%s|%c|%d/%d/%d|%.2f\n",
        empl -> dni, empl -> apyn, empl -> sexo,
        empl -> fIngr.d, empl -> fIngr.m, empl -> fIngr.a,
        empl -> sueldo
    );
}

void empleadoBinATxtF (const void* reg, FILE* archTxt) {

    const Empleado* empl = reg;

    fprintf(
        archTxt, "%08d%-20s%c%02d%02d%04d%011.2f\n",
        empl -> dni, empl -> apyn, empl -> sexo,
        empl -> fIngr.d, empl -> fIngr.m, empl -> fIngr.a,
        empl -> sueldo
    );
}

int generarEmpleadosBin(const char* nomArchBin) {

    Empleado empleados[] = {
        {12345678, "Juan Perez",      'M', {15, 3, 2015}, 85000.50},
        {23456789, "Máría Gomez",     'F', {1, 7, 2018}, 92000.75},
        {34567890, "Luis Fernandez",  'M', {23, 11, 2020}, 78000.00},
        {45678901, "Ana Torres",      'F', {5, 5, 2019}, 88000.25},
        {56789012, "Carlos Diaz",     'M', {10, 1, 2021}, 80000.10},
        {67890123, "Sofia Ruiz",      'F', {3, 8, 2017}, 91000.40},
        {78901234, "Pedro Sanchez",   'M', {12, 2, 2016}, 86000.00},
        {89012345, "Laura Ortega",    'F', {28, 9, 2022}, 79500.65},
        {90123456, "Diego Ramirez",   'M', {7, 4, 2014}, 87000.30},
        {11223344, "Lucia Herrera",   'F', {19, 6, 2020}, 94000.90}
    };
    FILE* archBin = fopen(nomArchBin, "wb");

    if (archBin == NULL)
        return ERR_ARCHIVO;

    fwrite(empleados, sizeof(Empleado), 10, archBin);
    fclose(archBin);

    return TODO_OK;
}
