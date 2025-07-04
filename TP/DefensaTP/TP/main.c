#include <stdio.h>
#include <stdlib.h>
#include "./funciones.h"
#include "../TPString/string.h"
#include "../TPPalabra/SecuenciaPalabra.h"

#define ARG_NOM_ARCH_ICC_GENERAL 1
#define ARG_NOM_ARCH_ITEMS_OBRA 2
#define ARG_NOM_ARCH_INDICES_UNIF 3

#define RUTA_TAM 254

/*
 * Nota:
 * Hay cosas duras en la vida, desaprobar un parcial, ver como Boca pierde la septima,
   o tener que usar comentarios multilinea cuando solo quiero comentar una línea.
 * Atte: Los predicadores de Linux.
*/

/*
 * Nota 2:
 * Tenemos al menos 6 chistes más sobre comentarios multilinea pero no queremos ocupar más espacio en el main.
 * Atte: Los predicadores de Linux (de nuevo).
*/

/*
 * Nota 3 (post defensa):
 * Traté muy mal a los comentarios multilinea, hay cosas peores, como que no funcione bien el left ctrl en el teclado.
 * Atte: Luis Conforti
*/

/*
 * Argumentos a main:
 * TP.exe
 * ../TP/archivos/indices_icc_general_capitulos.csv
 * ../TP/archivos/Indice_items_obra.csv
 * archivos/indices_unificado.dat
*/
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

    corregirRegistros(&vecIccGeneral, corregirIccGeneralDef);
    corregirRegistros(&vecItemsObra, corregirItemsObraDef);

    vectorMostrar(&vecIccGeneral, mostrarRegistro);
    vectorMostrar(&vecItemsObra, mostrarRegistro);

    vectorDestruir(&vecIccGeneral);
    vectorDestruir(&vecItemsObra);

    return TODO_OK;
}
