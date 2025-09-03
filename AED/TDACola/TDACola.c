#include "./TDACola.h"
#include <string.h>

void crearCola(tCola *p) {
    p -> pri = TAM_COLA / 2;
    p -> ult = TAM_COLA / 2;
    p -> tDisp = TAM_COLA;
}

void vaciarCola(tCola *p) {
    p -> pri = TAM_COLA / 2;
    p -> ult = TAM_COLA / 2;
    p -> tDisp = TAM_COLA;
}

bool colaLlena(const tCola *p, unsigned cantB) {
    return p -> tDisp < (sizeof(unsigned int) + cantB);
}

bool colaVacia(const tCola *p) {
    return TAM_COLA == p -> tDisp;
}

bool ponerEnCola(tCola *p, const void *info, unsigned cantB) {

    unsigned int ini, fin;

    if (p -> tDisp < (sizeof(unsigned int) + cantB))
        return false; // o un LLENO

    p -> tDisp -= (sizeof(unsigned int) + cantB);

    ini = MIN(sizeof(unsigned int), TAM_COLA - p -> ult);
    fin = sizeof(unsigned int) - ini;

    if (ini > 0)
        memcpy(p -> cola + p -> ult, &cantB, ini); // Probar con ini = 0 si no falla el memcpy

    if (fin > 0)
        memcpy(p -> cola, ((char*) &cantB) + ini, fin);

    // p -> ult = (p -> ult + sizeof(unsigned int)) % TAM_COLA;
    p -> ult = fin > 0 ? fin : p -> ult + ini;


    ini = MIN(cantB, TAM_COLA - p -> ult);
    fin = cantB - ini;

    if (ini > 0)
        memcpy(p -> cola + p -> ult, info, ini); // Probar con ini = 0 si no falla el memcpy

    if (fin > 0)
        memcpy(p -> cola, ((char*) info) + ini, fin);

    // p -> ult = (p -> ult + cantB) % TAM_COLA;
    p -> ult = fin > 0 ? fin : p -> ult + ini;

    return true;
}

bool sacarDeCola(tCola *p, void *info, unsigned cantB) {

    unsigned int ini, fin, tamEnCola, tamMin;

    if (TAM_COLA == p -> tDisp)
        return false;

    ini = MIN(sizeof(unsigned int), TAM_COLA - p -> pri);
    fin = sizeof(unsigned int) - ini;

    if (ini > 0)
        memcpy(&tamEnCola, p -> cola + p -> pri, ini);

    if (fin > 0)
        memcpy(((char*) &tamEnCola) + ini, p -> cola, fin);

    // p -> pri = (p -> pri + sizeof(unsigned int)) % TAM_COLA;
    p -> pri = fin > 0 ? fin : p -> pri + ini;

    p -> tDisp += (sizeof(unsigned int) + tamEnCola);

    tamMin = MIN(tamEnCola, cantB);

    ini = MIN(tamMin, TAM_COLA - p -> pri);
    fin = tamMin - ini;

    if (ini > 0)
        memcpy(info, p -> cola + p -> pri, ini);

    if (fin > 0)
        memcpy(((char*) info) + ini, p -> cola, fin);

    // Para moverse en la cola, usar lo que dice la cola.
    // p -> pri = (p -> pri + tamEnCola) % TAM_COLA;
    p -> pri = fin > 0 ? fin : p -> pri + ini;

    return true;
}

bool verPriDeCola(const tCola *p, void *info, unsigned cantB) {

    unsigned int ini, fin, tamEnCola, tamMin, offset;

    if (TAM_COLA == p -> tDisp)
        return false;

    ini = MIN(sizeof(unsigned int), TAM_COLA - p -> pri);
    fin = sizeof(unsigned int) - ini;

    if (ini > 0)
        memcpy(&tamEnCola, p -> cola + p -> pri, ini);

    if (fin > 0)
        memcpy(((char*) &tamEnCola) + ini, p -> cola, fin);

    offset = fin > 0 ? fin : p -> pri + ini;

    tamMin = MIN(tamEnCola, cantB);

    ini = MIN(tamMin, TAM_COLA - offset);
    fin = tamMin - ini;

    if (ini > 0)
        memcpy(info, p -> cola + offset, ini);

    if (fin > 0)
        memcpy(((char*) info) + ini, p -> cola, fin);

    return true;
}
