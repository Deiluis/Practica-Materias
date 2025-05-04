#include <stdio.h>
#include <stdlib.h>

#include "../TDAPalabra/SecuenciaPalabras.h"

char* normalizar (char* cadDest, const char* cadOrig);

int main()
{
    char cadOrig[] = "#$%cAdeNa&/(a)&//%$#$=)(NOrmALIZaR";
    char cadDest[101];

    normalizar(cadDest, cadOrig);
    puts(cadDest);

    return 0;
}

char* normalizar (char* cadDest, const char* cadOrig) {

    SecuenciaPalabras secL, secE;
    Palabra pal;

    secuenciaPalabrasCrear(&secL, cadOrig);
    secuenciaPalabrasCrear(&secE, cadDest);
    secuenciaPalabrasLeer(&secL, &pal);

    while (!secuenciaPalabrasFin(&secL)) {
        palabraMostrar(&pal);
        palabraATitulo(&pal);
        secuenciaPalabrasEscribir(&secE, &pal);

        if (secuenciaPalabrasLeer(&secL, &pal))
           secuenciaPalabrasEscribirCaracter(&secE, ' ');
    }

    secuenciaPalabrasCerrar(&secE);

    return cadDest;
}
