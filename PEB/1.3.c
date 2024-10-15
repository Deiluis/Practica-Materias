#include <stdio.h>

int ingIntVal (int, int, int);
int ingIntEntre (int, int);
int buscarDNI (int[], int, int);
int cargarNotas (int[], int[], int);
void ordenar (int[], int[], int);
void mostrar (int[], int[], int);

int main () {

    int cantAlum, vDNI[60], vNota[60];

    cantAlum = cargarNotas(vDNI, vNota, 60);

    if (cantAlum > 0) {
        ordenar(vDNI, vNota, cantAlum);

        printf("Listado de alumnos cargado con sus notas ordenados de manera descendente:\n");
        mostrar(vDNI, vNota, cantAlum);
    } else
        printf("No se cargaron alumnos.");

    return 0;
}

int ingIntVal (int limi, int lims, int menA) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato >= menA)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato >= menA);

    return dato;
}

int ingIntEntre (int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato < limi || dato > lims)
            printf("Dato invalido, reingresar: ");

    } while (dato < limi || dato > lims);

    return dato;
}

int buscarDNI (int vDNI[], int tam, int dni) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vDNI[i] == dni)
            pos = i;
        else
            i++;
    }

    return pos;
}

int cargarNotas (int vDNI[], int vNota[], int tam) {
    int cant = 0, pos, dni, nota;

    printf("Se ingresara el listado de alumnos por DNI junto con su nota en el parcial.\n\n");

    printf("Ingrese el DNI de un alumno (entre 1000000 y 99999999, negativo para terminar): ");
    dni = ingIntVal(1000000, 99999999, 0);
    
    while (dni > 0 && cant < tam) {
        pos = buscarDNI(vDNI, tam, dni);

        if (pos == -1) {
            printf("Ingrese la nota del alumno (entero, 1 a 10): ");
            nota = ingIntEntre(1, 10);
            vDNI[cant] = dni;
            vNota[cant] = nota;
            cant++;
        } else {
            printf("No se puede cargar un DNI ya cargado.\n");
        }

        if (cant < tam) {
            printf("Ingrese el DNI del proximo alumno (entre 1000000 y 99999999, negativo para terminar): ");
            dni = ingIntVal(1000000, 99999999, 0);
        }
    }

    return cant;
}

void ordenar (int vDNI[], int vNota[], int tam) {
    int i, j, aux;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam -1 - i; j++) {
            if (vNota[j] < vNota[j +1]) {

                aux = vNota[j +1];
                vNota[j +1] = vNota[j];
                vNota[j] = aux;

                aux = vDNI[j +1];
                vDNI[j +1] = vDNI[j];
                vDNI[j] = aux;
            }
        }
    }
}

void mostrar (int vDNI[], int vNota[], int tam) {
    int i;

    printf("DNI\t\tNota\n");

    for (i = 0; i < tam; i++)
        printf("%d\t\t%d\n", vDNI[i], vNota[i]);
}