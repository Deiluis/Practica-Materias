#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dni;
    char nomape[81];
    int n1, n2;
    float prom;
} Alumno;

void genArchivos();
void mostrar(char[]);

int main () {
    genArchivos();
    mostrar("PROMOCIONADOS.DAT");
    mostrar("CURSADOS.DAT");
    mostrar("REPROBADOS.DAT");

    return 0;
}

void genArchivos() {
    FILE *pAlum, *pProm, *pCurs, *pRep;
    Alumno alum;
    
    pAlum = fopen("ALUMNOS.DAT", "rb");
    pProm = fopen("PROMOCIONADOS.DAT", "wb");
    pCurs = fopen("CURSADOS.DAT", "wb");
    pRep = fopen("REPROBADOS.DAT", "wb");

    if (pAlum == NULL || pProm == NULL || pCurs == NULL || pRep == NULL) {
        printf("Hubo un error en el manejo de los archivos");
        exit(1);
    }

    fread(&alum, sizeof(Alumno), 1, pAlum);

    while (!feof(pAlum)) {
        if (alum.n1 >= 7) {
            if (alum.n2 >= 7) {
                fwrite(&alum, sizeof(Alumno), 1, pProm);
            } else {
                if (alum.n2 >= 4)
                    fwrite(&alum, sizeof(Alumno), 1, pCurs);
                else
                    fwrite(&alum, sizeof(Alumno), 1, pRep);
            }
        } else {
            if (alum.n1 >= 4) {
                if (alum.n2 >= 4)
                    fwrite(&alum, sizeof(Alumno), 1, pCurs);
                else
                    fwrite(&alum, sizeof(Alumno), 1, pRep);
            } else
                fwrite(&alum, sizeof(Alumno), 1, pRep);
        }

        fread(&alum, sizeof(Alumno), 1, pAlum);
    }

    fclose(pAlum);
    fclose(pProm);
    fclose(pCurs);
    fclose(pRep);
}

void mostrar(char nArchivo[]) {
    FILE *pf;
    Alumno alum;

    pf = fopen(nArchivo, "rb");

    if (pf == NULL) {
        printf("Hubo un error al abrir %s", nArchivo);
        exit(1);
    }

    printf("Archivo: %s\n\n", nArchivo);

    fread(&alum, sizeof(Alumno), 1, pf);

    while (!feof(pf)) {
        printf("%d\n", alum.dni);
        printf("%s\n", alum.nomape);
        printf("%d\n", alum.n1);
        printf("%d\n", alum.n2);
        printf("%.2f\n", alum.prom);
        printf("\n");

        fread(&alum, sizeof(Alumno), 1, pf);
    }

    fclose(pf);
    printf("\n");
}