#include "Pila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool redimensionarPila (tPila* pila, int operacion, size_t tamElem);

bool crearPila (tPila* pila) {

    void* cont = malloc(CAP_INI);

    if (!cont)
        return false;

    pila -> cont = cont;
    pila -> tope = 0;
    pila -> cap = CAP_INI;

    return true;
}

bool apilar (tPila* pila, const void* elem, size_t tamElem) {

    if ((pila -> tope + tamElem + sizeof(unsigned int)) >= pila -> cap) {
        if (!redimensionarPila(pila, INCREMENTAR, tamElem))
            return false;
    }

    memcpy(((char*) pila -> cont) + pila -> tope, elem, tamElem);
    pila -> tope += tamElem;
    memcpy(((char*) pila -> cont) + pila -> tope, &tamElem, sizeof(unsigned int));
    pila -> tope += sizeof(unsigned int);

    return true;
}

bool verTope (tPila* pila, void* elem, size_t tamElem) {

    unsigned int tamEnPila;

    if (pila -> tope == 0)
        return false;

    memcpy(
        &tamEnPila,
        ((char*) pila -> cont) + pila -> tope - sizeof(unsigned int),
        sizeof(unsigned int)
    );
    memcpy(
        elem,
        ((char*) pila -> cont) + pila -> tope - sizeof(unsigned int) - tamEnPila,
        MIN(tamEnPila, tamElem)
    );

    return true;
}

bool desapilar (tPila* pila, void* elem, size_t tamElem) {

    unsigned int tamEnPila;

    if (pila -> tope == 0)
        return false;

    pila -> tope -= sizeof(unsigned int);
    memcpy(&tamEnPila, ((char*) pila -> cont) + pila -> tope, sizeof(unsigned int));
    pila -> tope -= tamEnPila;
    memcpy(elem, ((char*) pila -> cont) + pila -> tope, MIN(tamEnPila, tamElem));

    if (pila -> tope != 0 && (float) pila -> tope / pila -> cap <= FACTOR_OCUP)
        redimensionarPila(pila, DECREMENTAR, 0);

    return true;
}

void vaciarPila (tPila* pila) {
    pila -> tope = 0;
}

bool pilaVacia (const tPila* pila) {
    return pila -> tope == 0;
}

bool pilaLlena (const tPila* pila, size_t tamElem) {
    return (pila -> tope + tamElem + sizeof(unsigned int)) > pila -> cap;
}

void destruirPila (tPila* pila) {
    free(pila -> cont);

    pila -> cont = NULL;
    pila -> tope = 0;
    pila -> cap = 0;
}

bool redimensionarPila (tPila* pila, int operacion, size_t tamElem) {

    /*
     * La redimensión podría resolverse de dos formas:
     * 1. Solicitando la cantidad de espacio necesaria para almacenar al elemento a añadir, sin importar el espacio libre que ya exista.
     * 2. Tomando el espacio libre que ya existe, solo se solicita el espacio restante para poder almacenar el elemento, quedando sin espacio libre.
     * En este caso, elegimos la opción 1, la cual permitiría seguir añadiendo elementos en el espacio libre sobrante sin necesidad de otro realloc.
    */
    size_t nuevaCap = operacion == INCREMENTAR
    ? pila -> tope + tamElem + sizeof(unsigned int)
    : MAX(CAP_INI, pila -> cap * FACTOR_DECR);

    void* nuevoCont = realloc(pila -> cont, nuevaCap);

    if (!nuevoCont)
        return false;

    printf("Redimension de %Iu a %Iu\n", pila -> cap, nuevaCap);

    pila -> cont = nuevoCont;
    pila -> cap = nuevaCap;

    return true;
}
