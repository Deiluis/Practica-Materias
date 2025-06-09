#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARG_TXT 1
#define ARG_TIPO_TXT 2
#define ARG_BIN 3

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define ERR_LINEA_LARGA 3

#define TAM_APYN 20
#define TAM_SUELDO 11
#define TAM_FECHA 8
#define TAM_SEXO 1
#define TAM_LINEA 500

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

typedef int (*TxtABin) (char* linea, void* reg);
typedef bool (*EsErrorFatal) (int cod);

int convTxtABin (const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin, EsErrorFatal esErrorFatal);
int empleadoTxtVABin (char* linea, void* reg);
int empleadoTxtFABin (char* linea, void* reg);
bool eFatalEmp (int cod);
int mostrarEmpleadosBin (const char* nomArchBin);

// ConversorTxtABin EmpleadosV.txt V Empleados.dat

int main(int argc, char* argv[])
{
    int ret;

    char tipoTxt = argv[ARG_TIPO_TXT][0];
    TxtABin conv = tipoTxt == 'V' ? empleadoTxtVABin : empleadoTxtFABin;

    ret = convTxtABin(argv[ARG_TXT], argv[ARG_BIN], sizeof(Empleado), conv, eFatalEmp);

    ret = mostrarEmpleadosBin(argv[ARG_BIN]);

    return ret;
}

int convTxtABin (const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin, EsErrorFatal esErrorFatal) {

    void* reg = malloc(tamReg);

    if (reg == NULL)
        return ERR_MEMORIA;

    FILE* archTxt = fopen(nomArchTxt, "rt");

    if (archTxt == NULL) {

        free(reg);
        return ERR_ARCHIVO;
    }

    FILE* archBin = fopen(nomArchBin, "wb");

    if (archBin == NULL) {
        free(reg);
        fclose(archTxt);
        return ERR_ARCHIVO;
    }

    char linea[TAM_LINEA +1];
    char* pos = fgets(linea, TAM_LINEA, archTxt);
    int ret = TODO_OK;

    while (!esErrorFatal(ret) && pos != NULL) {
        ret = txtABin(linea, reg);

        if (ret == TODO_OK)
            fwrite(reg, tamReg, 1, archBin);

        pos = fgets(linea, TAM_LINEA, archTxt);
    }

    fclose(archBin);
    fclose(archTxt);

    free(reg);

    return ret;
}

int empleadoTxtVABin (char* linea, void* reg) {

    Empleado* empl = reg;
    char* act = strchr(linea, '\n');

    if (act == NULL)
        return ERR_LINEA_LARGA;

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act +1, "%f", &(empl -> sueldo));

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act +1, "%d/%d/%d", &(empl -> fIngr.d), &(empl -> fIngr.m), &(empl -> fIngr.a));

    *act = '\0';
    act = strrchr(linea, '|');
    empl -> sexo = *(act +1);

    *act = '\0';
    act = strrchr(linea, '|');
    strcpy(empl -> apyn, act +1);

    *act = '\0';
    sscanf(linea, "%d", &(empl -> dni));

    return TODO_OK;
}

int empleadoTxtFABin (char* linea, void* reg) {

    Empleado* empl = reg;
    char* act = strchr(linea, '\n');

    if (act == NULL)
        return ERR_LINEA_LARGA;

    *act = '\0';
    act -= TAM_SUELDO;
    sscanf(act, "%f", &(empl -> sueldo));

    *act = '\0';
    act -= TAM_FECHA;
    sscanf(act, "%2d%2d%4d", &(empl -> fIngr.d), &(empl -> fIngr.m), &(empl -> fIngr.a));

    *act = '\0';
    act -= TAM_SEXO;
    empl -> sexo = *act;

    *act = '\0';
    act -= TAM_APYN;
    strcpy(empl -> apyn, act);

    *act = '\0';
    sscanf(linea, "%d", &(empl -> dni));

    return TODO_OK;
}

bool eFatalEmp (int cod) {

    switch (cod) {
        case ERR_LINEA_LARGA:
            return true;

        default:
            return false;
    }
}

int mostrarEmpleadosBin (const char* nomArchBin) {
    FILE* archBin = fopen(nomArchBin, "rb");

    if (!archBin)
    {
        return ERR_ARCHIVO;
    }

    Empleado empl;

    while (fread(&empl, sizeof(Empleado), 1, archBin) == 1)
    {
        printf("%d | %s | %c | %02d/%02d/%04d | %.2f\n",
               empl.dni, empl.apyn, empl.sexo,
               empl.fIngr.d, empl.fIngr.m, empl.fIngr.a,
               empl.sueldo);
    }

    fclose(archBin);

    return TODO_OK;
}
