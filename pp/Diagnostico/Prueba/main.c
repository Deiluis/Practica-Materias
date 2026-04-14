#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

int main () {

    int mtx[][ORDER] = {
        {2, 2, 3, 6},
        {4, 2, 6, 7},
        {7, 8, 4, 11},
        {-5, 6, 5, 8},
    };
    int sum = mtx[0][0];

    for (int i = 1; i < ORDER && mtx[i][i] == sum; i++)
        sum += mtx[i][i];

    if (i == ORDER)
        printf("La matriz cumple la regla\n");
    else
        printf("La matriz no cumple la regla\n");

    return 0;
}
