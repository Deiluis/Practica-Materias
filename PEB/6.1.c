#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dni;
    char nomape[81];
    int n1, n2;
    float prom;
} Alumno;

int ingIntVal (int, int, int);
void guardar ();
void lectura ();

int main () {
    guardar();
    lectura();

    return 0;
}

int ingIntVal (int limi, int lims, int cf) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato != cf)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato != cf);

    return dato;
}

void guardar () {
    FILE *fp;
    Alumno alum;
    int dni;

    fp = fopen("ALUMNOS.DAT", "wb");

    if (fp == NULL) {
        printf("No pudo crearse el archivo.");
        exit(1);
    }

    printf("Carga de alumnos\n");
    printf("Ingresa el DNI del primer alumno (1000000 a 99999999), 0 para terminar: ");
    dni = ingIntVal(1000000, 99999999, 0);

    while (dni > 0) {
        alum.dni = dni;

        printf("Ingresa el nombre y apellido del alumno: ");
        fflush(stdin);
        gets(alum.nomape);

        printf("Ingresa la primer nota: ");
        alum.n1 = ingIntVal(1, 10, 10);

        printf("Ingresa la segunda nota: ");
        alum.n2 = ingIntVal(1, 10, 10);

        alum.prom = (float) (alum.n1 + alum.n2) / 2;

        fwrite(&alum, sizeof(Alumno), 1, fp);

        printf("Ingresa el DNI del siguiente alumno (1000000 a 99999999), 0 para terminar: ");
        dni = ingIntVal(1000000, 99999999, 0);
    }

    fclose(fp);
}

void lectura () {
    FILE *fp;
    Alumno alum;

    fp = fopen("ALUMNOS.DAT", "rb");

    if (fp == NULL) {
        printf("No se pudo abrir el archivo para leerlo");
        exit(1);
    }

    fread(&alum, sizeof(Alumno), 1, fp);

    while (!feof(fp)) {
        printf("%d\n", alum.dni);
        printf("%s\n", alum.nomape);
        printf("%d\n", alum.n1);
        printf("%d\n", alum.n2);
        printf("%.2f\n", alum.prom);
        printf("\n");

        fread(&alum, sizeof(Alumno), 1, fp);
    }

    fclose(fp);
}