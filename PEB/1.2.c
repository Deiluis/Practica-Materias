#include <stdio.h>

int ingIntVal (int, int, int);
int ingIntMayA(int);
int buscarCod (int[], int, int);
void ingresaCod (int[], int);
void cargarPed (int[], int[], int);
void mostrarVecs (int[], int[], int);
int buscarMin (int[], int);
int buscarMax (int[], int);
void mostrarProdsConCant (int[], int[], int, int);

int main () {
    int min, max, vCod[10], vPed[10] = {0};
    
    ingresaCod(vCod, 10);
    cargarPed(vPed, vCod, 10);
    min = buscarMin(vPed, 10);
    max = buscarMax(vPed, 10);
    mostrarVecs(vPed, vCod, 10);

    printf("Codigos de producto de los cuales se solicitaron mas unidades: ");
    mostrarProdsConCant(vPed, vCod, 10, max);
    printf("\n\n");

    printf("Codigos de producto de los cuales se solicitaron menos unidades: ");
    mostrarProdsConCant(vPed, vCod, 10, min);

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
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vCod[i] == cod)
            pos = i;
        else
            i++;
    }

    return pos;
}

void ingresaCod (int vCod[], int tam) {
    int i, cod, pos;

    printf("Se ingresaran los codigos de los productos a vender.\n\n");

    for (i = 0; i < tam; i++) {

        printf("Ingresa el codigo numero %d (debe ser de 4 cifras no haberse cargado ya): ", i +1);

        do {
            cod = ingIntVal(1000, 9999, 9999);
            pos = buscarCod(vCod, 10, cod);

            if (pos != -1)
                printf("Ya existe el codigo especificado, reingresar: ");

        } while (pos != -1);

        vCod[i] = cod;
    }
    
    printf("\n");
}

void cargarPed (int vPed[], int vCod[], int tam) {
    int cod, pos, cant;

    printf("Se ingresarán los datos de los pedidos realizados a cada producto.\n\n");

    printf("Ingresa el codigo de un producto (de 4 cifras, o 0 para terminar): ");
    cod = ingIntVal(1000, 9999, 0);

    while (cod > 0) {
        pos = buscarCod(vCod, 10, cod);

        if (pos != -1) {
            printf("Ingresa la cantidad de unidades solicitadas: ");
            cant = ingIntMayA(0);
            vPed[pos] += cant;
        } else
            printf("No se encontro un producto con este codigo.\n");

        printf("Ingresa el codigo de un producto (de 4 cifras, o 0 para terminar): ");
        cod = ingIntVal(1000, 9999, 0);
    }
}

void mostrarVecs (int vPed[], int vCod[], int tam) {
    int i;

    printf("Listado de productos:\n");
    printf("Codigo\tCantidad\n");

    for (i = 0; i < tam; i++)
        printf("%d\t%d\n", vCod[i], vPed[i]);

    printf("\n");
}

int buscarMin (int vec[], int tam) {
    int i, min = vec[0];

    for (i = 1; i < tam; i++) {
        if (vec[i] < min)
            min = vec[i];
    }

    return min;
}

int buscarMax (int vec[], int tam) {
    int i, max = vec[0];

    for (i = 1; i < tam; i++) {
        if (vec[i] > max)
            max = vec[i];
    }

    return max;
}

void mostrarProdsConCant (int vPed[], int vCod[], int tam, int cant) {
    int i;

    for (i = 0; i < tam; i++) {
        if (cant == vPed[i])
            printf("%d, ", vCod[i]);
    }
}
