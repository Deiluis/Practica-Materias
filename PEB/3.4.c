#include <stdio.h>
#include <string.h>

int ingIntMayA (int);
float ingFloatMayA (float);
int buscarCod (char[][4], int, char[]);
int ingProds (char[][4], float[], int);
void ingVentas (char[][4], float[], int[], int);
void calcRecaudacion (float[], int[], int);
int buscarMin (int[], int);
void mostrarProdVal (char[][4], int[], int, int);
void ordenar (char[][4], float[], int);
void listar (char[][4], float[], int);

int main () {
    int cant, min, vVentas[50] = {0};
    char vCod[50][4];
    float vPrecio[50];

    cant = ingProds(vCod, vPrecio, 50);

    if (cant > 0) {
        ingVentas(vCod, vPrecio, vVentas, cant);
        calcRecaudacion(vPrecio, vVentas, cant);
        min = buscarMin(vVentas, cant);
        mostrarProdVal(vCod, vVentas, cant, min);
        ordenar(vCod, vPrecio, cant);
        listar(vCod, vPrecio, cant);
    } else {
        printf("No se cargaron productos");
    }

    return 0;
}

int ingIntMayA (int limi) {
    int dato;
    
    do {
        scanf("%d", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi);

    return dato;
}

float ingFloatMayA (float limi) {
    float dato;
    
    do {
        scanf("%f", &dato);

        if (dato <= limi)
            printf("Dato invalido, reingresar: ");
            
    } while (dato <= limi);

    return dato;
}

int buscarCod (char vCod[][4], int tam, char cod[]) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (strcmpi(vCod[i], cod) == 0)
            pos = i;
        else
            i++;
    }

    return pos;
}

int ingProds (char vCod[][4], float vPrecio[], int tam) {
    int cant = 0, pos;
    char cod[4];
    float precio;

    printf("Registro de productos.\n\n");
    printf("Ingresa el codigo del primer producto a registrar (hasta 3 caracteres), 'FIN' para terminar: ");
    fflush(stdin);
    gets(cod);

    while (strcmpi(cod, "FIN") != 0 && cant < tam) {
        pos = buscarCod(vCod, cant, cod);

        if (pos == -1) {
            printf("Ingresa el precio unitario del producto (real mayor a 0): ");
            precio = ingFloatMayA(0);

            strcpy(vCod[cant], cod);
            vPrecio[cant] = precio;
            cant++;
        } else {
            printf("El codigo de producto que se intenta registrar ya existe, reintentar.\n");
        }

        if (cant < tam) {
            printf("Ingresa el codigo del siguiente producto a registrar (hasta 3 caracteres), 'FIN' para terminar: ");
            fflush(stdin);
            gets(cod);
        }  
    }

    return cant;
}

void ingVentas (char vCod[][4], float vPrecio[], int vVentas[], int tam) {
    int unidades, pos;
    char cod[4];
    
    printf("Se ingresaran las ventas registradas en el dia.\n\n");
    printf("Ingresa la cantidad de unidades vendidas de una venta (mayor a 0, o 0 para terminar): ");
    unidades = ingIntMayA(-1);

    while (unidades > 0) {
        printf("Ingresa el codigo del producto vendido (3 caracteres): ");
        fflush(stdin);
        gets(cod);

        pos = buscarCod(vCod, tam, cod);

        if (pos != -1)
            vVentas[pos] += unidades;
        else
            printf("No se encontro el producto con el codigo ingresado.\n");

        printf("Ingresa la cantidad de unidades vendidas de la siguiente venta (mayor a 0, o 0 para terminar): ");
        unidades = ingIntMayA(-1);
    }
}

void calcRecaudacion (float vPrecio[], int vVentas[], int tam) {
    float rec = 0;
    int i;

    for (i = 0; i < tam; i++)
        rec += vVentas[i] * vPrecio[i];

    printf("La recaudacion total del dia fue de $%.2f.\n", rec);
}

int buscarMin (int vVentas[], int tam) {
    int i, min = vVentas[0];

    for (i = 1; i < tam; i++) {
        if (vVentas[i] < min)
            min = vVentas[i];
    }

    return min;
}

void mostrarProdVal (char vCod[][4], int vVentas[], int tam, int val) {
    int i;

    printf("Los productos de menor venta de unidades fueron: ");

    for (i = 0; i < tam; i++) {
        if (vVentas[i] == val)
            printf("%s, ", vCod[i]);
    }
}

void ordenar (char vCod[][4], float vPrecio[], int tam) {
    int i, j;
    char auxCod[4];
    float auxPrecio;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam -1 -i; j++) {
            if (strcmpi(vCod[j], vCod[j+1]) > 0) {

                strcpy(auxCod, vCod[j+1]);
                strcpy(vCod[j+1], vCod[j]);
                strcpy(vCod[j], auxCod);

                auxPrecio = vPrecio[j+1];
                vPrecio[j+1] = vPrecio[j];
                vPrecio[j] = auxPrecio;
            }
        }
    }
}

void listar (char vCod[][4], float vPrecio[], int tam) {
    int i;

    printf("Listado de productos en orden alfabetico:\n");
    printf("Codigo\t\tPrecio\n");

    for (i = 0; i < tam; i++)
        printf("%s\t\t$%.2f\n", vCod[i], vPrecio[i]);
}