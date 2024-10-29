#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

int ingIntMayA(int);
int ingIntDifDe(int);
char ingRes();
TInscriptos buscarIns(FILE *, int);

int main () {
    FILE *pIns, *pInt;
    TInscriptos inscripto;
    TInteresados interesado;
    int dni, cantIns;
    char res;

    pIns = fopen("Archivos/INSCRIPTOS.DAT", "r+b");
    pInt = fopen("Archivos/INTERESADOS.DAT", "ab");

    if (pIns == NULL || pInt == NULL) {
        printf("Hubo un error en el manejo de archivos.");
        exit(1);
    }

    printf("Sistema de inscripcion.\n\n");

    printf("Ingrese su DNI para la inscripcion / pago (o numero negativo para terminar): ");
    dni = ingIntDifDe(0);

    while (dni > 0) {
        inscripto = buscarIns(pIns, dni);

        if (inscripto.dni != -1) {
            if (!inscripto.pagado) {
                printf("Desea realizar el pago de su inscripcion? (S/N): ");
                res = ingRes();

                if (res == 'S') {
                    inscripto.pagado = 1;
                    fseek(pIns, -sizeof(TInscriptos), SEEK_CUR);
                    fwrite(&inscripto, sizeof(TInscriptos), 1, pIns);
                    printf("Pago registrado con exito.\n");
                } else {
                    printf("No se ha registrado el pago.\n");
                }
            } else {
                printf("El pago de su inscripcion ya fue registrado.\n");
            }

        } else {
            cantIns = ftell(pIns) / sizeof(TInscriptos);

            if (cantIns < 14) {
                printf("No se encuentra inscripto, desea inscribirse? (S/N): ");
                res = ingRes();

                if (res == 'S') {
                    inscripto.dni = dni;

                    printf("Ingrese sus apellidos y nombres: ");
                    fflush(stdin);
                    gets(inscripto.apenom);
                    inscripto.pagado = 0;

                    fflush(pIns);
                    fwrite(&inscripto, sizeof(TInscriptos), 1, pIns);

                    printf("Registro exitoso. Debe registrar su pago.\n");
                } else {
                    printf("No se realizo el registro.\n");
                }
            } else {
                printf("No quedan cupos en el curso actual.\n");
                printf("Desea quedar registrado para un futuro? (S/N): ");

                res = ingRes();

                if (res == 'S') {
                    interesado.dni = dni;

                    printf("Ingrese su numero telefonico (mayor a 0): ");
                    interesado.tel = ingIntMayA(0);

                    printf("Ingrese sus apellidos y nombres: ");
                    fflush(stdin);
                    gets(interesado.apenom);

                    fwrite(&interesado, sizeof(TInteresados), 1, pInt);
                } else {
                    printf("No se registro para un futuro.\n");
                }
            }
        }

        printf("Ingrese su DNI para la inscripcion / pago (o numero negativo para terminar): ");
        dni = ingIntDifDe(0);
    }

    fclose(pIns);
    fclose(pInt);

    return 0;
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

int ingIntDifDe(int val) {
    int dato;

    do {
        scanf("%d", &dato);

        if (dato == val)
            printf("Dato invalido, reingresar: ");

    } while (dato == val);

    return dato;
}

char ingRes() {
    char res;

    do {
        fflush(stdin);
        scanf("%c", &res);

        res = toupper(res);

        if (res != 'S' && res != 'N')
            printf("Dato invalido, reingresar: ");

    } while (res != 'S' && res != 'N');

    return res;
}

TInscriptos buscarIns(FILE *fp, int dni) {
    TInscriptos inscripto;
    int encontrado = 0;

    rewind(fp);
    fread(&inscripto, sizeof(TInscriptos), 1, fp);

    while (!feof(fp) && !encontrado) {
        if (inscripto.dni == dni)
            encontrado = 1;
        else
            fread(&inscripto, sizeof(TInscriptos), 1, fp);
    }

    if (!encontrado)
        inscripto.dni = -1;

    return inscripto;
}