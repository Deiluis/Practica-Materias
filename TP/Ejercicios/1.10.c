#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#define TAM 80

void desofuscar (char* dest, const char* orig);
int buscarCaracter (const char* str, char c);
size_t longitudStr (const char* str);
bool esLetra (char caracter);
char aMinuscula (char letra);
char aMayuscula (char letra);
bool esMinuscula (char letra);
bool esMayuscula (char letra);

int main () {

    char* ofuscada = "Nj qemh v ljs kraenkqbres; lj oqe qemh es oqevorme sgn ellhs --Istqt Asdmgj";
    char clara[TAM];

    desofuscar(clara, ofuscada);

    printf("%s\n", ofuscada);
    printf("%s\n", clara);

    return 0;
}

void desofuscar (char* dest, const char* orig) {

    const char* letraOrigActual = orig;
    const char* arrOfuscacion = "abcdghijkoqtuv";
    char *letraDestActual = dest, *palabraActual;
    bool primerPalabra = true, primerLetra, finSec = false;
    int pos, posEnPalabra;
    size_t longArr = longitudStr(arrOfuscacion);

    while (!finSec) {

        palabraActual = (char*) letraOrigActual;
        primerLetra = true;

        while (*letraOrigActual != '\0' && esLetra(*letraOrigActual)) {

            if (primerLetra) {
                primerLetra = false;

                if (!primerPalabra) {
                    *letraDestActual = ' ';
                    letraDestActual++;
                } else
                    primerPalabra = false;
            }

            pos = buscarCaracter(arrOfuscacion, *letraOrigActual);

            if (pos != -1) {
                posEnPalabra = letraOrigActual - palabraActual +1;
                pos += posEnPalabra;

                // Acomoda la posición para obtener en el array de ofuscación
                while (pos >= longArr)
                    pos -= longArr;

                *letraDestActual = *(arrOfuscacion + pos);

            } else
                *letraDestActual = *letraOrigActual;

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

int buscarCaracter (const char* str, char c) {
    int pos = -1;
    char* cActual = (char*) str;

    while (pos == -1 && *cActual != '\0') {
        if (*cActual == c)
            pos = cActual - str;
        else
            cActual++;
    }

    return pos;
}

size_t longitudStr (const char* str) {
    char* strP = (char*) str;

    while (*strP != '\0')
        strP++;

    return strP - str;
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
