#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#define TAM 10

#define LLENO 0
#define DUPLICADO 1
#define FUERA_RANGO 2
#define OK 3
#define SIN_MEM 4

#define CAP_INI 8 // Cantidad elementos
#define FACTOR_INCR 1.5 // Incremento del 50%
#define FACTOR_DECR 0.5 // Decremento del 50%
#define FACTOR_OCUP 0.25 // Ocupación del 25%

#define AUMENTAR 1
#define DISMINUIR 2

typedef struct
{
    int* vec;
    size_t tam;
    size_t cap;
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
bool redimensionarVector (Vector* v, int operacion);
size_t max (size_t a, size_t b);


#endif // VECTOR_H
