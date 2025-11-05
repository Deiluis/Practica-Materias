#include <stdio.h>
#include <stdlib.h>
//#include "../PilaEstatica/PilaEstatica.h"
#include "../PilaDinamica/PilaDinamica.h"
#include "../ColaEstatica/ColaEstatica.h"
//#include "../ColaDinamica/ColaDinamica.h"
#include "../ListaSimple/ListaSimple.h"
#include "../ListaDoble/ListaDoble.h"
#include "../Arbol/Arbol.h"
#include "../Indice/Indice.h"
#include <string.h>

#define TAM_NOM 50

typedef struct {
    int cod;
    char nombre[TAM_NOM +1];
    float sueldo;
    bool activo;
} tEmpleado;

typedef struct {
    int cod, pos;
} tEmpleadoIdx;

void probarPila();
void probarCola();
void probarLista();
void probarListaDoble();
void probarArbolInt();
void probarArbolEmpl();
void probarIndiceEmpl();

void mostrarInt (void* elem, void* extra);
void sumarInt (void* elem, void* dst);
int compararInt (const void* e1, const void* e2);
bool condicionInt (const void* elem);

void mostrarEmpl (void* elem, void* extra);
void sumarSueldoEmpl (void* elem, void* dst);
int compararEmpl (const void* e1, const void* e2);
int compararNomEmpl (const void* e1, const void* e2);
bool condicionEmpl (const void* elem);
bool convEmplAIdx (void* idx, const void* reg, int pos);
int compararEmplIdx (const void* e1, const void* e2);
void mostrarEmplIdx (void* elem, void* extra);
int generarArchEmpl (const char* nomArch);

int main() {

    int tam = 50;
    int num = 123456789;
    char buffer[tam +1];

    snprintf(buffer, tam, "%d", num);
    buffer[tam] = '\0';


    printf("%s", buffer);

    // probarCola();

    return 0;
}

void probarPila() {
    tPila pila;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int dato;
    int* i;
    bool memLibre = true;

    crearPila(&pila);

    i = nums;
    memLibre = apilar(&pila, i, sizeof(int));
    i++;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = apilar(&pila, i, sizeof(int));
        i++;
    }

    if (!memLibre) {
        vaciarPila(&pila);
        printf("Memoria insuficiente, vaciando pila...\n");
    }

    while (desapilar(&pila, &dato, sizeof(int)))
        printf("%d, ", dato);

    if (verTope(&pila, &dato, sizeof(dato)))
        printf("Tope: %d\n", dato);
    else
        printf("Pila vacia\n");
}

void probarCola() {
    tCola cola;

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int dato;
    int* i;
    bool memLibre = true;

    crearCola(&cola);

    i = nums;
    memLibre = ponerEnCola(&cola, i, sizeof(int));
    i++;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = ponerEnCola(&cola, i, sizeof(int));
        i++;
    }

//    if (!memLibre) {
//        vaciarCola(&cola);
//        printf("Memoria insuficiente, vaciando cola...\n");
//    }

    while (sacarDeCola(&cola, &dato, sizeof(int)))
        printf("%d, ", dato);

    if (verPriDeCola(&cola, &dato, sizeof(dato)))
        printf("Tope: %d\n", dato);
    else
        printf("Cola vacia\n");
}

void probarLista() {
    tLista lista, listaNeg;

    int nums[] = { 8, 15, 3, 4, 11, 5, 6, -1, 7, 2, 15, 10, 6, 1, 12, 14, 9, -3 };
    //int dato;
    int* i;
    bool memLibre = true;
    //int cod = TODO_OK;

    crearLista(&lista);
    crearLista(&listaNeg);

    i = nums;

    while (memLibre && i < nums + (sizeof(nums) / sizeof(int))) {
        memLibre = ponerEnListaAlFinal(&lista, i, sizeof(int));

        // cod = ponerEnListaEnOrden(&lista, i, sizeof(int), compararInt, NULL);

        // if (cod == DUPLICADO)
        //     fprintf(stderr, "Error, el elemento %d ya se encuentra en la lista.\n", *i);

        i++;
    }

    // if (cod == SIN_MEM) {
    //     vaciarLista(&lista);
    //     fprintf(stderr, "Memoria insuficiente, vaciando lista...\n");
    // }

    // if (!memLibre) {
    //     vaciarLista(&lista);
    //     printf("Memoria insuficiente, vaciando lista...\n");
    // }

    recorrerListaDesdeFinal(&lista, mostrarInt);
    printf("\n");
    // ordenarLista(&lista, compararInt);
    // recorrerLista(&lista, mostrarInt);
    // printf("\n");
    // filtrarLista(&lista, condicionInt);
    // recorrerLista(&lista, mostrarInt);
    // printf("\n");

    // reducirLista(&lista, &suma, sumarInt);
    // printf("Sumatoria: %d", suma);

    // cargarListaNoFiltrada(&lista, &listaNeg, condicionInt);
    // recorrerLista(&lista, mostrarInt);
    // printf("\n");
    // recorrerLista(&listaNeg, mostrarInt);
    // printf("\n");

    // while (sacarDeListaAlFinal(&lista, &dato, sizeof(int)))
    //     printf("%d, ", dato);

    // if (listaVacia(&lista))
    //     printf("Lista vacia.\n");

    // if (verTope(&pila, &dato, sizeof(dato)))
    //     printf("Tope: %d\n", dato);
    // else
    //     printf("Pila vacia\n");
}

