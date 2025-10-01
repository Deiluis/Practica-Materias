#include <stdio.h>
#include <stdlib.h>

#define COLA 0
#define PILA 1

#define PRUEBA COLA

#if PRUEBA == COLA
    #include "../TDAColaCircular/Cola.h"
#else
    #include "../TDAPilaCircular/Pila.h"
#endif

void probarCola();
void probarPila();

int main () {

    #if PRUEBA == COLA
        probarCola();
    #else
        probarPila();
    #endif

    return 0;
}



#if PRUEBA == COLA

void probarCola() {
    tCola cola;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int dato;
    int* i;
    bool memLibre = true;

    crearCola(&cola);

    i = nums;
    memLibre = ponerEnCola(&cola, i, sizeof(int));
    i++;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = ponerEnCola(&cola, i, sizeof(int));
        i++;
    }

    if (!memLibre) {
        vaciarCola(&cola);
        printf("Memoria insuficiente");
    }

    while (sacarDeCola(&cola, &dato, sizeof(int)))
        printf("%d\n", dato);

    if (verPriDeCola(&cola, &dato, sizeof(dato)))
        printf("Primero: %d\n", dato);
    else
        printf("Cola vacia");
}
#else

void probarPila() {
    tPila pila;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int dato;
    int* i;
    bool memLibre = true;

    crearPila(&pila);

    i = nums;
    memLibre = apilar(&pila, i, sizeof(int));
    i++;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = apilar(&pila, i, sizeof(int));
        i++;
    }

    if (!memLibre) {
        vaciarPila(&pila);
        printf("Memoria insuficiente");
    }

    while (desapilar(&pila, &dato, sizeof(int)))
        printf("%d\n", dato);

    if (verTope(&pila, &dato, sizeof(dato)))
        printf("Tope: %d\n", dato);
    else
        printf("Pila vacia");

}
#endif
