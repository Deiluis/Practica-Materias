#include <stdio.h>

void cargarValores (int *, float *, char *);

int main () {

    int num;
    float real;
    char letra;

    cargarValores(&num, &real, &letra);

    printf("Entero: %d\n", num);
    printf("Float: %.2f\n" , real);
    printf("Letra: %c\n", letra);

    return 0;
}

void cargarValores (int *pInt, float *pFloat, char *pChar) {
    
    printf("Ingrese el entero: ");
    scanf("%d", pInt);
    printf("Ingrese el float: ");
    scanf("%f", pFloat);
    fflush(stdin);
    printf("Ingrese el char: ");
    scanf("%c", pChar);
}