#include "TDAPila.h"
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

void crearPila(tPila* pila) {
    pila -> tope = TAM_PILA;
}

int apilar(tPila* pila, const void* elem, size_t tamElem) {

    if (pila -> tope < (tamElem + sizeof(size_t)))
        return LLENO;

    pila -> tope -= tamElem;
    memcpy(pila -> pila + pila -> tope, elem, tamElem);
    pila -> tope -= sizeof(size_t);
    memcpy(pila -> pila + pila -> tope, &tamElem, sizeof(size_t));

    return TODO_OK;
}

int verTope(const tPila* pila, void* elem, size_t tamElem) {

    size_t tamEnPila;

    if (pila -> tope == TAM_PILA)
        return VACIO;

    memcpy(&tamEnPila, pila -> pila + pila -> tope, sizeof(size_t));
    // Va el minimo entre los dos para que contemple todos los largos del dato donde se guarda.
    memcpy(elem, pila -> pila + pila -> tope + sizeof(size_t), MIN(tamElem, tamEnPila));

    return TODO_OK;
}

int desapilar(tPila* pila, void* elem, size_t tamElem) {

    size_t tamEnPila;

    if (pila -> tope == TAM_PILA)
        return VACIO;

    memcpy(&tamEnPila, pila -> pila + pila -> tope, sizeof(size_t));
    pila -> tope += sizeof(size_t);
    // Va el minimo entre los dos para que contemple todos los largos del dato donde se guarda.
    memcpy(elem, pila -> pila + pila -> tope, MIN(tamElem, tamEnPila));
    // Se corre el tamaño que ocupa en la pila, no importa la cantidad de bytes que se devuelvan.
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

int pilaLlena (const tPila* pila, size_t tamElem) {

    if (pila -> tope < (tamElem + sizeof(size_t)))
        return LLENO;

    return NO_LLENO;
}

