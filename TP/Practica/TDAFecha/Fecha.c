
#include "Fecha.h"

bool fechaAsignar (Fecha* f, int dia, int mes, int anio) {

    if (esFechaValida(dia, mes, anio)) {
        f -> dia = dia;
        f -> mes = mes;
        f -> anio = anio;

        return true;
    }

    return false;
}

void fechaSumarDias (Fecha* f, int dias) {

    size_t cantDMes;
    f -> dia += dias;

    cantDMes = cantidadDiasMes(f -> mes, f -> anio);

    while (f -> dia > cantDMes) {

        f -> dia -= cantDMes;
        f -> mes++;

        while (f -> mes > 12) {
            f -> mes = 1;
            f -> anio++;
        }

        cantDMes = cantidadDiasMes(f -> mes, f -> anio);
    }
}

void fechaRestarDias (Fecha* f, int dias) {

    size_t cantDMes;
    f -> dia -= dias;

    while (f -> dia < 1) {

        f -> mes--;

        while (f -> mes < 1) {
            f -> mes = 12;
            f -> anio--;
        }

        cantDMes = cantidadDiasMes(f -> mes, f -> anio);
        f -> dia += cantDMes;
    }

}

int fechaADias (Fecha* f) {

    int dias = f -> dia;
    int i;

    for (i = 1; i < f -> mes; i++)
        dias += cantidadDiasMes(i, f -> anio);

    for (i = ANIO_REF; i < f -> anio; i++)
        dias += esBisiesto(i) ? 366 : 365;
    
    return dias;
}

int fechaDiferenciaDias (Fecha* f1, Fecha* f2) {

    int f1EnDias = fechaADias(f1);
    int f2EnDias = fechaADias(f2);

    return f1EnDias - f2EnDias;
}

int fechaDiaDeLaSemana (Fecha* f) {

    Fecha ref = { DIA_REF, MES_REF, ANIO_REF };

    int dias = fechaDiferenciaDias(f, &ref);

    return dias % 7;
}

int fechaDiaDelAnio (Fecha* f) {

    size_t dias = 0;

    for (int i = 1; i < f -> mes; i++)
        dias += cantidadDiasMes(i, f -> anio);

    dias += f -> dia;

    return dias;
}

void fechaObtenerCampos (Fecha* f, int* dia, int* mes, int* anio) {
    *dia = f -> dia;
    *mes = f -> mes;
    *anio = f -> anio;
}

// Auxiliares

bool esFechaValida (int dia, int mes, int anio) {

    if (anio < ANIO_REF)
        return false;

    if (mes < 1 || mes > 12)
        return false;

    if (dia < 1 || dia > cantidadDiasMes(mes, anio))
        return false;

    return true;
}

size_t cantidadDiasMes (int mes, int anio) {

    int diasXMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (mes == 2 && esBisiesto(anio))
        return 29;
    else
        return diasXMes[mes];
}

bool esBisiesto (int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}