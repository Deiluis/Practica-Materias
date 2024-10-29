#include <stdio.h>
#include <string.h>

typedef struct {
    char nom[31];
    int dni;
} TAlumno;

int ingIngVal(int, int, int);
int cargarAlumnos(TAlumno[], int);
void mostrarAlumnos(TAlumno[], int);

int main () {
    TAlumno vAlum[50];
    int cant;

    cant = cargarAlumnos(vAlum, 50);
    
    if (cant > 0)
        mostrarAlumnos(vAlum, cant);
    else
        printf("No se cargaron alumnos.");

    return 0;
}

int ingIngVal(int limi, int lims, int cf) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato != cf)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato != cf);

    return dato;
}

int cargarAlumnos(TAlumno vAlum[], int tam) {
    int cant = 0, dni;
    char nom[31];

    printf("Carga de alumnos\n");
    printf("Ingrese el dni del primer alumno, 0 para terminar: ");
    dni = ingIngVal(1000000, 99999999, 0);

    while (dni > 0 && cant < tam) {
        printf("Ingrese el nombre del alumno: ");
        gets(nom);
        (*(vAlum+cant)).dni = dni;
        strcpy((*(vAlum+cant)).nom, nom);
        cant++;

        if (cant < tam) {
            printf("Ingrese el dni del siguiente alumno, o 0 para terminar: ");
            dni = ingIngVal(1000000, 99999999, 0);
        }
    }

    return cant;
}

void mostrarAlumnos(TAlumno vAlum[], int cant) {
    int i;

    printf("Alumnos cargados:\n");
    printf("DNI\t\tNombre\n");

    for (i = 0; i < cant; i++)
        printf("%d\t\t%s", (*(vAlum+i)).dni, (*(vAlum+i)).nom);
}
