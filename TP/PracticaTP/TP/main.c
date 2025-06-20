#include <stdio.h>
#include <stdlib.h>
#include "./funciones.h"
#include "../TPString/string.h"

#define ARG_NOM_ARCH_ICC_GENERAL 1
#define ARG_NOM_ARCH_ITEMS_OBRA 2
#define ARG_NOM_ARCH_INDICES_UNIF 3

#define RUTA_TAM 254

/* TP.exe indices_icc_general_capitulos.csv Indices_items_obra.csv indices_unificado.dat */
int main (int argc, char* argv[]) {

    Vector vecIccGeneral, vecItemsObra;
    int cod;
    
    system("chcp 65001 > nul");

    cod = vectorCrear(&vecIccGeneral, sizeof(Registro));

    if (cod != TODO_OK)
        return cod;

    vectorCrear(&vecItemsObra, sizeof(Registro));

    cod = vectorCargarDeTxt(
        &vecIccGeneral,
        argv[ARG_NOM_ARCH_ICC_GENERAL],
        cargarEnRegistro,
        BUFFER_TAM
    );

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeTxt(
        &vecItemsObra,
        argv[ARG_NOM_ARCH_ITEMS_OBRA],
        cargarEnRegistro,
        BUFFER_TAM
    );

    if (cod != TODO_OK)
        return cod;

    corregirRegistros(&vecIccGeneral, corregirIccGeneral);
    corregirRegistros(&vecItemsObra, corregirItemsObra);

    cod = vectorUnir(&vecIccGeneral, &vecItemsObra);

    if (cod != TODO_OK)
        return cod;

    vectorDestruir(&vecItemsObra);

    cod = vectorOrdenar(&vecIccGeneral, INSERCION, compRegistrosPeriodoClasificador);

    if (cod != TODO_OK)
        return cod;


    calcularVariaciones(&vecIccGeneral);

    cod = cargarABinario(&vecIccGeneral, argv[ARG_NOM_ARCH_INDICES_UNIF]);

    if (cod != TODO_OK)
        return cod;

    vectorDestruir(&vecIccGeneral);


    /* Prueba para verificar que se hayan cargado bien los registros en el binario */

    /*
    char ruta[RUTA_TAM +1] = "../TP/";
    Vector vecPrueba;

    cod = vectorCrear(&vecPrueba, sizeof(RegistroExportado));

    if (cod != TODO_OK)
        return cod;

    concatenarString(ruta, argv[ARG_NOM_ARCH_INDICES_UNIF], RUTA_TAM);
    cod = vectorCargarDeBin(&vecPrueba, ruta);

    if (cod != TODO_OK)
        return cod;

    vectorMostrar(&vecPrueba, mostrarRegistroExportado);

    vectorDestruir(&vecPrueba);
    */

    return TODO_OK;
}