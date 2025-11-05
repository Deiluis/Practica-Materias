#include "./PilaEstatica.h"
#include "string.h"

void crearPila(tPila* p) {
    p -> tope = 0;
}

bool apilar(tPila* p, const void* info, unsigned tamInfo) {

    if (tamInfo + sizeof(unsigned) + p -> tope > TAM_PILA)
        return false;

    memcpy(p -> pila + p -> tope, info, tamInfo);
    p -> tope += tamInfo;

    memcpy(p -> pila + p -> tope, &tamInfo, sizeof(unsigned));
    p -> tope += sizeof(unsigned);

    return true;
}

bool verTope(const tPila* p, void* info, unsigned tamInfo) {

    unsigned pos = p -> tope;
    unsigned tamEnPila;

    if (p -> tope == 0)
        return false;

    pos -= sizeof(unsigned);
    memcpy(&tamEnPila, p -> pila + pos, sizeof(unsigned));

    pos -= tamEnPila;
    memcpy(info, p -> pila + pos, MIN(tamEnPila, tamInfo));

    return true;
}

bool desapilar(tPila* p, void* info, unsigned tamInfo) {

    unsigned tamEnPila;

    if (p -> tope == 0)
        return false;

    p -> tope -= sizeof(unsigned);
    memcpy(&tamEnPila, p -> pila + p -> tope, sizeof(unsigned));

    p -> tope -= tamEnPila;
    memcpy(info, p -> pila + p -> tope, MIN(tamEnPila, tamInfo));

    return true;
}

void vaciarPila(tPila* p) {
    p -> tope = 0;
}

bool pilaVacia(const tPila* p) {
    return p -> tope == 0;
}

bool pilaLlena(const tPila* p, unsigned tamInfo) {
    return tamInfo + sizeof(unsigned) + p -> tope > TAM_PILA;
}
