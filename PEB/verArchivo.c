#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dni;
    char apenom[21];
    int pagado;
} TInscriptos;

typedef struct {
    char apenom[21];
    int dni;
    int tel;
} TInteresados;

void mostrarArchivo();
void mostrarArchivo2();

int main() {
    mostrarArchivo();
    mostrarArchivo2();
    return 0;
}

void mostrarArchivo() {
    FILE *fp;
    TInscriptos ins;

    fp = fopen("Archivos/INSCRIPTOS.DAT", "rb");

    if (fp == NULL) {
        printf("Error al leer STOCK.DAT");
        exit(1);
    }

    fread(&ins, sizeof(TInscriptos), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%d\t%s\t%d\n", ins.dni, ins.apenom, ins.pagado);
        fread(&ins, sizeof(TInscriptos), 1, fp);
    }
    
    fclose(fp);
}

void mostrarArchivo2() {
    FILE *fp;
    TInteresados intersado;

    fp = fopen("Archivos/INTERESADOS.DAT", "rb");

    if (fp == NULL) {
        printf("Error al leer INTERESADOS.DAT");
        exit(1);
    }

    fread(&intersado, sizeof(TInteresados), 1, fp);

    printf("Contenido del archivo:\n");

    while (!feof(fp)) {
        printf("%d\t%s\t%d\n", intersado.dni, intersado.apenom, intersado.tel);
        fread(&intersado, sizeof(TInteresados), 1, fp);
    }
    
    fclose(fp);
}