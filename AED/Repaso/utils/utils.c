#include <math.h>

#define EPSILON 1e-10f
#define IGUALES 0
#define A_ES_MAYOR 1
#define B_ES_MAYOR -1

int cmpFloat(const void* a, const void* b) {

    float nroA = *(float*) a;
    float nroB = *(float*) b;

    if (fabsf(nroA - nroB) < EPSILON)
        return IGUALES;
    else if (nroA > nroB)
        return A_ES_MAYOR;
    else
        return B_ES_MAYOR;
}
