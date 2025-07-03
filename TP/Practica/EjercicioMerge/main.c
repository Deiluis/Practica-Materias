#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_ARG 2

#define ARG_ARCH_EMP 1
#define ARG_ARCH_EST 2
#define CANT_ARG 3

typedef struct {
    int dni;
    char apellido[51];
    char nombre[51];
    double sueldo;
} Empleado;

typedef struct {
    int dni;
    char apellido[51];
    char nombre[51];
    float promedio;
} Estudiante;

int generarEmpleados(const char* nomArchEmp);
int generarEstudiantes(const char* nomArchEst);
int mostrarEmpleados(const char* nomArchEmp);
int mostrarEstudiantes(const char* nomArchEst);
int compararRegistros(Empleado* emp, Estudiante* est);
int actualizarSueldos(const char* nomArchEmp, const char* nomArchEst);

// 5.7.exe Empleados.dat Estudiantes.dat
int main (int argc, char* argv[]) {

    if (argc != CANT_ARG)
        return ERR_ARG;

    generarEmpleados(argv[ARG_ARCH_EMP]);
    generarEstudiantes(argv[ARG_ARCH_EST]);

    mostrarEmpleados(argv[ARG_ARCH_EMP]);
    printf("\n");

    mostrarEstudiantes(argv[ARG_ARCH_EST]);
    printf("\n");

    actualizarSueldos(argv[ARG_ARCH_EMP], argv[ARG_ARCH_EST]);

    mostrarEmpleados(argv[ARG_ARCH_EMP]);
    printf("\n");

    return 0;
}

int generarEmpleados(const char* nomArchEmp) {

    FILE* archEmp = fopen(nomArchEmp, "wb");

    if (!archEmp)
        return ERR_ARCHIVO;

    Empleado empleados[] = {
        { 1007, "Fernandez", "Sofia",     120000.0 },
        { 1009, "Gomez",     "Ana",       105000.0 },
        { 1006, "Lopez",     "Juan",      98000.0  },
        { 1011, "Lopez",     "Juan",      60000.0  },
        { 1004, "Lopez",     "Maria",     96000.0  },
        { 1005, "Martinez",  "Carlos",    112000.0 },
        { 1003, "Mendez",    "Julian",    99000.0  },
        { 1001, "Perez",     "Lucia",     125000.0 },
        { 1008, "Sosa",      "Camila",    101000.0 },
        { 1002, "Zapata",    "Nicolas",   88000.0  },
        { 1010, "Zarate",    "Clara",     97000.0  },
    };

    fwrite(empleados, sizeof(Empleado), sizeof(empleados) / sizeof(Empleado), archEmp);
    fclose(archEmp);

    return TODO_OK;
}

int generarEstudiantes(const char* nomArchEst) {

    FILE* archEst = fopen(nomArchEst, "wb");

    if (!archEst)
        return ERR_ARCHIVO;

    Estudiante estudiantes[] = {
        { 1012, "Acosta",     "Sofia",     4.2 },
        { 1007, "Fernandez", "Sofia",     7.5 },
        { 1009, "Gomez",     "Ana",       6.2 },
        { 1006, "Lopez",     "Juan",      8.2  },
        { 1011, "Lopez",     "Juan",      6.4  },
        { 1004, "Lopez",     "Maria",     5.9  },
        { 1003, "Mendez",    "Julian",    7.1  },
        { 1001, "Perez",     "Lucia",     6.4 },
        { 1008, "Sosa",      "Camila",    8.6 },
        { 1010, "Zarate",    "Clara",     7.9  },
    };

    fwrite(estudiantes, sizeof(Estudiante), sizeof(estudiantes) / sizeof(Estudiante), archEst);
    fclose(archEst);

    return TODO_OK;
}

int mostrarEmpleados(const char* nomArchEmp) {

    FILE* archEmp = fopen(nomArchEmp, "rb");

    if (!archEmp)
        return ERR_ARCHIVO;

    Empleado emp;

    while (fread(&emp, sizeof(Empleado), 1, archEmp))
        printf("%-20s %-20s %d %.2f\n", emp.apellido, emp.nombre, emp.dni, emp.sueldo);

    fclose(archEmp);

    return TODO_OK;


}

int mostrarEstudiantes(const char* nomArchEst) {

    FILE* archEst = fopen(nomArchEst, "rb");

    if (!archEst)
        return ERR_ARCHIVO;

    Estudiante est;

    while (fread(&est, sizeof(Estudiante), 1, archEst))
        printf("%-20s %-20s %d %.2f\n", est.apellido, est.nombre, est.dni, est.promedio);

    fclose(archEst);

    return TODO_OK;
}

int compararRegistros(Empleado* emp, Estudiante* est) {

    int comp = strcmp(emp -> apellido, est -> apellido);

    if (comp != 0)
        return comp;

    comp = strcmp(emp -> nombre, est -> nombre);

    if (comp != 0)
        return comp;

    comp = emp -> dni - est -> dni;

    return comp;
}

int actualizarSueldos(const char* nomArchEmp, const char* nomArchEst) {

    FILE* archEmp = fopen(nomArchEmp, "r+b");

    if (!archEmp)
        return ERR_ARCHIVO;

    FILE* archEst = fopen(nomArchEst, "rb");

    if (!archEst) {
        fclose(archEmp);
        return ERR_ARCHIVO;
    }
        
    Empleado emp;
    Estudiante est;
    int comp;

    fread(&emp, sizeof(Empleado), 1, archEmp);
    fread(&est, sizeof(Estudiante), 1, archEst);

    while (!feof(archEmp) && !feof(archEst)) {

        comp = compararRegistros(&emp, &est);

        if (comp == 0) {
            
            if (est.promedio >= 7) {
                emp.sueldo *= 1.0728;

                fseek(archEmp, (long) -sizeof(Empleado), SEEK_CUR);
                fwrite(&emp, sizeof(Empleado), 1, archEmp);
                fflush(archEmp);
            }

            fread(&emp, sizeof(Empleado), 1, archEmp);
            fread(&est, sizeof(Estudiante), 1, archEst);
        }

        else if (comp < 0) 
            fread(&emp, sizeof(Empleado), 1, archEmp);

        else
            fread(&est, sizeof(Estudiante), 1, archEst);
    }

    fclose(archEmp);
    fclose(archEst);

    return TODO_OK;
}