#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include <stdbool.h>
#include <stddef.h>

#define ANIO_REF 1600
#define MES_REF 1
#define DIA_REF 3

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

// Primitivas

bool fechaAsignar (Fecha* f, int dia, int mes, int anio);
void fechaSumarDias (Fecha* f, int dias);
void fechaRestarDias (Fecha* f, int dias);
int fechaDiferenciaDias (Fecha* f1, Fecha* f2);
int fechaADias (Fecha* f);
int fechaDiaDeLaSemana (Fecha* f);
int fechaDiaDelAnio (Fecha* f);
void fechaObtenerCampos (Fecha* f, int* dia, int* mes, int* anio);

// Auxiliares

bool esFechaValida (int dia, int mes, int anio);
size_t cantidadDiasMes (int mes, int anio);
bool esBisiesto (int anio);

#endif // FECHA_H_INCLUDED
