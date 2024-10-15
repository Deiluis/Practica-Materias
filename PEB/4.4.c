#include <stdio.h>
#include <string.h>
#define CANT 5

typedef struct {
    int cod;
    char nombApe[51];
    int ventas;
    float totalFac;
} TCliente;

int ingIntVal(int, int);
float ingFloatMayA(float);
int buscarCliente(TCliente[], int, int);
void cargarClientes(TCliente[], int);
int ingVentas(TCliente[], int[], int);
void ventasXCliente(TCliente[], int);
void ventasXVend(int[], int);
void ordenar(TCliente[], int);
void listarClientes(TCliente[], int);

int main () {
    
    TCliente vClientes[CANT];
    int vVend[10] = {0};
    int ventasTot = 0;

    cargarClientes(vClientes, CANT);
    ventasTot = ingVentas(vClientes, vVend, CANT);

    if (ventasTot > 0) {
        ventasXCliente(vClientes, CANT);
        ventasXVend(vVend, 10);
        ordenar(vClientes, CANT);
        listarClientes(vClientes, CANT);
    } else {
        printf("No se registraron ventas.");
    }

    return 0;
}

int ingIntVal(int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato < limi || dato > lims)
            printf("Dato invalido, reingresar: ");

    } while (dato < limi || dato > lims);

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

int buscarCliente(TCliente vClientes[], int tam, int cod) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vClientes[i].cod == cod)
            pos = i;
        else
            i++;
    }

    return pos;
}

void cargarClientes(TCliente vClientes[], int tam) {
    int i, cod, pos;
    char nombApe[51];

    printf("Se cargaran los datos de los clientes.\n\n");

    for (i = 0; i < tam; i++) {
        printf("Ingresa los datos del cliente %d:\n", i+1);

        printf("Ingresa el codigo de cliente (4 cifras): ");
        do {
            cod = ingIntVal(1000, 9999);
            pos = buscarCliente(vClientes, tam, cod);

            if (pos != -1)
                printf("Ya existe un cliente con el codigo ingresado, reintentar: ");

        } while (pos != -1);

        printf("Ingresa el nombre y apellido del cliente (hasta 50 caracteres): ");
        fflush(stdin);
        gets(nombApe);

        vClientes[i].cod = cod;
        strcpy(vClientes[i].nombApe, nombApe);
        vClientes[i].ventas = 0;
        vClientes[i].totalFac = 0;

        printf("\n");
    }

    printf("\n");
}

int ingVentas(TCliente vClientes[], int vVend[], int tam) {
    int cod, pos, vend, ventas = 0;
    float importe;

    printf("Se registraran las ventas.\n\n");

    printf("Ingresa el codigo de cliente al que se le realizo la venta (4 cifras, o 999 para terminar): ");
    cod = ingIntVal(999, 9999);

    while (cod > 999) {
        pos = buscarCliente(vClientes, tam, cod);

        if (pos != -1) {
            printf("Ingresa el importe de la venta realizada: ");
            importe = ingFloatMayA(0);
            printf("Ingresa el codigo del vendedor que realizo la venta (1 al 10): ");
            vend = ingIntVal(1, 10);

            vVend[vend -1]++;
            vClientes[pos].ventas++;
            vClientes[pos].totalFac += importe;
            ventas++;
        } else {
            printf("No se encontro el cliente con el codigo especificado.\n");
        }

        printf("Ingresa el codigo de cliente al que se le realizo la venta (4 cifras, o 999 para terminar): ");
        cod = ingIntVal(999, 9999);
    }

    return ventas;
}

void ventasXCliente(TCliente vClientes[], int tam) {
    int i;

    printf("Ventas realizadas a cada cliente:\n");
    printf("Codigo\t\tCantidad\n");

    for (i = 0; i < tam; i++)
        printf("%d\t\t%d\n", vClientes[i].cod, vClientes[i].ventas);
}

void ventasXVend(int vVend[], int tam) {
    int i;

    printf("Ventas realizadas a por cada vendedor:\n");
    printf("Codigo\t\tCantidad\n");

    for (i = 0; i < tam; i++)
        printf("%d\t\t%d\n", i+1, vVend[i]);
}

void ordenar(TCliente vClientes[], int tam) {
    int i, j;
    TCliente aux;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam - 1 - i; j++) {
            if (vClientes[j].totalFac < vClientes[j+1].totalFac) {
                aux = vClientes[j+1];
                vClientes[j+1] = vClientes[j];
                vClientes[j] = aux;
            }
        }
    }
}

void listarClientes(TCliente vClientes[], int tam) {
    int i;

    printf("Total facturado a cada cliente:\n");
    printf("Codigo\t\tNombre y apellido\t\tTotal facturado\n");

    for (i = 0; i < tam; i++)
        printf("%d\t\t%s\t\t$%.2f\n", vClientes[i].cod, vClientes[i].nombApe, vClientes[i].totalFac);
}