#ifndef COMUNLISTAENLAZADA_H_INCLUDED
#define COMUNLISTAENLAZADA_H_INCLUDED

#include <stddef.h>

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
} tNodo;

typedef struct sNodoA {
    void* info;
    unsigned tamInfo;
    struct sNodoA *izq, *der;
} tNodoA;

typedef struct sNodoD {
    void* info;
    unsigned tamInfo;
    struct sNodoD *ant, *sig;
} tNodoD;

typedef int (*Cmp) (const void* elem1, const void* elem2);
typedef void (*Acc) (void* elem, void* extra);
typedef bool (*Cond) (const void* elem);

#endif // COMUNLISTAENLAZADA_H_INCLUDED
