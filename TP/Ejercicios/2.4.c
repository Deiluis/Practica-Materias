#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define SIN_MEM -1

size_t longitudString (const char*);
char* copiaCadena (const char*);

int main () {

    const char* orig = "Hola me llamo Luis Conforti AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char* dest;

    dest = copiaCadena(orig);

    if (dest == NULL) {
        printf("Memoria insuficiente");
        return SIN_MEM;
    }

    printf("Cadena original: %s\n", orig);
    printf("Longitud cadena original: %Id\n", longitudString(orig));
    printf("Cadena destino: %s\n", dest);
    printf("Longitud cadena destino: %Id\n", longitudString(dest));

    free(dest);
    dest = NULL;

    return 0;
}

size_t longitudString (const char* str) {

    const char* cursor = str;

    while (*cursor != '\0')
        cursor++;

    return cursor - str;
}

char* copiaCadena (const char* orig) {

    const char* cursorOrig = orig;
    char *dest, *cursorDest;
    size_t longitud = longitudString(orig);

    // longitud +1 ya que longitudString no cuenta a '/0' como caracter
    dest = malloc((longitud +1) * sizeof(char));

    if (dest == NULL)
        return NULL;

    cursorDest = dest;

    while (*cursorOrig != '\0') {
        *cursorDest = *cursorOrig;
        cursorDest++;
        cursorOrig++;
    }

    *cursorDest = '\0';

    return dest;
}