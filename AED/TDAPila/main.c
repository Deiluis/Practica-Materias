#include <stdio.h>
#include <stdlib.h>
#include "TDAPila.h"

typedef struct {
    char codigo[11];
    char descripcion[51];
    float precio;
    int stock;
} Producto;

int main()
{
    tPila pila1;

    Producto prods[] = {
        { "BANA",   "Banana",    2200.5,  7 },
        { "PERA",   "Pera",      1800.0,  5 },
        { "MANZ",   "Manzana",   2000.0,  6 },
        { "KIWI",   "Kiwi",      2500.5,  3 },
        { "UVA",    "Uvas",      3000.0,  10 },
        { "MELN",   "Melon",     2700.3,  2 },
        { "DURZ",   "Durazno",   2100.9,  4 },
        { "CIRU",   "Ciruela",   2300.0,  8 },
        { "NARA",   "Naranja",   1900.2,  6 },
        { "LIMN",   "Limon",     1600.7,  9 }
    };

    int i;
    Producto dato;

    crearPila(&pila1);

    for (i = 0; i < (sizeof(prods) / sizeof(Producto)); i++) {
        if (apilar(&pila1, prods + i, sizeof(Producto)) != TODO_OK)
            printf("Pila llena\n");
    }

    if (verTope(&pila1, &dato, sizeof(dato)) == TODO_OK)
        printf("El id del tope es: %s\n", dato.codigo);

//    for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
//        if (desapilar(&pila1, &dato, sizeof(dato)) != TODO_OK)
//            printf("Pila vacia\n");
//    }

    vaciarPila(&pila1);

    if (pilaLlena(&pila1, sizeof(Producto)) == LLENO)
        printf("Pila llena\n");

    return 0;
}
