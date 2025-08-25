#ifndef TDAPILA_H_INCLUDED
#define TDAPILA_H_INCLUDED

#define TAM_PILA 300
#define TODO_OK 0
#define LLENO 1
#define VACIO -1
#define NO_VACIO 2
#define NO_LLENO 3

typedef struct {
    char pila[TAM_PILA];
    unsigned int tope;
} tPila;

void crearPila(tPila* pila);
int apilar(tPila* pila, const void* elem, unsigned int tamElem);
int verTope(const tPila* pila, void* elem, unsigned int tamElem);
int desapilar(tPila* pila, void* elem, unsigned int tamElem);
void vaciarPila(tPila* pila);
int pilaVacia(const tPila* pila);
int pilaLlena(const tPila* pila, unsigned int tamElem);

#endif // TDAPILA_H_INCLUDED
