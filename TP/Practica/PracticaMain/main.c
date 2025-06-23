#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "../TDAFecha/Fecha.h"

size_t longitudStr (const char* str);
bool esPalindromo (const char* str);
char aMayuscula (char c);

int main () {

    Fecha f1, f2;

    // char* diasSemana[] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo" };

    if (!fechaAsignar(&f1, 23, 6, 2025))
        printf("Fecha 1 invalida");

    if (!fechaAsignar(&f2, 2, 8, 2023))
        printf("Fecha invalida");

    // int dia = fechaDiaDeLaSemana(&f1);
    // char* nombreDia = diasSemana;

    int dia, mes, anio;

    fechaObtenerCampos(&f1, &dia, &mes, &anio);

    // printf("%02d/%02d/%4d", dia, mes, anio);

    printf("%d", fechaDiaDelAnio(&f1));

    // fechaSumarDias(&f1, 10);

    // fechaMostrar(&f1, mostrarFecha);

    return 0;
}

size_t longitudStr (const char* str) {

    const char* letraActual = str;

    while (*letraActual != '\0')
        letraActual++;

    return letraActual - str;
}

bool esPalindromo (const char* str) {

    const char* i1 = str;
    const char* i2 = str + longitudStr(str) -1;

    while (i1 < i2 && aMayuscula(*i1) == aMayuscula(*i2)) {
        i1++;
        i2--;
    }

    return i1 >= i2;
}

char aMayuscula (char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');

    return c;
}
