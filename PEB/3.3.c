#include <stdio.h>
#include <string.h>

int ingIntVal (int, int);
void leerTexto (char[], int);
int buscarDNI (int[], int, int);
void mostrarDNIConNombre (int[], char[][31], int, char[]);
int cargarAlum (int[], char[][31], int);
void busquedaAlum (int[], char[][31], int);
void ordenar (int[], char[][31], int);
void mostrar (int[], char[][31], int);

int main () {
    int cant, vDNI[50];
    char vNombres[50][31];

    cant = cargarAlum(vDNI, vNombres, 50);
    printf("\n");

    if (cant > 0) {
        busquedaAlum(vDNI, vNombres, cant);
        printf("\n");
        ordenar(vDNI, vNombres, cant);
        mostrar(vDNI, vNombres, cant);
    } else {
        printf("No se cargaron alumnos");
    }

    return 0;
}

int ingIntVal (int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato < limi || dato > lims)
            printf("Dato invalido, reingresar: ");

    } while (dato < limi || dato > lims);

    return dato;
}

void leerTexto (char texto[], int tam) {
    int i = 0;

    fflush(stdin);
    fgets(texto, tam, stdin);

    while (texto[i] != '\0') {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}

int buscarDNI (int vDNI[], int tam, int val) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vDNI[i] == val)
            pos = i;
        else
            i++;
    }

    return pos;
}

void mostrarDNIConNombre (int vDNI[], char vNombres[][31], int tam, char nombre[]) {
    int i, cant = 0;

    printf("Los DNI que coinciden con este nombre son: ");

    for (i = 0; i < tam; i++) {
        if (strcmpi(vNombres[i], nombre) == 0) {
            printf("%d, ", vDNI[i]);
            cant++;
        }
    }
    
    if (cant == 0)
        printf("Ninguno.");
    
    printf("\n");
}

int cargarAlum (int vDNI[], char vNombres[][31], int tam) {
    int cant = 0, dni, pos;
    char nombre[31];

    printf("Se cargaran los alumnos del curso.\n\n");
    printf("Carga el nombre del primer alumno, 'FIN' para terminar: ");
    leerTexto(nombre, 31);

    while (strcmpi(nombre, "FIN") != 0 && cant < tam) {
        printf("Ingresa el DNI del alumno: ");
        dni = ingIntVal(1000000, 99999999);
        pos = buscarDNI(vDNI, tam, dni);

        if (pos == -1) {
            vDNI[cant] = dni;
            strcpy(vNombres[cant], nombre);
            cant++;
        } else {
            printf("Ya existe un alumno cargado con este DNI.\n\n");
        }

        if (cant < tam) {
            printf("Carga el nombre del siguiente alumno, 'FIN' para terminar: ");
            leerTexto(nombre, 31);
        }
    }   

    return cant;
}

void busquedaAlum (int vDNI[], char vNombres[][31], int tam) {
    char nombre[31];

    printf("Busqueda de alumnos por nombre.\n\n");
    printf("Ingrese el nombre de un alumno para conocer su DNI o DNIs si el nombre coincide con mas de un alumno.\n");
    printf("Ingresa 'NOBUSCARMAS' para terminar: ");
    leerTexto(nombre, 31);

    while (strcmpi(nombre, "NOBUSCARMAS") != 0) {
        mostrarDNIConNombre(vDNI, vNombres, tam, nombre);

        printf("Ingrese el nombre de otro alumno para conocer su DNI o DNIs si el nombre coincide con mas de un alumno.\n");
        printf("Ingresa 'NOBUSCARMAS' para terminar: ");
        leerTexto(nombre, 31);
    }
}

void ordenar (int vDNI[], char vNombres[][31], int tam) {
    int i, j, dniAux;
    char nombreAux[31];

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam -1 -i; j++) {
            if (strcmpi(vNombres[j], vNombres[j+1]) > 0) {

                strcpy(nombreAux, vNombres[j+1]);
                strcpy(vNombres[j+1], vNombres[j]);
                strcpy(vNombres[j], nombreAux);

                dniAux = vDNI[j+1];
                vDNI[j+1] = vDNI[j];
                vDNI[j] = dniAux;
            }
        }
    }
}

void mostrar (int vDNI[], char vNombres[][31], int tam) {
    int i;

    printf("Listado de alumnos ordenado de manera alfabetica de menor a mayor:\n");
    printf("DNI\t\tNombre\n");

    for (i = 0; i < tam; i++) {
        printf("%d\t\t%s\n", vDNI[i], vNombres[i]);
    }
}