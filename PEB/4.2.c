#include <stdio.h>
#define TAM 3

typedef struct {
    int cod;
    float precio;
    int stock;
} TMed;

int ingIntEntre(int, int, int);
int ingIntMayA(int);
float ingFloatMayA(float);
int buscarMed(TMed[], int, int);
void ingreso(TMed[], int);
void busquedaMedi(TMed[], int);
void informe(TMed[], int);

int main () {

    TMed vMeds[TAM];
    
    ingreso(vMeds, TAM);
    busquedaMedi(vMeds, TAM);
    informe(vMeds, TAM);

    return 0;
}

int ingIntEntre(int limi, int lims, int cf) {
    int dato;

    do {
        scanf("%d", &dato);

        if ((dato < limi || dato > lims) && dato != cf)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato != cf);

    return dato;
}

int ingIntMayA(int limi) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

float ingFloatMayA(float limi) {
    float dato;

    do {
        scanf("%f", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

int buscarMed(TMed vMeds[], int tam, int cod) {
    int i = 0, pos = -1;
    
    while (pos == -1 && i < tam) {
        if (vMeds[i].cod == cod)
            pos = i;
        else
            i++;
    }

    return pos;
}

void ingreso(TMed vMeds[], int tam) {
    int i, cod, pos, stock;
    float precio;

    printf("Se ingresaran los datos de los %d medicamentos.\n\n", tam);

    for (i = 0; i < tam; i++) {
        printf("Ingrese los datos del medicamento %d:\n", i+1);

        printf("Ingresa el codigo de medicamento (3 cifras): ");
        do {
            cod = ingIntEntre(100, 999, 999);
            pos = buscarMed(vMeds, i, cod);

            if (pos != -1)
                printf("Ya existe un medicamento registrado con este codigo, reingresar: ");
            
        } while (pos != -1);

        printf("Ingresa el precio del medicamento (real mayor a 0): ");
        precio = ingFloatMayA(0);

        printf("Ingresa el stock del medicamento (entero positivo o 0): ");
        stock = ingIntMayA(-1);

        vMeds[i].cod = cod;
        vMeds[i].precio = precio;
        vMeds[i].stock = stock;
    }

    printf("\n");
}

void busquedaMedi(TMed vMeds[], int tam) {
    int cod, pos;

    printf("Informe de precio de medicamento por su codigo.\n\n");
    printf("Ingresa el codigo de un medicamento para conocer su precio (3 cifras), o 0 para terminar: ");
    cod = ingIntEntre(100, 999, 0);

    while (cod > 0) {
        pos = buscarMed(vMeds, tam, cod);

        if (pos != -1)
            printf("Precio: $%.2f\n", vMeds[pos].precio);
        else
            printf("No se encontro un medicamento con este codigo.");
        
        printf("Ingresa el codigo de otro medicamento para conocer su precio (3 cifras), o 0 para terminar: ");
        cod = ingIntEntre(100, 999, 0);
    }

    printf("\n");
}

void informe(TMed vMeds[], int tam) {
    int i, cant = 0;

    printf("Los medicamentos con un stock inferior a 10 unidades poseen los siguientes codigos: ");

    for (i = 0; i < tam; i++) {
        if (vMeds[i].stock < 10) {
            printf("%d, ", vMeds[i].cod);
            cant++;
        }
    }

    if (cant == 0)
        printf("N/A");
}