void probarListaDoble() {

    tListaD lista;

    int nums[] = { 8, 15, 3, 4, 11, 5, 6, -1, 7, 2, 10, 1, 12, 14, 9, -3 };
    int* i;
    int cod = TODO_OK;

    crearListaD(&lista);

    i = nums;

    while (cod == TODO_OK && i < nums + (sizeof(nums) / sizeof(int))) {
        cod = ponerEnListaDAlFinal(&lista, i, sizeof(int));

        if (cod == DUPLICADO)
            fprintf(stderr, "Error, el elemento %d ya se encuentra en la lista.\n", *i);

        i++;
    }

    if (cod == SIN_MEM) {
        fprintf(stderr, "Error, memoria insuficiente, vaciando lista...\n");
        vaciarListaD(&lista);
    }

    recorrerListaDDesdeInicio(&lista, mostrarInt, NULL);
    printf("\n");
    recorrerListaDDesdeFinal(&lista, mostrarInt, NULL);
    printf("\n\n");

    ordenarListaD(&lista, compararInt);

    recorrerListaDDesdeInicio(&lista, mostrarInt, NULL);
    printf("\n");

    printf("Lista vacia? %s", listaDVacia(&lista) ? "Si" : "No");
}

void probarArbolEmpl() {

    tArbol arbol;

    // tEmpleado empls[] = {
    //     {3, "Martin", 3000},
    //     {1, "Juan", 11000},
    //     {2, "Alberto", 20000},
    //     {4, "Maria", 1000},
    //     {5, "Luis", 2000},
    // };
    // tEmpleado* i;

    tEmpleado busq = {1, "", 0};

    // int cod = TODO_OK;

    crearArbol(&arbol);

    // i = empls;

    // while (cod == TODO_OK && i < (empls + sizeof(empls) / sizeof(tEmpleado))) {

    //     cod = ponerEnArbolI(&arbol, i, sizeof(*i), compararEmpl, NULL);

    //     if (cod == SIN_MEM) {
    //         printf("Error creando elemento\n");
    //         mostrarEmpl(i);
    //         printf("memoria insuficiente.\n");
    //     }

    //     if (cod == DUPLICADO) {
    //         printf("Error creando elemento\n");
    //         mostrarEmpl(i);
    //         printf("esta duplicado.\n");
    //     }

    //     i++;
    // }

    //recorrerHastaNivel(&arbol, 3, mostrarInt);
    // printf("%d\n", alturaArbol(&arbol));

    //vaciarArbol(&arbol);

    if (generarArchEmpl("empleados.dat") == TODO_OK) {
        if (cargarArbolDeArchBin(&arbol, "empleados.dat", sizeof(tEmpleado), compararEmpl, NULL) != TODO_OK)
            printf("Error cargando el arbol.\n");
    } else
        printf("Error creando el archivo de empleados.\n");

    if (arbolVacio(&arbol))
        printf("Arbol vacio.\n");

    recorrerArbolR(&arbol, INORDEN, mostrarEmpl);
    printf("\n");

    // printf("El arbol tiene %d nodos.\n", cantNodosArbolR(&arbol));
    // printf("El arbol tiene %d hojas.\n", cantHojasArbolR(&arbol));
    // printf("El arbol tiene %d no hojas.\n", cantNoHojasArbolR(&arbol));
    // printf("Altura del arbol: %d\n", alturaArbol(&arbol));
    // printf("Nivel del arbol: %d\n", nivelArbol(&arbol));
    // printf("Arbol completo?: %s\n", esArbolCompleto(&arbol) ? "Si" : "No");
    // printf("\n");
    // printf("%d empleados tienen un sueldo mayor a los $%.2f\n", cantNodosCond(&arbol, condicionEmpl), 10000.0f);

    // if (buscarClaveMayorArbol(&arbol, &busq, sizeof(busq)))
    //     mostrarEmpl(&busq);
    // else
    //     printf("Clave mayor no encontrada.\n");

    // if (buscarClaveMenorArbol(&arbol, &busq, sizeof(busq)))
    //     mostrarEmpl(&busq);
    // else
    //     printf("Clave menor no encontrada.\n");

    // if (buscarPorNoClaveArbol(&arbol, &busq, sizeof(busq), compararNomEmpl))
    //     mostrarEmpl(&busq);
    // else
    //     printf("Empleado no encontrado.\n");

    printf("El arbol tiene %d nodos.\n", cantNodosArbolR(&arbol));
    printf("El arbol tiene %d hojas.\n", cantHojasArbolR(&arbol));
    printf("El arbol tiene %d no hojas.\n", cantNoHojasArbolR(&arbol));
    printf("Altura del arbol: %d\n", alturaArbol(&arbol));
    printf("Nivel del arbol: %d\n", nivelArbol(&arbol));
    printf("Arbol completo?: %s\n", esArbolCompleto(&arbol) ? "Si" : "No");
    printf("Arbol balanceado?: %s\n", esArbolBalanceado(&arbol) ? "Si" : "No");
    printf("Arbol AVL?: %s\n", esArbolAVL(&arbol) ? "Si" : "No");
    printf("\n");

    if (sacarDeArbol(&arbol, &busq, sizeof(busq), compararEmpl)) {
        printf("Empleado obtenido:\n");
        mostrarEmpl(&busq, NULL);
        printf("\n");
    } else
        printf("Error al eliminar al empleado.\n");

    recorrerArbolR(&arbol, INORDEN, mostrarEmpl);
    printf("\n");
}

