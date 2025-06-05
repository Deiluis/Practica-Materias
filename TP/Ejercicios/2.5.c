#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIN_MEM -1

void* copiaCosas (void*, size_t);
void* moverMemoria (void*, void*, size_t);

int main () {

    char* orig = "Hola que tal";
    char* dest;

    dest = copiaCosas(orig, sizeof(char) * (strlen(orig) +1));

    if (dest == NULL) {
        printf("Memoria insuficiente");
        return SIN_MEM;
    }

    printf("Cadena original: %s\n", orig);
    printf("Cadena destino: %s\n", dest);

    free(dest);
    dest = NULL;

    return 0;
}

void* copiaCosas (void* elem, size_t tamElem) {

    if (elem == NULL || tamElem == 0)
        return NULL;

    void *dest;

    dest = malloc(tamElem);

    if (dest == NULL)
        return NULL;

    if (moverMemoria(dest, elem, tamElem) == NULL)
        return NULL;

    return dest;
}

void* moverMemoria (void* dest, void* origen, size_t tam) {

    if (dest == NULL || origen == NULL || tam == 0)
        return NULL;

    const char* buffer;

    buffer = malloc(tam);

    if (buffer == NULL)
        return NULL;

    const char* iniOrig = (char*) origen;
    const char* ultOrig = iniOrig + tam -1;
    const char* iniDest = (char*) dest;
    const char* ultDest = iniDest + tam -1;
    char* i;
    char* bufferCur = (char*) buffer;

    for (i = (char*) iniOrig; i <= ultOrig; i++, bufferCur++)
        *bufferCur = *i;

    bufferCur = (char*) buffer;

    for (i = (char*) iniDest; i <= ultDest; i++, bufferCur++)
        *i = *bufferCur;

    free((char*) buffer);

    return dest;
}