#include <stdio.h>
#include <stdlib.h>
#include "TDAPila.h"

int main()
{
    tPila pila1;
    int nums[] = { 100, 200, 300, 400, 500, 600, 700, 800 };
    int i;
    int dato;

    crearPila(&pila1);

    for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
        if (apilar(&pila1, nums + i, sizeof(int)) != TODO_OK)
            printf("Pila llena\n");
    }

    if (verTope(&pila1, &dato, sizeof(dato)) == TODO_OK)
        printf("El tope es: %d\n", dato);

//    for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
//        if (desapilar(&pila1, &dato, sizeof(dato)) != TODO_OK)
//            printf("Pila vacia\n");
//    }

    vaciarPila(&pila1);

    if (pilaLlena(&pila1, sizeof(int)) == LLENO)
        printf("Pila llena\n");

    return 0;
}
