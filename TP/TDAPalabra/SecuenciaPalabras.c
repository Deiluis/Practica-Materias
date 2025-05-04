#include "SecuenciaPalabras.h"

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, const char* cad) {
    sec -> cur = (char*) cad; // Casteo el const char* a char* para que el compilador no de warning.
    sec -> finSec = false;
}

bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal) {

    // Tambien puedo usar *(sec -> cur) ya que el valor de '\0' es 0, entonces se toma como falso.
    while (*(sec -> cur) != '\0' && !esLetra(*(sec -> cur))) {
        sec -> cur++;
    }

    if (*(sec -> cur) == '\0') {
        sec -> finSec = true;
        return false;
    }

    char *iPal = pal -> vPal;

    do {
        *iPal = *(sec -> cur);
        sec -> cur++;
        iPal++;
    } while (*(sec -> cur) != '\0' && esLetra(*(sec -> cur)));

    *iPal = '\0';

    return true;
}

void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, const Palabra* pal) {
    const char *iPal = pal -> vPal;

    while (*iPal != '\0') {
        *(sec -> cur) = *iPal;
        iPal++;
        sec -> cur++;
    }
}

void secuenciaPalabrasEscribirCaracter(SecuenciaPalabras* sec, const char c) {
    *(sec -> cur) = c;
    sec -> cur++;
}

bool secuenciaPalabrasFin(const SecuenciaPalabras* sec) {
    return sec -> finSec;
}

void secuenciaPalabrasCerrar(SecuenciaPalabras* sec) {
    *(sec -> cur) = '\0';
}
