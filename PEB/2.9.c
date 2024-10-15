#include <stdio.h>
#define LISTAS 10
#define SEDES 15

int ingIntVal (int, int, int);
int ingIntMayA (int);
int buscar (int[], int, int);
void mostrarVec (int[], int);
void cargarListas(int[], int);
int cargarVotos (int[][SEDES], int[], int[], int, int);
void ordenar (int[], int[], int);
void listadoTotal (int[][SEDES], int[], int[], int, int);
void listadoPorcentual (int[], int[], int, int);
void sinVotosSede5 (int[][SEDES], int[], int, int);

int main () {
    int total, vNListas[LISTAS], vTotVotos[LISTAS] = {0};
    int mVotos[LISTAS][SEDES] = {{0}};

    cargarListas(vNListas, LISTAS);
    total = cargarVotos(mVotos, vNListas, vTotVotos, LISTAS, SEDES);

    if (total > 0) {
        listadoTotal(mVotos, vNListas, vTotVotos, LISTAS, SEDES);
        sinVotosSede5(mVotos, vNListas, LISTAS, SEDES);
        ordenar(vNListas, vTotVotos, LISTAS);
        listadoPorcentual(vNListas, vTotVotos, total, LISTAS);
    } else {
        printf("No se registraron votos en ninguna sede.");
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

int buscar (int vec[], int tam, int val) {
    int i = 0, pos = -1;

    while (pos == -1 && i < tam) {
        if (vec[i] == val)
            pos = i;
        else
            i++;
    }

    return pos;
}

void mostrarVec (int vec[], int tam) {
    int i;

    for (i = 0; i < tam; i++)
        printf("%d, ", vec[i]);
}

void cargarListas(int vNListas[], int cListas) {
    int i, nLista, pos;

    printf("Se ingresaran los numeros de lista.\n\n");

    for (i = 0; i < cListas; i++) {
        printf("Ingresa el numero de lista numero %d: ", i+1);

        do {
            nLista = ingIntVal(100, 999, 999);
            pos = buscar(vNListas, i, nLista);

            if (pos != -1)
                printf("Ya existe una lista registrada con este numero, reingresar: ");

        } while (pos != -1);

        vNListas[i] = nLista;
    }
}

int cargarVotos (int mVotos[][SEDES], int vNListas[], int vTotVotos[], int cListas, int cSedes) {
    int total = 0, nLista, nSede, pos, nVotos;

    printf("Se registraran los votos efectuados.\n\n");
    printf("Las listas a votar son las siguientes:\n");
    mostrarVec(vNListas, cListas);
    printf("\n");

    printf("Ingrese el numero de lista a votar (3 cifras, 0 para terminar): ");
    nLista = ingIntVal(100, 999, 0);

    while (nLista > 0) {
        pos = buscar(vNListas, cListas, nLista);

        if (pos != -1) {
            printf("Ingrese el numero de sede a votar (1 a 15): ");
            nSede = ingIntVal(1, 15, 15);
            printf("Ingrese la cantidad de votos registrados (mayor a 0): ");
            nVotos = ingIntMayA(0);

            mVotos[pos][nSede -1] += nVotos;
            vTotVotos[pos] += nVotos;
            total += nVotos;
        } else {
            printf("No se encontro la lista con el numero especificado.\n");
        }

        printf("Ingrese el numero de lista a registrar votos (3 cifras, 0 para terminar): ");
        nLista = ingIntVal(100, 999, 0);
    }

    return total;
}

void ordenar (int vNListas[], int vTotVotos[], int cListas) {
    int i, j, aux;

    for (i = 0; i < cListas -1; i++) {
        for (j = 0; j < cListas - 1 - i; j++) {
            if (vTotVotos[j] < vTotVotos[j+1]) {

                aux = vTotVotos[j+1];
                vTotVotos[j+1] = vTotVotos[j];
                vTotVotos[j] = aux;

                aux = vNListas[j+1];
                vNListas[j+1] = vNListas[j];
                vNListas[j] = aux;
            }
        }
    }
}

void listadoTotal (int mVotos[][SEDES], int vNListas[], int vTotVotos[], int cListas, int cSedes) {
    int i, j;

    printf("Listado de votos de cada lista en cada sede:\n\n");
    printf("Lista\t");

    for (i = 0; i < cSedes; i++)
        printf("Sede %d\t", i+1);

    printf("\n");

    for (i = 0; i < cListas; i++) {
        if (vTotVotos[i] > 0) {
            printf("%d\t", vNListas[i]);

            for (j = 0; j < cSedes; j++)
                printf("%d\t", mVotos[i][j]);

            printf("\n");
        }
    }
}

void listadoPorcentual (int vNListas[], int vTotVotos[], int total, int cListas) {
    int i;
    float porc;

    printf("Listado de votos ordenado decreciente con porcentajes:\n\n");
    printf("Total de votos\tPorcentaje\tLista\n");

    for (i = 0; i < cListas; i++) {
        if (vTotVotos[i] > 0) {
            porc = (float) (vTotVotos[i] * 100) / total;
            printf("%d\t%.2f%\t%d\n", vTotVotos[i], porc, vNListas[i]);
        }
    }
}

void sinVotosSede5 (int mVotos[][SEDES], int vNListas[], int cListas, int cSedes) {
    int i;

    printf("Listas que no recibieron votos en la sede 5: ");

    for (i = 0; i < cListas; i++) {
        if (mVotos[i][4] == 0)
            printf("%d, ", vNListas[i]);
    }
}