#include <stdio.h>

int main () {

    int num, *p;

    p = &num;
    *p = 20;

    printf("Direccion de num: %p\n", &num);
    printf("Direccion de p: %p\n", &p);
    printf("Contenido de num: %d\n", num);
    printf("Contenido de num: %d\n", *p);
    printf("Contenido de p: %p\n", p);

    return 0;
}