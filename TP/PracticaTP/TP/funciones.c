#include "./funciones.h"
#include "../TPString/string.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void corregirFecha (char* fecha);
void desencriptarIccGeneral (char* str);
void desencriptarItemsObra (char* str);
void normalizarItemsObra (char* str);
float variacionANMeses (Vector* v, Registro* reg, size_t meses);

bool esLetra (char c);
char aMayuscula(char c);
int compararFecha (char* fecha1, char* fecha2);
int compRegistrosPeriodoNGeneralAb (const void* regA, const void* regB);
void copiarReg (Vector* v, RegistroExportado* regExp, Registro* reg, const char* tVariable, FILE* archBin);


int cargarEnRegistro (void* reg, char* buffer) {
    Registro* r = reg;
    char* act;

    removerCharEnString(buffer, '\"');

    act = buscarEnStringReversa(buffer, '\n');

    if (act == NULL)
        return ERR_BUFFER_CORTO;

    *act = '\0';
    act = buscarEnStringReversa(buffer, ';');

    sscanf(act +1, "%s", r -> indiceICC);

    *act = '\0';
    act = buscarEnStringReversa(buffer, ';');

    sscanf(act +1, "%s", r -> nGeneralAberturas);

    *act = '\0';

    sscanf(buffer, "%s", r -> periodo);

    return TODO_OK;
}

void mostrarRegistro (const void* reg) {
    const Registro* r = reg;

    printf(
        "%s;%s;%s;%s;%s;%s\n",
        r -> periodo, r -> nGeneralAberturas, r -> indiceICC, r -> clasificador, r -> vMensual,  r -> vAnual
    );
}

void mostrarRegistroExportado (const void* reg) {
    const RegistroExportado* r = reg;

    printf(
        "%s;%s;%s;%s;%s\n",
        r -> periodo, r -> clasificador, r -> nGeneralAberturas, r -> tipoVariable, r -> valor
    );
}

void corregirRegistros (Vector* v, Crr corrector) {

    Registro reg;

    /* Elimina la cabecera */
    vectorEliminarDePos(v, 0);

    vectorPosicionarCursor(v, 0, INICIO);

    while (vectorLeer(v, &reg)) {
        corrector(&reg);

        vectorPosicionarCursor(v, -1, ACTUAL);
        vectorEscribir(v, &reg);
    }
}

void corregirIccGeneral (Registro* reg) {

    bool esNGeneral;

    corregirFecha(reg -> periodo);

    reemplazarCharEnString(reg -> indiceICC, ',', '.');

    desencriptarIccGeneral(reg -> nGeneralAberturas);

    reemplazarCharEnString(reg -> nGeneralAberturas, '_', ' ');
    *(reg -> nGeneralAberturas) = aMayuscula(*(reg -> nGeneralAberturas));

    esNGeneral = compararString(reg -> nGeneralAberturas, "Nivel general") == 0;

    copiarString(
        reg -> clasificador,
        esNGeneral ? "Nivel general" : "Capítulos",
        CLASIFICADOR_TAM -1
    );

}

void corregirItemsObra (Registro* reg) {
    corregirFecha(reg -> periodo);

    reemplazarCharEnString(reg -> indiceICC, ',', '.');

    desencriptarItemsObra(reg -> nGeneralAberturas);

    normalizarItemsObra(reg -> nGeneralAberturas);

    copiarString(reg -> clasificador, "Ítems", CLASIFICADOR_TAM -1);
}

void corregirFecha (char* fecha) {
    int dia, mes, anio;

    sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio);
    sprintf(fecha, "%4d-%02d-%02d", anio, mes, dia);
}

void desencriptarIccGeneral (char* str) {

    char* letraActual = str;
    int pos;

    while (*letraActual != '\0') {
        if (esLetra(*letraActual)) {

            pos = (letraActual - str);

            if (pos % 2 == 0)
                *letraActual += 4;
            else
                *letraActual += 2;


            if (*letraActual > 'z')
                *letraActual -= ('z' - 'a' +1);
        }

        letraActual++;
    }
}

void desencriptarItemsObra (char* str) {

    char* letraActual = str;
    const char vEnc[] = "@8310$7|59";
    const char vDes[] = "abeiostlmn";
    int pos;
    char* dir;

    while (*letraActual != '\0') {

        dir = buscarEnString(vEnc, *letraActual);

        if (dir) {
            pos = dir - vEnc;
            *letraActual = *(vDes + pos);
        }



        letraActual++;
    }
}

void normalizarItemsObra (char* str) {

    char* letraActual = str;
    bool primerGuionBajo = false;
    size_t longSeg;

    while (!primerGuionBajo && *letraActual != '\0') {

        if (*letraActual == '_') {
            primerGuionBajo = true;
            *(letraActual +1) = aMayuscula(*(letraActual +1));
            longSeg = longitudString(letraActual +1);
            memmove(str, letraActual +1, longSeg +1);
        }
        else
            letraActual++;
    }

    reemplazarCharEnString(str, '_', ' ');
}

