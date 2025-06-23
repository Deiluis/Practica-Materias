#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include "../Comun/CodigosRet.h"

#define TAM 10

#define CAP_INI 8 // Cantidad elementos
#define FACTOR_INCR 1.5 // Incremento del 50%
#define FACTOR_DECR 0.5 // Decremento del 50%
#define FACTOR_OCUP 0.25 // Ocupación del 25%

#define AUMENTAR 1
#define DISMINUIR 2

#define BURBUJEO 1
#define SELECCION 2
#define SELECCION_DOBLE 3
#define INSERCION 4

typedef struct
{
    void* vec;
    size_t tam;
    size_t cap;
    size_t tamElem;
} Vector;

typedef struct
{
    void* act;
    void* ult;
    Vector* vector;
    bool finIter;
} VectorIterador;

typedef int (*Cmp) (const void* a, const void* b);
typedef void (*Imp) (const void* elem);
typedef void (*Accion) (void* elem, void* datos);

bool vectorCrear (Vector* v, size_t tamElem);
int vectorCrearDeArchivo (Vector* v, size_t tamElem, const char* nomArch);
int vectorGrabar(Vector* v, const char* nomArch);
int vectorOrdInsertar(Vector* v, void* elem, Cmp cmp);
int vectorInsertarAlInicio(Vector* v, void* elem, Cmp cmp);
int vectorInsertarAlFinal(Vector* v, void* elem);
int vectorInsertarEnPos(Vector* v, void* elem, int pos, Cmp cmp);
int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp);
int vectorDesordBuscar(const Vector* v, void* elem, Cmp cmp);
bool vectorOrdEliminar (Vector* v, void* elem, Cmp cmp);
bool vectorEliminarDePos (Vector* v, int pos);
void vectorOrdenar (Vector* v, int metodo, Cmp cmp);
void vectorVaciar (Vector* v);
void vectorDestruir (Vector* v);
void vectorMostrar (const Vector* v, Imp imp);
size_t max (size_t a, size_t b);


// Vector iterador

void vectorIteradorCrear (VectorIterador* it, const Vector* v);
void* vectorIteradorPrimero (VectorIterador* it);
void* vectorIteradorSiguiente (VectorIterador* it);
bool vectorIteradorFin (VectorIterador* it);


#endif // VECTOR_H
