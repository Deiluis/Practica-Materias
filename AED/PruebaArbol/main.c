#include <stdio.h>
#include <stdlib.h>
#include "../TDAArbol/Arbol.h"

void mostrarInt (void* elem);
int compararInt (const void* e1, const void* e2);

int main() {

    tArbol arbol;
    //int dato;
    int nums[] = {5, 3, 8, 1};
    int cod = TODO_OK;
    int* i;

    crearArbol(&arbol);

    i = nums;

    while (cod == TODO_OK && i < (nums + sizeof(nums) / sizeof(int))) {

        cod = ponerEnArbolR(&arbol, i, sizeof(*i), compararInt);

        if (cod == ERR_MEMORIA)
            printf("Error creando elemento %d, memoria insuficiente\n", *i);

        if (cod == DUPLICADO)
            printf("Error creando elemento %d, esta duplicado\n", *i);

        i++;
    }

    recorrerArbol(&arbol, POSORDEN, mostrarInt);
    printf("\n");

    return 0;
}

void mostrarInt (void* elem) {
    int* num = (int*) elem;
    printf("%d, ", *num);
}

int compararInt (const void* e1, const void* e2) {
    int* n1 = (int*) e1;
    int* n2 = (int*) e2;

    return *n1 - *n2;
}