int compRegistrosPeriodoClasificador (const void* regA, const void* regB) {

    Registro* rA = (Registro*) regA;
    Registro* rB = (Registro*) regB;
    Vector diccionario;
    int compFecha, posA, posB;

    compFecha = compararFecha(rA -> periodo, rB -> periodo);

    if (compFecha != 0)
        return compFecha;

    /* Todo esto de acá abajo no hace falta realmente, por como estan hechos los archivos, al ordenar por periodo, el clasificador queda ordenado */

    vectorCrear(&diccionario, CLASIFICADOR_TAM);

    vectorEscribir(&diccionario, "Nivel general");
    vectorEscribir(&diccionario, "Capítulos");
    vectorEscribir(&diccionario, "Ítems");

    posA = vectorDesordBuscar(&diccionario, rA -> clasificador, compararString);
    posB = vectorDesordBuscar(&diccionario, rB -> clasificador, compararString);

    vectorDestruir(&diccionario);

    return posA - posB;
}

void calcularVariaciones (Vector* v) {

    float vMensual, vAnual;
    Registro reg;

    vectorPosicionarCursor(v, 0, INICIO);

    while (vectorLeer(v, &reg)) {
        vMensual = variacionANMeses(v, &reg, 1);
        vAnual = variacionANMeses(v, &reg, 12);

        if (vMensual != 0)
            sprintf(reg.vMensual, "%.2f", vMensual);
        else
            copiarString(reg.vMensual, "NA", V_MENSUAL_TAM -1);

        if (vAnual != 0)
            sprintf(reg.vAnual, "%.2f", vAnual);
        else
            copiarString(reg.vAnual, "NA", V_ANUAL_TAM -1);

        vectorPosicionarCursor(v, -1, ACTUAL);
        vectorEscribir(v, &reg);
    }
}

float variacionANMeses (Vector* v, Registro* reg, size_t meses) {

    int dia, mes, anio, pos;
    float variacion = 0;
    Registro elem;

    sscanf(reg -> periodo, "%d-%d-%d", &anio, &mes, &dia);

    while (meses >= 12) {
        anio--;
        meses -= 12;
    }

    mes -= meses;

    if (mes == 0) {
        anio--;
        mes = 12;
    }

    sprintf(elem.periodo, "%4d-%02d-%02d", anio, mes, dia);
    copiarString(elem.nGeneralAberturas, reg -> nGeneralAberturas, N_GENERAL_ABERTURAS_TAM -1);

    /* Hacer con binary search */
    pos = vectorDesordBuscar(v, &elem, compRegistrosPeriodoNGeneralAb);

    if (pos != -1)
        variacion = (atof(reg -> indiceICC) / atof(elem.indiceICC) -1) * 100;

    return variacion;
}

int cargarABinario (Vector* v, const char* nomArchBin) {

    FILE* archBin = fopen(nomArchBin, "wb");
    Registro reg;
    RegistroExportado regExp;

    if (!archBin)
        return ERR_ARCHIVO;

    copiarReg(v, &regExp, &reg, "indice_icc", archBin);
    copiarReg(v, &regExp, &reg, "var_mensual", archBin);
    copiarReg(v, &regExp, &reg, "var_interanual", archBin);

    fclose(archBin);

    return TODO_OK;
}


bool esLetra (char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char aMayuscula(char c) {
    if (c >= 'a' && c <= 'z')
        return c -= ('a' - 'A');

    return c;
}

int compararFecha (char* fecha1, char* fecha2) {

    int dia, mes, anio, f1, f2;

    sscanf(fecha1, "%d-%d-%d", &anio, &mes, &dia);
    f1 = anio * 10000 + mes * 100 + dia;

    sscanf(fecha2, "%d-%d-%d", &anio, &mes, &dia);
    f2 = anio * 10000 + mes * 100 + dia;

    return f1 - f2;
}

int compRegistrosPeriodoNGeneralAb (const void* regA, const void* regB) {

    Registro* rA = (Registro*) regA;
    Registro* rB = (Registro*) regB;

    int compFecha = compararFecha(rA -> periodo, rB -> periodo);

    if (compFecha != 0)
        return compFecha;

    return compararString(rA -> nGeneralAberturas, rB -> nGeneralAberturas);
}

void copiarReg (Vector* v, RegistroExportado* regExp, Registro* reg, const char* tVariable, FILE* archBin) {

    char valor[VALOR_TAM];

    vectorPosicionarCursor(v, 0, INICIO);

    while (vectorLeer(v, reg)) {

        /* Esto podría hacerse mejor */

        if (compararString(tVariable, "indice_icc") == 0)
            copiarString(valor, reg -> indiceICC, VALOR_TAM);
        else {
            if (compararString(tVariable, "var_mensual") == 0)
                copiarString(valor, reg -> vMensual, VALOR_TAM);
            else
                copiarString(valor, reg -> vAnual, VALOR_TAM);
        }


        copiarString(regExp -> periodo, reg -> periodo, PERIODO_TAM);
        copiarString(regExp -> clasificador, reg -> clasificador, CLASIFICADOR_TAM);
        copiarString(regExp -> nGeneralAberturas, reg -> nGeneralAberturas, N_GENERAL_ABERTURAS_TAM);
        copiarString(regExp -> tipoVariable, tVariable, T_VARIABLE_TAM);
        copiarString(regExp -> valor, valor, VALOR_TAM);

        fwrite(regExp, sizeof(RegistroExportado), 1, archBin);
    }
}
