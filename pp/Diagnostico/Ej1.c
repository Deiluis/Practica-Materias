#include <stdio.h>

int main () {

    int mtx[][] = {
        {1, 2, 3}, 
        {4, 1, 6},
        {7, 8, 2} 
    };

    int i = 1;
    int sum = mtx[0][0];
    int order = 3;

    while (i < order && mtx[i][i] == sum) {
        sum += mtx[i][i];
        i++;
    }

    if (i == order)
        printf("La matriz cumple la regla\n");
    else
        printf("La matriz no cumple la regla\n");

    return 0;
}