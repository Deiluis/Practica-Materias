#include "TDAPila.h"
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

void crearPila(tPila* pila) {
    pila -> tope = TAM_PILA;
}

int apilar(tPila* pila, const void* elem, unsigned int tamElem) {

    if (pila -> tope < (tamElem + sizeof(unsigned int)))
        return LLENO;

    pila -> tope -= tamElem;
    memcpy(pila -> pila + pila -> tope, elem, tamElem);
    pila -> tope -= sizeof(unsigned int);
    memcpy(pila -> pila + pila -> tope, &tamElem, sizeof(unsigned int));

    return TODO_OK;
}

int verTope(const tPila* pila, void* elem, unsigned int tamElem) {

    unsigned int tamEnPila;

    if (pila -> tope == TAM_PILA)
        return VACIO;

    memcpy(&tamEnPila, pila -> pila + pila -> tope, sizeof(unsigned int));
    // Va el minimo entre los dos para que contemple todos los largos del dato donde se guarda.
    memcpy(elem, pila -> pila + pila -> tope + sizeof(unsigned int), MIN(tamElem, tamEnPila));

    return TODO_OK;
}

int desapilar(tPila* pila, void* elem, unsigned int tamElem) {

    unsigned int tamEnPila;

    if (pila -> tope == TAM_PILA)
        return VACIO;

    memcpy(&tamEnPila, pila -> pila + pila -> tope, sizeof(unsigned int));
    pila -> tope += sizeof(unsigned int);
    // Va el minimo entre los dos para que contemple todos los largos del dato donde se guarda.
    memcpy(elem, pila -> pila + pila -> tope, MIN(tamElem, tamEnPila));
    // Se corre el tama�o que ocupa en la pila, no importa la cantidad de bytes que se devuelvan.
    pila -> tope += tamEnPila;

    return TODO_OK;
}

void vaciarPila(tPila* pila) {
    pila -> tope = TAM_PILA;
}

int pilaVacia(const tPila* pila) {

    if (pila -> tope == TAM_PILA)
        return VACIO;

    return NO_VACIO;
}

int pilaLlena (const tPila* pila, unsigned int tamElem) {

    if (pila -> tope < (tamElem + sizeof(unsigned int)))
        return LLENO;

    return NO_LLENO;
}

