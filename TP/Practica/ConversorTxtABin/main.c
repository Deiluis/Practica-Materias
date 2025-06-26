#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define ARG_ARCH_TXT 1
#define ARG_TIPO_TXT 2
#define ARG_ARCH_BIN 3

#define BUFFER_TAM 254

#define TAM_DNI 8
#define TAM_APYN 20
#define TAM_SEXO 1
#define TAM_F_INGRESO 10
#define TAM_SUELDO 8

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define SIN_MEM 2
#define ERR_BUFFER_CORTO 3

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

typedef int (*TxtABin) (void* reg, char* buffer);

int mostrarArchivoBin (const char* nomArch);
int convTxtABin (const char* nomArchTxt, const char* nomArchBin, size_t tamReg, size_t tamBuffer, TxtABin txtABin);
int empleadoTxtFABin (void* reg, char* buffer);
int empleadoTxtVABin (void* reg, char* buffer);

// ConversorTxtABin.exe EmpleadosV.txt V Empleados.dat
int main (int argc, char* argv[]) {

    int cod;

    TxtABin conv = argv[ARG_TIPO_TXT][0] == 'V' ? empleadoTxtVABin : empleadoTxtFABin;

    cod = convTxtABin(argv[ARG_ARCH_TXT], argv[ARG_ARCH_BIN], sizeof(Empleado), BUFFER_TAM, conv);

    if (cod != TODO_OK)
        return cod;

    mostrarArchivoBin(argv[ARG_ARCH_BIN]);

    return 0;
}

int convTxtABin (const char* nomArchTxt, const char* nomArchBin, size_t tamReg, size_t tamBuffer, TxtABin txtABin) {

    void* reg = malloc(tamReg);

    if (reg == NULL)
        return SIN_MEM;

    FILE* archBin = fopen(nomArchBin, "wb");

    if (archBin == NULL) {
        free(reg);
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "rt");

    if (archTxt == NULL) {
        free(reg);
        fclose(archBin);
        return ERR_ARCHIVO;
    }

    char* buffer = malloc((tamBuffer +1) * sizeof(char));

    if (buffer == NULL) {
        free(reg);
        fclose(archBin);
        fclose(archTxt);
        return SIN_MEM;
    }

    int cod = TODO_OK;

    while (cod == TODO_OK && fgets(buffer, tamBuffer, archTxt)) {

        cod = txtABin(reg, buffer);

        if (cod == TODO_OK)
            fwrite(reg, tamReg, 1, archBin);
    }

    free(reg);
    free(buffer);
    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int empleadoTxtFABin (void* reg, char* buffer) {

    Empleado* empl = reg;

    char* act = strrchr(buffer, '\n');

    if (!act)
        return ERR_BUFFER_CORTO;

    *act = '\0';
    act -= TAM_SUELDO;
    sscanf(act, "%f", &(empl -> sueldo));

    *act = '\0';
    act -= TAM_F_INGRESO;
    sscanf(act, "%2d/%2d/%4d", &(empl -> fIngr.d), &(empl -> fIngr.m), &(empl -> fIngr.a));

    *act = '\0';
    act -= TAM_SEXO;
    empl -> sexo = *act;

    *act = '\0';
    act -= TAM_APYN;
    strcpy(empl -> apyn, act);

    *act = '\0';
    sscanf(buffer, "%d", &(empl -> dni));

    return TODO_OK;
}

int empleadoTxtVABin (void* reg, char* buffer) {

    Empleado* empl = reg;

    char* act = strrchr(buffer, '\n');

    if (!act)
        return ERR_BUFFER_CORTO;

    *act = '\0';
    act = strrchr(buffer, '|');
    sscanf(act +1, "%f", &(empl -> sueldo));

    *act = '\0';
    act = strrchr(buffer, '|');
    sscanf(act +1, "%d/%d/%d", &(empl -> fIngr.d), &(empl -> fIngr.m), &(empl -> fIngr.a));

    *act = '\0';
    act = strrchr(buffer, '|');
    empl -> sexo = *(act +1);

    *act = '\0';
    act = strrchr(buffer, '|');
    strcpy(empl -> apyn, act +1);

    *act = '\0';
    sscanf(buffer, "%d", &(empl -> dni));

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