#include <stdio.h>

void cargar (int[], int);
int* buscar (int[], int, int);
void mostrar(int[], int);

int main () {

    int vNums[10];
    int val, *pPos, pos;

    cargar(vNums, 10);
    mostrar(vNums, 10);

    printf("Busqueda de valores\n");
    printf("Ingrese un valor a buscar en el vector para saber si se encuentra en el mismo. 0 o negativo para terminar: ");
    scanf("%d", &val);

    while (val > 0) {

        pPos = buscar(vNums, 10, val);

        printf("%p\n", vNums);
        printf("%p\n", pPos);
        printf("%p\n", pPos - vNums);

        if (pPos != NULL) {
            pos = pPos - vNums;
            printf("El numero %d se encuenta en la posicion: %d del vector\n", val, pos +1);
        } else
            printf("No se encontro el valor en el vector\n");
            
        printf("Ingresar el siguiente valor a buscar: ");
        scanf("%d", &val);
    }

    return 0;
}

void cargar (int vec[], int tam) {
    int i;

    for (i = 0; i < tam; i++) {
        printf("Cargue el entero numero %d: ", i+1);
        scanf("%d", vec+i);
    }
}

int* buscar (int vec[], int tam, int val) {
    int i = 0, *pPos = NULL;

    while (pPos == NULL && i < tam) {
        if (*(vec+i) == val)
            pPos = vec+i;
        else
            i++;
    }

    return pPos;
}

void mostrar(int vec[], int tam) {
    int i;

    printf("Vector cargado:\n");

    for (i = 0; i < tam; i++) {
        printf("%d, ", *(vec+i));
    }
}
