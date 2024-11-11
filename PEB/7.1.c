#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int canal;
    char prog[36];
    float rating;
} TRating;

typedef struct {
    int canal;
    float prom;
} TProm;

int main () {
    FILE *pRat, *pProm;
    TRating reg;
    TProm promReg;
    float ratingCanal, maxRating = 0;
    int maxCanal, cantProg, antCanal;

    pRat = fopen("Archivos/RATING.DAT", "rb");
    pProm = fopen("Archivos/PROMEDIOS_RATING.DAT", "wb");

    if (pRat == NULL || pProm == NULL) {
        printf("Hubo un error en el manejo de archivos");
        exit(1);
    }

    fread(&reg, sizeof(TRating), 1, pRat);

    printf("Canales con menos de 15 puntos de rating:\n");

    while (!feof(pRat)) {

        antCanal = reg.canal;
        ratingCanal = 0;
        cantProg = 0;

        do {
            cantProg++;
            ratingCanal += reg.rating;
            fread(&reg, sizeof(TRating), 1, pRat);
        } while (!feof(pRat) && reg.canal == antCanal);

        if (ratingCanal < 15)
            printf("%d\n", antCanal);

        if (ratingCanal > maxRating) {
            maxCanal = antCanal;
            maxRating = ratingCanal;
        }
            
        promReg.canal = antCanal;
        promReg.prom = ratingCanal / cantProg;
        fwrite(&promReg, 1, sizeof(TProm), pProm);

    }

    printf("\nEl canal mas visto fue el: %d", maxCanal);

    fclose(pRat);
    fclose(pProm);

    return 0;
}