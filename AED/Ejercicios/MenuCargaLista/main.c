#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../TDALista/TDALista.h"

#define V_LISTA_SIMPLE 1
#define V_LISTA_COMPUESTA 2
#define C_DATO_SIMPLE 3
#define C_DATO_COMPUESTO 4
#define ORD_LISTA_SIMPLE 5
#define ORD_LISTA_COMPUESTA 6
#define SALIR 7

#define SIN_DUP 1
#define CON_DUP 2

#define COD 1
#define DESC 2
#define CANT 3

#define TAM_DESC 100
#define TAM_LINEA 1024

#define ARCH_TXT 1
#define ARCH_BIN 2

typedef struct {
    int cod;
    char desc[TAM_DESC +1];
    int cant;
} tVenta;

typedef bool (*TxtABin) (const char* buffer, void* reg);

bool intTxtVABin (const char* buffer, void* reg);
bool generarVentasBin (const char* nomArch);

void mostrarMenu();
void mostrarSubMenuDup();
void mostrarSubMenuCriterio();

int ingrYValidarInt(int limI, int limS);
int ingrYValidarIntMayorA(int limI);
void leerStr(char* str, int tam);

void cargarDatoCompuesto(tVenta* v);

void mostrarSimple (const void* elem);
void mostrarCompuesto (const void* elem);
int compararSimple (const void* e1, const void* e2);
int compararCompuestoCod (const void* e1, const void* e2);
int compararCompuestoDesc (const void* e1, const void* e2);
int compararCompuestoCant (const void* e1, const void* e2);
void accionCompuesto (const void* e1, const void* e2);

bool cargarListaDeArchivoBin (tLista* lista, const char* nomArch, size_t tamReg);
bool cargarListaDeArchivoTxt (tLista* lista, const char* nomArch, size_t tamReg, TxtABin txtABin);

// MenuCargaLista.exe simp.txt comp.dat
int main (int argc, char* argv[]) {

    tLista listaS, listaC;
    int op, datoS;
    tVenta datoC;
    Cmp funcComp = compararCompuestoCod;

    if (!generarVentasBin(argv[ARCH_BIN]))
        printf("Error creando %s.\n", argv[ARCH_BIN]);

    crearLista(&listaS);
    crearLista(&listaC);

    if (!cargarListaDeArchivoTxt(&listaS, argv[ARCH_TXT], sizeof(int), intTxtVABin)) {
        printf("Error cargando la lista de datos simples, vaciando...\n");
        vaciarLista(&listaS);
    }

    if (!cargarListaDeArchivoBin(&listaC, argv[ARCH_BIN], sizeof(tVenta))) {
        printf("Error cargando la lista de datos compuestos, vaciando...\n");
        vaciarLista(&listaC);
    }

    mostrarMenu();
    op = ingrYValidarInt(V_LISTA_SIMPLE, SALIR);

    while (op != SALIR) {

        switch (op) {
            case V_LISTA_SIMPLE:
                printf("\n");
                mostrarLista(&listaS, mostrarSimple);
                printf("\n\n");
                break;

            case V_LISTA_COMPUESTA:
                printf("\n");
                mostrarLista(&listaC, mostrarCompuesto);
                printf("\n\n");
                break;

            case C_DATO_SIMPLE:
                mostrarSubMenuDup();
                op = ingrYValidarInt(SIN_DUP, CON_DUP);

                printf("Ingresa el dato a cargar: ");

                fflush(stdin);

                while (!scanf("%d", &datoS)) {
                    printf("Dato invalido, reingresar: ");
                    fflush(stdin);
                }

                printf("\n");

                if (!ponerEnListaEnOrden(&listaS, &datoS, sizeof(datoS), op == CON_DUP, compararSimple, compararSimple, NULL))
                    printf("Error cargando el elemento en la lista, puede ya no haber mas memoria o estar duplicado.\n");

                printf("\n");
                mostrarLista(&listaS, mostrarSimple);
                printf("\n\n");

                break;

            case C_DATO_COMPUESTO:
                mostrarSubMenuDup();
                op = ingrYValidarInt(SIN_DUP, CON_DUP);
                cargarDatoCompuesto(&datoC);

                printf("\n");

                if (!ponerEnListaEnOrden(&listaC, &datoC, sizeof(datoC), op == CON_DUP, compararCompuestoCod, funcComp, accionCompuesto))
                    printf("Error cargando el elemento en la lista, puede ya no haber mas memoria o estar duplicado por su clave.\n");

                printf("\n");
                mostrarLista(&listaC, mostrarCompuesto);
                printf("\n\n");

                break;

            case ORD_LISTA_SIMPLE:
                ordenarLista(&listaS, compararSimple, SELECCION);
                printf("\n");
                mostrarLista(&listaS, mostrarSimple);
                printf("\n\n");
                break;

            case ORD_LISTA_COMPUESTA:
                printf("\n");
                mostrarSubMenuCriterio();
                op = ingrYValidarInt(COD, CANT);

                funcComp = op == COD
                ? compararCompuestoCod
                : (
                    op == DESC
                    ? compararCompuestoDesc
                    : compararCompuestoCant
                );

                printf("\n");

                ordenarLista(&listaC, funcComp, SELECCION);

                printf("\n");
                mostrarLista(&listaC, mostrarCompuesto);
                printf("\n\n");

                break;
        }

        mostrarMenu();
        op = ingrYValidarInt(V_LISTA_SIMPLE, SALIR);
    }

    return 0;
}

