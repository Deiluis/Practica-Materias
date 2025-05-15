#include <stdbool.h>
#include <stdio.h>

#define TAM 100

void normalizar (char* strDest, const char* strOrig);
bool esLetra (char caracter);
char aMinuscula (char letra);
char aMayuscula (char letra);
bool esMinuscula (char letra);
bool esMayuscula (char letra);

int main () {

    char* strOrig = "cadEna	a  NorMALizar";
    char strDest[TAM];

    normalizar(strDest, strOrig);
    printf("%s", strDest);

    return 0;
}

void normalizar (char* strDest, const char* strOrig) {

    const char* letraOrigActual = strOrig;
    char* letraDestActual = strDest;
    bool primerLetra, primerPalabra = true, finSec = false;

    while (!finSec) {

        primerLetra = true;

        while (*letraOrigActual != '\0' && esLetra(*letraOrigActual)) {

            if (primerLetra) {

                if (!primerPalabra) {
                    *letraDestActual = ' ';
                    letraDestActual++;
                } else
                    primerPalabra = false;

                *letraDestActual = aMayuscula(*letraOrigActual);
                primerLetra = false;
            } else
                *letraDestActual = aMinuscula(*letraOrigActual);

            letraDestActual++;
            letraOrigActual++;
        }

        if (*letraOrigActual == '\0')
            finSec = true;
        else
            letraOrigActual++;
    }

    *letraDestActual = '\0';
}

bool esLetra (char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool esMayuscula (char letra) {
    return letra >= 'A' && letra <= 'Z';
}

bool esMinuscula (char letra) {
    return letra >= 'a' && letra <= 'z';
}

char aMayuscula (char letra) {
    if (esMinuscula(letra))
        return letra - ('a' - 'A');

    return letra;
}

char aMinuscula (char letra) {
    if (esMayuscula(letra))
        return letra + ('a' - 'A');

    return letra;
}
