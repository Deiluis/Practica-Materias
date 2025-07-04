#ifndef PALABRA_H_INCLUDED
#define PALABRA_H_INCLUDED


#define PAL_TAM 50

typedef struct {
    char vPal[PAL_TAM +1];
} Palabra;

typedef char* (*Modif) (char* cad);

void palabraModificar (Palabra* pal, Modif modif);

#endif
