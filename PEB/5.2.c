#include <stdio.h>

int main () {

    int n1, n2, n3, *p1, *p2;

    p1 = &n1;
    p2 = &n2;

    
    printf("Numero 1: ");
    scanf("%d", p1);
    printf("Numero 2: ");
    scanf("%d", p2);

    n3 = *p1 + *p2;

    printf("Resultado: %d", n3);

    return 0;
}