void mostrarMenu() {
    printf("Operaciones\n");
    printf("--------------------------------------\n");
    printf("1. Visualizar lista simple (enteros)\n");
    printf("2. Visualizar lista compuesta (ventas)\n");
    printf("3. Cargar dato simple\n");
    printf("4. Cargar dato compuesto\n");
    printf("5. Ordenar lista simple\n");
    printf("6. Ordenar lista compuesta\n");
    printf("7. Salir\n");
    printf("\n");
    printf("Operacion: ");
}

void mostrarSubMenuDup() {
    printf("Cargar con o sin duplicados?\n");
    printf("--------------------------------------\n");
    printf("1. Sin duplicados\n");
    printf("2. Con duplicados\n");
    printf("\n");
    printf("Operacion: ");
}

void mostrarSubMenuCriterio() {
    printf("Criterio de ordenamiento?\n");
    printf("--------------------------------------\n");
    printf("1. Codigo de producto\n");
    printf("2. Descripcion de producto\n");
    printf("3. Cantidad vendida\n");
    printf("\n");
    printf("Operacion: ");
}

int ingrYValidarInt(int limI, int limS) {
    int dato;

    do  {
        fflush(stdin);

        while (!scanf("%d", &dato)) {
            printf("Dato invalido, reingresar: ");
            fflush(stdin);
        }

        if (dato < limI || dato > limS)
            printf("Dato invalido, reingresar: ");

    } while (dato < limI || dato > limS);

    return dato;
}

int ingrYValidarIntMayorA(int limI) {
    int dato;

    do  {
        fflush(stdin);

        while (!scanf("%d", &dato)) {
            printf("Dato invalido, reingresar: ");
            fflush(stdin);
        }

        if (dato <= limI)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limI);

    return dato;
}

void leerStr(char* str, int tam) {

    char* act;

    fflush(stdin);
    fgets(str, tam, stdin);

    // Limpia el buffer si quedan caracteres.
    fflush(stdin);

    act = strchr(str, '\n');

    if (act)
        *act = '\0';
}

void cargarDatoCompuesto(tVenta* v) {

    int cod, cant;
    char desc[TAM_DESC +1];

    printf("Ingresa el codigo de producto (entero entre 1 y 200): ");
    cod = ingrYValidarInt(1, 200);
    printf("\n");

    printf("Ingresa la descripcion del producto (hasta 100 caracteres): ");
    leerStr(desc, TAM_DESC +1);
    printf("\n");

    printf("Ingresa la cantidad vendida (mayor a 0): ");
    cant = ingrYValidarIntMayorA(0);
    printf("\n");

    v -> cod = cod;
    strncpy(v -> desc, desc, TAM_DESC +1);
    v -> cant = cant;
}

