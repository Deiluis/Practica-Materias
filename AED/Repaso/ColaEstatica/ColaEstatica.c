#include "./ColaEstatica.h"
#include <string.h>

void crearCola(tCola* c) {
    c -> pri = TAM_COLA / 2;
    c -> ult = TAM_COLA / 2;
    c -> tDisp = TAM_COLA;
}

bool ponerEnCola(tCola* c, const void* info, unsigned tamInfo) {

    unsigned ini, fin;

    if (c -> tDisp < tamInfo + sizeof(unsigned))
        return false;

    c -> tDisp -= tamInfo + sizeof(unsigned);

    ini = MIN(TAM_COLA - c -> ult, sizeof(unsigned));
    fin = sizeof(unsigned) - ini;

    if (ini > 0)
        memcpy(c -> cola + c -> ult, &tamInfo, ini);

    if (fin > 0)
        memcpy(c -> cola, ((char*) &tamInfo) + ini, fin);

    c -> ult = fin > 0 ? fin : c -> ult + ini;

    ini = MIN(TAM_COLA - c -> ult, tamInfo);
    fin = tamInfo - ini;

    if (ini > 0)
        memcpy(c -> cola + c -> ult, info, ini);

    if (fin > 0)
        memcpy(c -> cola, ((char*) &info) + ini, fin);

    c -> ult = fin > 0 ? fin : c -> ult + ini;

    return true;
}

bool verPriDeCola(const tCola* c, void* info, unsigned tamInfo) {

    unsigned ini, fin, offset, tamMin, tamEnCola;

    if (c -> tDisp == TAM_COLA)
        return false;

    ini = MIN(TAM_COLA - c -> pri, sizeof(unsigned));
    fin = sizeof(unsigned) - ini;

    if (ini > 0)
        memcpy(&tamEnCola, c -> cola + c -> pri, ini);

    if (fin > 0)
        memcpy(((char*) &tamEnCola) + ini, c -> cola, fin);

    offset = fin > 0 ? fin : c -> pri + ini;
    tamMin = MIN(tamEnCola, tamInfo);

    ini = MIN(TAM_COLA - offset, tamMin);
    fin = tamMin - ini;

    if (ini > 0)
        memcpy(info, c -> cola + offset, ini);

    if (fin > 0)
        memcpy(((char*) info) + ini, c -> cola, fin);

    return true;
}

bool sacarDeCola(tCola* c, void* info, unsigned tamInfo) {

    unsigned ini, fin, tamMin, tamEnCola;

    if (c -> tDisp == TAM_COLA)
        return false;

    ini = MIN(TAM_COLA - c -> pri, sizeof(unsigned));
    fin = sizeof(unsigned) - ini;

    if (ini > 0)
        memcpy(&tamEnCola, c -> cola + c -> pri, ini);

    if (fin > 0)
        memcpy(((char*) &tamEnCola) + ini, c -> cola, fin);

    c -> pri = fin > 0 ? fin : c -> pri + ini;
    c -> tDisp += tamEnCola + sizeof(unsigned);
    tamMin = MIN(tamEnCola, tamInfo);

    ini = MIN(TAM_COLA - c -> pri, tamMin);
    fin = tamMin - ini;

    if (ini > 0)
        memcpy(info, c -> cola + c -> pri, ini);

    if (fin > 0)
        memcpy(((char*) info) + ini, c -> cola, fin);

    c -> pri = fin > 0 ? fin : c -> pri + ini;

    return true;
}

void vaciarCola(tCola* c) {
    c -> pri = TAM_COLA / 2;
    c -> ult = TAM_COLA / 2;
    c -> tDisp = TAM_COLA;
}

bool colaVacia(const tCola* c) {
    return c -> tDisp == TAM_COLA;
}

bool colaLlena(const tCola* c, unsigned tamInfo) {
    return c -> tDisp < tamInfo + sizeof(unsigned);
}