void probarArbolInt() {

    tArbol arbol;

    //int nums[] = {10, 5, 3, 15, 1, 2, 32, 11};
    int nums[] = {10, 7, 18, 17, 21, 19, 1, 8, -1, 2, 3, 9};
    int* i;

    int cod = TODO_OK;

    crearArbol(&arbol);

    i = nums;

    while (cod == TODO_OK && i < (nums + sizeof(nums) / sizeof(int))) {

        cod = ponerEnArbolI(&arbol, i, sizeof(*i), compararInt, NULL);

        if (cod == SIN_MEM)
            printf("Error creando elemento %d, memoria insuficiente\n", *i);

        if (cod == DUPLICADO)
            printf("Error creando elemento %d, esta duplicado\n", *i);

        i++;
    }

    //recorrerHastaNivel(&arbol, 3, mostrarInt);
    // printf("%d\n", alturaArbol(&arbol));

    // vaciarArbol(&arbol);

    if (arbolVacio(&arbol))
        printf("Arbol vacio.\n");

    recorrerArbolR(&arbol, INORDEN, mostrarInt);
    printf("\n");

    printf("El arbol tiene %d nodos.\n", cantNodosArbolR(&arbol));
    printf("El arbol tiene %d hojas.\n", cantHojasArbolR(&arbol));
    printf("El arbol tiene %d no hojas.\n", cantNoHojasArbolR(&arbol));
    printf("Altura del arbol: %d\n", alturaArbol(&arbol));
    printf("Nivel del arbol: %d\n", nivelArbol(&arbol));
    printf("Arbol completo?: %s\n", esArbolCompleto(&arbol) ? "Si" : "No");
    printf("Arbol balanceado?: %s\n", esArbolBalanceado(&arbol) ? "Si" : "No");
    printf("Arbol AVL?: %s\n", esArbolAVL(&arbol) ? "Si" : "No");
}