void mostrarSimple (const void* elem) {
    int* num = (int*) elem;
    printf("%d ", *num);
}

int compararSimple (const void* e1, const void* e2) {
    int* n1 = (int*) e1;
    int* n2 = (int*) e2;

    return *n1 - *n2;
}

void mostrarCompuesto (const void* elem) {
    tVenta* venta = (tVenta*) elem;

    printf("Codigo de producto: %d\n", venta -> cod);
    printf("Descripcion: %s\n", venta -> desc);
    printf("Cantidad vendida: %d\n", venta -> cant);
    printf("\n");
}

int compararCompuestoCod (const void* e1, const void* e2) {
    tVenta* v1 = (tVenta*) e1;
    tVenta* v2 = (tVenta*) e2;

    return v1 -> cod - v2 -> cod;
}

int compararCompuestoDesc (const void* e1, const void* e2) {
    tVenta* v1 = (tVenta*) e1;
    tVenta* v2 = (tVenta*) e2;

    return strcmp(v1 -> desc, v2 -> desc);
}

int compararCompuestoCant (const void* e1, const void* e2) {
    tVenta* v1 = (tVenta*) e1;
    tVenta* v2 = (tVenta*) e2;

    return v1 -> cant - v2 -> cant;
}

void accionCompuesto (const void* e1, const void* e2) {
    tVenta* v1 = (tVenta*) e1;
    tVenta* v2 = (tVenta*) e2;

    v1 -> cant += v2 -> cant;
}

bool cargarListaDeArchivoBin (tLista* lista, const char* nomArch, size_t tamReg) {

    FILE* archBin = fopen(nomArch, "rb");
    void* reg;
    bool err = false;

    if (!archBin)
        return false;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(archBin);
        return false;
    }

    while (!err && fread(reg, tamReg, 1, archBin))
        err = !ponerEnListaAlFinal(lista, reg, tamReg, true, NULL);

    fclose(archBin);
    free(reg);

    return !err;
}

bool cargarListaDeArchivoTxt (tLista* lista, const char* nomArch, size_t tamReg, TxtABin txtABin) {

    FILE* archTxt = fopen(nomArch, "rt");
    void* reg;
    char* buffer;
    char* pos;
    bool err = false;

    if (!archTxt)
        return false;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(archTxt);
        return false;
    }

    buffer = malloc(TAM_LINEA +1);

    if (!buffer) {
        free(reg);
        fclose(archTxt);
        return false;
    }

    pos = fgets(buffer, TAM_LINEA, archTxt);

    while (!err && pos != NULL) {
        err = !txtABin(buffer, reg);

        if (!err)
            err = !ponerEnListaAlFinal(lista, reg, tamReg, true, NULL);

        pos = fgets(buffer, TAM_LINEA, archTxt);
    }

    fclose(archTxt);
    free(reg);
    free(buffer);

    return !err;
}

bool intTxtVABin (const char* buffer, void* reg) {

    char* act = strchr(buffer, '\n');

    if (!act)
        return false;

    *act = '\0';

    sscanf(buffer, "%d", (int*) reg);
    return true;
}

bool generarVentasBin (const char* nomArch) {

    tVenta ventas[] = {
        {1, "Producto E", 5},
        {2, "Producto J", 12},
        {3, "Producto H", 8},
        {4, "Producto D", 20},
        {5, "Producto A", 15},
        {6, "Producto B", 3},
        {7, "Producto G", 9},
        {8, "Producto C", 14},
        {9, "Producto I", 7},
        {10, "Producto F", 11}
    };

    FILE* arch = fopen(nomArch, "wb");

    if (!arch)
        return false;

    fwrite(ventas, sizeof(tVenta), sizeof(ventas) / sizeof(tVenta), arch);
    fclose(arch);

    return true;
}