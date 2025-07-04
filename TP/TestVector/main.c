#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../TDAVector/Vector.h"


typedef struct
{
    int d;
    int m;
    int a;
}
Fecha;


typedef struct
{
    int legajo;
    char apynom[51];
    float sueldo;
}
Empleado;

void imprimirFecha(const void* a);
void imprimirEmpleado(const void* a);
int cmpFechas(const void* a, const void* b);
int cmpEmpl(const void* a, const void* b);
void incrSueldoEmpl(void* elem, void* datos);
int compararInt (const void* a, const void* b);
void imprimirInt (const void* a);


int main()
{
    // Change the code page to support spanish characters in Windows terminal
    // system("chcp 65001 > nul");

//     Vector miVec;
//     if(!vectorCrear(&miVec, sizeof(Empleado)))
//     {
//         return SIN_MEM;
//     }

//     srand(time(NULL));
// //    Fecha f = {1, 5, 2025};
//     Empleado empl;

//     empl.legajo = 1;
//     strcpy(empl.apynom, "Juan Perez");
//     empl.sueldo = 100000;
//     vectorInsertarAlFinal(&miVec, &empl);

//     empl.legajo = 2;
//     strcpy(empl.apynom, "Roberto Rodriguez");
//     empl.sueldo = 200000;
//     vectorInsertarAlFinal(&miVec, &empl);

//     empl.legajo = 3;
//     strcpy(empl.apynom, "Belen Berardi");
//     empl.sueldo = 300000;
//     vectorInsertarAlFinal(&miVec, &empl);

//     Empleado emplABuscar;
//     emplABuscar.legajo = 1;

//     int pos = vectorOrdBuscar(&miVec, &emplABuscar, cmpEmpl);
//     // int pos = vectorDesordBuscar(&miVec, &emplABuscar, cmpEmpl);

//     if(pos == -1)
//     {
//         puts("Empleado no encontrado");
//         return 1;
//     }

//     printf("Posicion: %d\n", pos);
//     printf("Nombre: %s\n", emplABuscar.apynom);


    Vector vec;
    VectorIterador it;

    vectorCrear(&vec, sizeof(int));
    vectorIteradorCrear(&it, &vec);

    int elem;
    int* elemP;

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        elem = rand() % 100;
        vectorInsertarAlFinal(&vec, &elem);
    }

    vectorMostrar(&vec, imprimirInt);
    printf("\n");

    elemP = vectorIteradorPrimero(&it);

    while (!vectorIteradorFin(&it)) {
        *(elemP) += 1;
        elemP = vectorIteradorSiguiente(&it);
    }

    printf("\n");

    vectorMostrar(&vec, imprimirInt);

    vectorDestruir(&vec);


    // puts("Antes de ordenar:");
    // vectorMostrar(&miVec, imprimirFecha);

    // time_t segIni = time(NULL);

    // vectorOrdenar(&miVec, QSORT, cmpFechas);

    // time_t segFin = time(NULL);

    // printf("Tiempo de ordenamiento: %ld\n", segFin - segIni);

    // puts("Después de ordenar:");
    // vectorMostrar(&miVec, imprimirFecha);

    // puts("Antes:");
    // vectorMostrar(&miVec, imprimirEmpleado);

    // float porcIncrSueldo = 10;

    // //vectorRecorrer(&miVec, incrSueldoEmpl, &porcIncrSueldo);

    // puts("Despues:");
    // //vectorMostrar(&miVec, imprimirEmpleado);

    // VectorIterador it;
    // vectorIteradorCrear(&it, &miVec);

    // Empleado* pEmpl = vectorIteradorPrimero(&it);

    // while (!vectorIteradorFin(&it)) {
    //     printf("%8d %-20s %11.2f\n", pEmpl->legajo, pEmpl->apynom, pEmpl->sueldo);
    //     pEmpl = vectorIteradorSiguiente(&it);
    // }

    // vectorDestruir(&miVec);

    return 0;
}


void imprimirFecha(const void* a)
{
    const Fecha* f = a;
    printf("%02d/%02d/%4d\n", f->d, f->m, f->a);
}


void imprimirEmpleado(const void* a)
{
    const Empleado* empl = a;
    printf("%8d %-20s %11.2f\n", empl->legajo, empl->apynom, empl->sueldo);
}


int cmpFechas(const void* a, const void* b)
{
    const Fecha* f1 = a;
    const Fecha* f2 = b;
    return (f1->a * 10000 + f1->m * 100 + f1->d) - (f2->a * 10000 + f2->m * 100 + f2->d);
}


int cmpEmpl(const void* a, const void* b)
{
    const Empleado* e1 = a;
    const Empleado* e2 = b;
    return e1->legajo - e2->legajo;
}


void incrSueldoEmpl(void* elem, void* datos)
{
    Empleado* empl = elem;
    float porcIncrSueldo = *(float*)datos;
    empl->sueldo = empl->sueldo + empl->sueldo * porcIncrSueldo / 100;
}

int compararInt (const void* a, const void* b) {
    const int* n1 = a;
    const int* n2 = b;

    return *n1 - *n2;
}

void imprimirInt (const void* a) {
    const int* n1 = a;

    printf("%d, ", *n1);
}
