#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia, mes, anio;
} TFecha;

typedef struct {
    char nomape[36];
    int dni;
    char loc[41];
    char email[21];
    TFecha fecha;
} TVisitante;

int buscarVis(TVisitante[], int, int);
int cantDiasMes(int, int);
int bisiesto(int, int);
int esFechaVal(int, int, int);
TFecha ingFechaVal();
int ingIntVal(int, int);
int cargar(TVisitante[], int);
void ordenar(TVisitante[], int);
void genArchivo(TVisitante[], int, FILE *);
void infYGen(FILE *);

int main () {
    FILE *pVis;
    TVisitante vVis[500];
    int cant;

    pVis = fopen("Archivos/VISITANTES.dat", "w+b");
    
    if (pVis == NULL) {
        printf("Hubo un error en el manejo de archivos.");
        exit(1);
    }

    cant = cargar(vVis, 500);

    if (cant > 0) {
        ordenar(vVis, cant);
        genArchivo(vVis, cant, pVis);
        rewind(pVis);
        infYGen(pVis);
    } else
        printf("No se registraron visitantes.");

    fclose(pVis);
    return 0;
}

int buscarVis(TVisitante vVis[], int cant, int dni) {
    int i = 0, pos = -1;

    while (pos == -1 && i < cant) {
        if (vVis[i].dni == dni)
            pos = i;
        else
            i++;
    }

    return pos;
}

int cantDiasMes(int mes, int anio) {
    int dias;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        dias = 30;
    } else {
        if (mes == 2) {
            dias = 28 + bisiesto(mes, anio);
        } else
            dias = 31;
    }

    return dias;
}

int bisiesto(int mes, int anio) {
    int bisiesto = 0;

    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
        bisiesto = 1;

    return bisiesto;
}

int esFechaVal(int dia, int mes, int anio) {
    int fechaVal = 0;
    
    if (anio > 1582) {
        if (mes >= 1 && mes <= 12) {
            if (dia >= 1 && dia <= cantDiasMes(mes, anio))
                fechaVal = 1;
        }
    }

    return fechaVal;
}

TFecha ingFechaVal() {
    TFecha fecha;

    do {
        printf("Ingrese el dia: ");
        scanf("%d", &fecha.dia);
        printf("Ingrese el mes: ");
        scanf("%d", &fecha.mes);
        printf("Ingrese el anio: ");
        scanf("%d", &fecha.anio);
        
        if (!esFechaVal(fecha.dia, fecha.mes, fecha.anio))
            printf("Fecha invalida, reingresar.\n");

    } while (!esFechaVal(fecha.dia, fecha.mes, fecha.anio));

    return fecha;
}

int ingIntVal(int limi, int lims) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato <= limi || dato >= lims)
            printf("Dato invalido, reingresar: ");

    } while (dato <= limi || dato >= lims);

    return dato;
}

int cargar(TVisitante vVis[], int tam) {
    TVisitante vis;
    int pos, cant = 0;

    printf("Ingrese el nombre de un vistante a registrar, 'FIN' para terminar: ");
    gets(vis.nomape);

    while (strcmpi(vis.nomape, "FIN") != 0 && cant < tam) {
        printf("Ingrese el DNI del visitante: ");
        vis.dni = ingIntVal(1000000, 99999999);

        pos = buscarVis(vVis, cant, vis.dni);

        if (pos == -1) {
            printf("Ingrese la localidad del visitante: ");
            fflush(stdin);
            gets(vis.loc);
            printf("Ingrese el email del visitante: ");
            fflush(stdin);
            gets(vis.email);
            printf("Ingrese la fecha de visita: ");
            vis.fecha = ingFechaVal();

            vVis[cant] = vis;

            cant++;
        } else
            printf("Ya se registro a este visitante");

        if (cant < tam) {
            printf("Ingrese el nombre de un vistante a registrar, 'FIN' para terminar: ");
            fflush(stdin);
            gets(vis.nomape);
        }
    }

    return cant;
}

void ordenar(TVisitante vVis[], int cant) {
    int i, j;
    TVisitante aux;

    for (i = 0; i < cant -1; i++) {
        for (j = 0; j < cant -1 -i; j++) {
            if (strcmpi(vVis[j].loc, vVis[j+1].loc) > 0) {
                aux = vVis[j+1];
                vVis[j+1] = vVis[j];
                vVis[j] = aux; 
            }
        }
    }
}

void genArchivo(TVisitante vVis[], int cant, FILE *pVis) {
    int i;

    for (i = 0; i < cant; i++) {
        fwrite(&vVis[i], sizeof(TVisitante), 1, pVis);
    }
}

void infYGen(FILE *pVis) {
    TVisitante vis;
    int cantVis;
    char antLoc[41], nArch[54];
    FILE *pLoc;

    fread(&vis, sizeof(TVisitante), 1, pVis);

    while (!feof(pVis)) {

        strcpy(antLoc, vis.loc);
        cantVis = 0;
        strcpy(nArch, "Archivos/");
        strcat(nArch, vis.loc);
        strcat(nArch, ".dat");

        pLoc = fopen(nArch, "wb");

        if (pLoc == NULL) {
            printf("Error en el manejo de archivos");
            exit(1);
        }

        do {
            cantVis++;
            fwrite(&vis, sizeof(TVisitante), 1, pLoc);
            fread(&vis, sizeof(TVisitante), 1, pVis);
        } while (!feof(pVis) && strcmpi(antLoc, vis.loc) == 0);

        printf("Visitas en %s: %d\n", antLoc, cantVis);
        fclose(pLoc);
        
    }
}
