#ifndef TDACOLA_H_INCLUDED
#define TDACOLA_H_INCLUDED

#define TAM_COLA 30

#define bool int
#define true 1
#define false 0

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct {
    char cola[TAM_COLA];
    unsigned pri;
    unsigned ult;
    unsigned tDisp;
} tCola;

void crearCola(tCola *p);
void vaciarCola(tCola *p);
bool colaLlena(const tCola *p, unsigned cantB);
bool colaVacia(const tCola *p);
bool ponerEnCola(tCola *p, const void *info, unsigned cantB);
bool sacarDeCola(tCola *p, void *info, unsigned cantB);
bool verPriDeCola(const tCola *p, void *info, unsigned cantB);


#endif // TDACOLA_H_INCLUDED
