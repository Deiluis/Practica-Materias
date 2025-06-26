#include "./SecuenciaPalabras.h"

void secuenciaPalabrasCargar (SecuenciaPalabras* sec, const char* cad) {
    sec -> cur = (char*) cad;
    sec -> fin = false;
}

bool secuenciaPalabrasLeer (SecuenciaPalabras* sec, Palabra* pal) {

    char* iPal = pal -> vPal;

    while (*sec -> cur != '\0' && !esLetra(*sec -> cur))
        sec -> cur++;

    if (*sec -> cur == '\0') {
        sec -> fin = true;
        return false;
    }

    do {
        *iPal = *sec -> cur;
        sec -> cur++;
        iPal++;
    } while (*sec -> cur != '\0' && esLetra(*sec -> cur));

    *iPal = '\0';

    return true;
}

bool secuenciaPalabrasFin (SecuenciaPalabras* sec) {
    return sec -> fin;
}

bool esLetra (char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