void probarIndiceEmpl() {

    tIndice idxEmpl;
    tEmpleadoIdx empl = { 2, 0 };
    int cod;

    crearIndice(&idxEmpl);

    // cod = generarIndice(
    //     &idxEmpl,
    //     "empleados.dat",
    //     "empleadosIdx.dat",
    //     sizeof(tEmpleado),
    //     sizeof(tEmpleadoIdx),
    //     convEmplAIdx,
    //     compararEmplIdx
    // );

    // printf("Codigo generacion idx: %d\n", cod);

    cod = cargarIndice(&idxEmpl, "empleadosIdx.dat", sizeof(tEmpleadoIdx));
    printf("Codigo carga idx: %d\n", cod);

    mostrarIndice(&idxEmpl, mostrarEmplIdx);

    if (buscarIndice(&idxEmpl, &empl, sizeof(empl), compararEmplIdx)) {
        mostrarEmplIdx(&empl, NULL);
    } else {
        printf("No encontrado en la busqueda\n");
    }

    if (sacarDeIndice(&idxEmpl, &empl, sizeof(empl), compararEmplIdx)) {
        mostrarEmplIdx(&empl, NULL);
    } else {
        printf("No encontrado en la eliminacion\n");
    }

    cod = guardarIndice(&idxEmpl, "empleadosIdx.dat", sizeof(tEmpleadoIdx));
    printf("Codigo guardado idx: %d\n", cod);

}

void sumarInt (void* elem, void* dst) {
    int* num = (int*) elem;
    int* suma = (int*) dst;

    *suma += *num;
}

void mostrarInt (void* elem, void* extra) {
    int* num = (int*) elem;
    printf("%d, ", *num);
}

int compararInt (const void* e1, const void* e2) {
    int* n1 = (int*) e1;
    int* n2 = (int*) e2;

    return *n1 - *n2;
}

bool condicionInt (const void* elem) {
    int* n1 = (int*) elem;
    return *n1 > 0;
}

void mostrarEmpl (void* elem, void* extra) {
    tEmpleado* empl = (tEmpleado*) elem;
    printf("%d\t%s\t$%.2f\t%s\n", empl -> cod, empl -> nombre, empl -> sueldo, empl -> activo ? "Activo" : "Inactivo");
}

void sumarSueldoEmpl (void* elem, void* dst) {
    tEmpleado* empl = (tEmpleado*) elem;
    float* sueldo = (float*) dst;
    *sueldo += empl -> sueldo;
}

int compararEmpl (const void* e1, const void* e2) {
    tEmpleado* empl1 = (tEmpleado*) e1;
    tEmpleado* empl2 = (tEmpleado*) e2;

    return empl1 -> cod - empl2 -> cod;
}

bool condicionEmpl (const void* elem) {
    tEmpleado* empl = (tEmpleado*) elem;
    return empl -> sueldo >= 10000;
}

int compararNomEmpl (const void* e1, const void* e2) {
    tEmpleado* empl1 = (tEmpleado*) e1;
    tEmpleado* empl2 = (tEmpleado*) e2;
    return strcmpi(empl1 -> nombre, empl2 -> nombre);
}

// Devuelve si debe incluirlo al indice.
bool convEmplAIdx (void* idx, const void* reg, int pos) {
    tEmpleadoIdx* emplIdx = (tEmpleadoIdx*) idx;
    tEmpleado* empl = (tEmpleado*) reg;

    // Esto realmente depende de la logica de negocio.
    if (!empl -> activo)
        return false;

    emplIdx -> cod = empl -> cod;
    emplIdx -> pos = pos;

    return true;
}

int compararEmplIdx (const void* e1, const void* e2) {
    tEmpleadoIdx* empl1 = (tEmpleadoIdx*) e1;
    tEmpleadoIdx* empl2 = (tEmpleadoIdx*) e2;

    return empl1 -> cod - empl2 -> cod;
}

void mostrarEmplIdx (void* elem, void* extra) {
    tEmpleadoIdx* empl = (tEmpleadoIdx*) elem;
    printf("%d\t%d\n", empl -> cod, empl -> pos);
}

int generarArchEmpl (const char* nomArch) {

    FILE* archBin = fopen(nomArch, "wb");

    if (!archBin)
        return ERR_ARCHIVO;

    tEmpleado empls[] = {
        {9, "Daniela", 15000, true},
        {3, "Martin", 3000, true},
        {4, "Maria", 1000, true},
        {10, "Josefa", 4700, true},
        {5, "Luis", 2000, true},
        {6, "Diego", 7000, false},
        {1, "Juan", 11000, true},
        {7, "Lucio", 3500, true},
        {8, "Martina", 3000, false},
        {2, "Alberto", 20000, true}
    };

    fwrite(empls, sizeof(tEmpleado), sizeof(empls) / sizeof(tEmpleado), archBin);
    fclose(archBin);

    return TODO_OK;
}
