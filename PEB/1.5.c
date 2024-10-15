#include <stdio.h>

int ingIntVal (int, int, int);
int ingIntMayA (int);
int buscarCod (int[], int, int);
void ordenarDec (int[], int[], int);
void ordenarCre (int[], int);
int buscarMin (int[], int);
void mostrarMins (int[], int, int);
void listarUnidades (int[], int[], int);
void cargarCods (int[], int);
int ingVentas(int[], int[], int[], int);

int main () {
    int vCod[15], vUnidades[15] = {0}, vVend[15] = {0};
    int huboVent, minV;

    cargarCods(vCod, 15);
    ordenarCre(vCod, 15);

    huboVent = ingVentas(vCod, vUnidades, vVend, 15);

    if (huboVent) {
        ordenarDec(vCod, vUnidades, 15);
        listarUnidades(vCod, vUnidades, 15);
        minV = buscarMin(vVend, 5);

        printf("Vendedores con menor cantidad de ventas: ");
        mostrarMins(vVend, 5, minV);
    } else {
        printf("No se ingresaron ventas.");
    }

    return 0;
}

int ingIntVal (int limi, int lims, int cf) {
    int dato;

    do {
        scanf("%d", &dato);
        
        if ((dato < limi || dato > lims) && dato != cf)
            printf("Dato invalido, reingresar: ");

    } while ((dato < limi || dato > lims) && dato != cf);

    return dato;
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

int buscarCod (int vCod[], int tam, int cod) {
    int pos = -1, i = 0;

    while (pos == -1 && i < tam) {
        if (vCod[i] == cod)
            pos = i;
        else
            i++;
    }

    return pos;
}

void ordenarDec (int vCod[], int vUnidades[], int tam) {
    int i, j, aux;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam - i - 1; j++) {
            if (vUnidades[j] < vUnidades[j+1]) {
                aux = vUnidades[j+1];
                vUnidades[j+1] = vUnidades[j];
                vUnidades[j] = aux;

                aux = vCod[j+1];
                vCod[j+1] = vCod[j];
                vCod[j] = aux;
            }
        }
    }
}

void ordenarCre (int vCod[], int tam) {
    int i, j, aux;

    for (i = 0; i < tam -1; i++) {
        for (j = 0; j < tam - i - 1; j++) {
            if (vCod[j] > vCod[j+1]) {
                aux = vCod[j+1];
                vCod[j+1] = vCod[j];
                vCod[j] = aux;
            }
        }
    }
}

int buscarMin (int vec[], int tam) {
    int i, min = vec[0];

    for (i = 1; i < tam; i++) {
        if (vec[i] < min)
            min = vec[i];
    }

    return min;
}

void mostrarMins (int vec[], int tam, int min) {
    int i;

    for (i = 0; i < tam; i++) {
        if (vec[i] == min)
            printf("%d, ", i + 1001);
    }
}

void listarUnidades (int vCod[], int vUnidades[], int tam) {
    int i;

    printf("Cant. unidades\tCodigo\n");

    for (i = 0; i < tam; i++)
        printf("%d\t%d\n", vUnidades[i], vCod[i]);
}

void cargarCods (int vCod[], int tam) {
    int i, cod, pos;

    printf("Se cargaran los codigos de los 15 productos.\n\n");

    for (i = 0; i < tam; i++) {
        printf("Ingrese el codigo del producto numero %d (de 3 cifras): ", i+1);

        do {
            cod = ingIntVal(100, 999, 999);
            pos = buscarCod(vCod, tam, cod);

            if (pos != -1)
                printf("Ya existe un producto con este codigo, reingresar: ");

        } while (pos != -1);

        vCod[i] = cod;
    }
}

int ingVentas(int vCod[], int vUnidades[], int vVend[], int tamCods) {
    int huboVent = 0, vend, cod, pos, unidades;

    printf("Se cargaran las ventas realizadas durante el dia.\n\n");

    printf("Ingrese el codigo de vendedor que realizo la venta (entero entre 1001 a 1005, 0 para terminar): ");
    vend = ingIntVal(1001, 1005, 0);

    while (vend > 0) {

        printf("Ingrese el codigo de producto vendido (3 cifras): ");
        cod = ingIntVal(100, 999, 999);
        pos = buscarCod(vCod, tamCods, cod);

        if (pos != -1) {
            huboVent = 1;

            printf("Ingrese la cantidad de unidades vendidas: ");
            unidades = ingIntMayA(0);

            vVend[vend - 1001]++;
            vUnidades[pos] += unidades;
        } else {
            printf("No existe producto con el codigo ingresado.\n");
        }

        printf("Ingrese el codigo de vendedor que realizo la siguiente venta (entero entre 1001 a 1005, 0 para terminar): ");
        vend = ingIntVal(1001, 1005, 0);
    }

    return huboVent;
}