#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <Comun.h>

#define BURBUJEO 1
#define SELECCION 2
#define INSERCION 3


typedef struct
{
	void* vec;
	int ce;
	int cap;
	size_t tamElem;
}
Vector;


typedef struct
{
	Vector* vector;
	void* ult;
	void* act;
	size_t tamElem;
}
VectorIterador;


int vectorCrear(Vector* vec, size_t tamElem);
int vectorCrearDeArchivo(Vector* v, size_t tamElem, const char* nomArch);
void vectorDestruir(Vector* vec);
void vectorVaciar(Vector* vector);
void vectorGrabar(Vector* v, const char* nombreArch);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp, Actualizar actualizar);
int vectorOrdInsertarCDup(Vector* vector, const void* elem, Cmp cmp);
void vectorRecorrer(const Vector* v, Accion accion, void* datosAccion);
int vectorOrdBuscar(const Vector* v, void* elem, Cmp cmp);
void* vectorElemPos(const Vector* v, unsigned pos); // Retorna la dirección del elemento en la posición pos.
int vectorOrdEliminarDuplicados(Vector* v, Cmp cmp, Actualizar actualizar);
int vectorInsertarAlFinal(Vector* vector, const void* elem);
void vectorOrdenar(Vector* vector, int metodo, Cmp cmp);
int vectorCantidadElementos(const Vector* v);
bool vectorVacio(const Vector* v);

void vectorItCrear(VectorIterador* it, Vector* vector);
void* vectorItPrimero(VectorIterador* it);
void* vectorItSiguiente(VectorIterador* it);
bool vectorItFin(VectorIterador* it);


#endif //VECTOR_VECTOR_H
