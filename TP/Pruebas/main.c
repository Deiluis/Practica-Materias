#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define P_ENTERA(x) ((int) (x))
#define P_DECIMAL(x) ((x) - (int) (x))
#define ES_MAYUSCULA(c) ((c) >= 'A' && (c) <= 'Z')
#define ES_MINUSCULA(c) ((c) >= 'a' && (c) <= 'z')
#define ES_LETRA(c) (ES_MAYUSCULA(c) || ES_MINUSCULA(c))
#define ES_NUMERO(c) ((c) >= '0' && (c) <= '9')
#define A_MAYUSCULA(c) (ES_LETRA(c) ? (ES_MAYUSCULA(c) ? (c) : (c) - ('a' - 'A')) : (c))
#define A_MINUSCULA(c) (ES_LETRA(c) ? (ES_MINUSCULA(c) ? (c) : (c) + ('a' - 'A')) : (c))
#define FACTORIAL(x) ({\
    int fact = 1;\
    int i;\
    for (i = x; i > 1; i--)\
        fact *= i;\
    (fact);\
})

#include "../String/String.h"

int main () {
    String str1;
    String str2;

    stringCrear(&str1);
    stringCrear(&str2);

    stringCopiarLiteral(&str1, "abcdefghij");
    stringCopiarLiteral(&str2, "GHI");

    printf("%d\n", longitudLiteral(""));

    return 0;
}
