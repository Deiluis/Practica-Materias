#include "./string.h"
#include "../comun/comun.h"

size_t strlen(const char* str) {
    char *act = (char*) str;

    while (*act != '\0')
        act++;

    return act - str;
}

void readStr(char* str, size_t len, FILE* iostream) {
    char* act = str;
    
    // Len incluye el tamanio con el /0.
    fgets(str, len, iostream);

    while (*act != '\0' && *act != '\n')
        act++;

    *act = '\0';
}

void intToStr(char* str, int num) {

    int dig, res, div = 1;
    char* act = str;

    if (num < 0) {
        *act = '-';
        act++;
        num = ABS(num);
    }

    res = num / div;

    while (res >= 10) {
        div *= 10;
        res = num / div;
    }

    while (div > 0) {
        dig = num / div;
        num %= div;
        div /= 10;
        *act = '0' + dig;
        act++;
    }

    *act = '\0';
}

int parseInt(const char* str) {

    int num = 0, fact = 1, i, neg;
    char* act = (char*) str;
    size_t len;

    if (*act == '-') {
        act++;
        neg = true;
    }
        
    len = strlen(act);

    for (i = 1; i < len; i++)
        fact *= 10;

    while (*act != '\0') {
        num += (*act - '0') * fact;
        fact /= 10;
        act++;
    }

    if (neg)
        num *= -1;

    return num;
}
