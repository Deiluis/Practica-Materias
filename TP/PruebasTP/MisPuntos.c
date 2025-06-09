#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define bool int
#define false 0
#define true 1

typedef int (*Cmp) (void* a, void* b);

char* normalizar (char* str);
char* desencriptar (char* str, char* v_enc, char* v_des);
int buscarEnVector (void* vec, size_t cantElem, size_t tamElem, void* elem, Cmp cmp);
int cmpChar (void* a, void* b);
int esMayuscula (char letra);
int esMinuscula (char letra);
char aMayuscula (char letra);
char aMinuscula (char letra);
size_t longitudLiteral (const char* str);

int main()
{
    char str[] = "1_50v1513970_d3_713rr@$";
    char v_enc[] = "@8310$7|59";
    char v_des[] = "abeiostlmn";

    printf("Antes de desencriptar: %s\n", str);
    desencriptar(str, v_enc, v_des);
    printf("Desencriptado: %s\n", str);

    printf("\n");

    printf("Antes de normalizar: %s\n", str);
    normalizar(str);
    printf("Normalizado: %s\n", str);

    return 0;
}

char* normalizar (char* str) {

    char* letraActual = str;
    bool guionEncontrado = false;

    while (*letraActual != '\0') {

        if (*letraActual == '_') {

            if (!guionEncontrado) {

                *(letraActual +1) = aMayuscula(*(letraActual +1));
                memmove(str, letraActual +1, sizeof(char) * (longitudLiteral(str) +1));

                letraActual = str;
                guionEncontrado = true;
            }
            else
                *letraActual = ' ';
        }

        letraActual++;
    }

    return str;
}

char* desencriptar (char* str, char* v_enc, char* v_des) {

    char* letraActual = str;
    int pos;

    while (*letraActual != '\0') {

        pos = buscarEnVector(
            v_enc,
            longitudLiteral(v_enc) +1,
            sizeof(char),
            letraActual,
            cmpChar
        );

        if (pos != -1)
            *letraActual = *(v_des + pos);

        letraActual++;
    }

    return str;
}

int buscarEnVector (void* vec, size_t cantElem, size_t tamElem, void* elem, Cmp cmp) {

    int pos = -1;
    void* i = vec;
    void* ult = vec + (cantElem -1) * tamElem;

    while (pos == -1 && i <= ult) {

        if (cmp (i, elem) == 0)
            pos = (i - vec) / tamElem;
        else
            i += tamElem;
    }

    return pos;
}

int cmpChar (void* a, void* b) {
    char* c1 = a;
    char* c2 = b;

    return *c1 - *c2;
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

size_t longitudLiteral (const char* str) {
    char* strP = (char*) str;

    while (*strP != '\0')
        strP++;

    return strP - str;
}
