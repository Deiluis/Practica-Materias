#include "SecuenciaPalabra.h"

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, const char* cad) {
    sec -> cur = (char*) cad;
    sec -> finSec = false;
}

bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal) {

    char* iPal = pal -> vPal;

    while (*sec -> cur != '\0' && !esLetra(*sec -> cur))
        sec -> cur++;

    if (*sec -> cur == '\0') {
        sec -> finSec = true;
        return false;
    }

    do {
        *iPal = *sec -> cur;
        iPal++;
        sec -> cur++;
    } while (*sec -> cur != '\0' && esLetra(*sec -> cur));

    *iPal = '\0';

    return true;
}

bool secuenciaPalabrasFin(SecuenciaPalabras* sec) {
    return sec -> finSec;
}

void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, Palabra* pal) {

    char* iPal = pal -> vPal;

    while (*iPal != '\0') {
        *sec -> cur = *iPal;
        sec -> cur++;
        iPal++;
    }
}

void secuenciaPalabrasEscribirCaracter(SecuenciaPalabras* sec, char c) {
    *sec -> cur = c;
    sec -> cur++;
}

void secuenciaPalabrasCerrar(SecuenciaPalabras* sec) {
    *sec -> cur = '\0';
}
