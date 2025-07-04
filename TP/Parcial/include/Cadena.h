#ifndef CADENA_H
#define CADENA_H

#include <stddef.h>
#include <stdbool.h>


void normalizar(const char* cadOri, char* cadDest);
bool sonAnagramas(char* palabra1, char* palabra2);
void invertirCadena(char* cadena);
char* reemplazarSubcad(const char* cadena, const char* subcad, const char* reemplazo, char* cadDestino, size_t tamCadDestino);


#endif // CADENA_H
