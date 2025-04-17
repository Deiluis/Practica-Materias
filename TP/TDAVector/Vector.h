#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#define TAM 10
#define LLENO 0
#define DUPLICADO 1
#define FUERA_RANGO 2
#define OK 3

typedef struct
{
    int vec[TAM];
    size_t tam;
} Vector;

bool vectorCrear (Vector* v);
int vectorOrdInsertar(Vector* v, int elem);
int vectorInsertarAlInicio(Vector* v, int elem);
int vectorInsertarAlFinal(Vector* v, int elem);
int vectorInsertarEnPos(Vector* v, int elem, int pos);
int vectorOrdBuscar(const Vector* v, int elem);
int vectorDesordBuscar(const Vector* v, int elem);
bool vectorOrdEliminar (Vector* v, int elem);
bool vectorEliminarDePos (Vector* v, int pos);
void vectorOrdenar (Vector* v);
void vectorVaciar (Vector* v);
void vectorDestruir (Vector* v);

#endif // VECTOR_H
