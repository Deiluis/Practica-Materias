#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../TDAPilaDinamica/Pila.h"

#define ARG_TXT_OP_1 1
#define ARG_TXT_OP_2 2
#define ARG_TXT_RES 3

bool cargarPilaDeTxt(tPila*, const char*);
bool realizarSuma(tPila*, tPila*, tPila*);
bool cargarPilaEnTxt(tPila*, const char*);

// SumaGrande.exe op1.txt op2.txt res.txt
int main (int argc, char* argv[]) {

    tPila pila1;
    tPila pila2;
    tPila pilaRes;

    crearPila(&pila1);
    crearPila(&pila2);
    crearPila(&pilaRes);

    if (!cargarPilaDeTxt(&pila1, argv[ARG_TXT_OP_1])) {
        printf("Error cargando la pila 1. Vaciando.\n");
        vaciarPila(&pila1);
    }

    if (!cargarPilaDeTxt(&pila2, argv[ARG_TXT_OP_2])) {
        printf("Error cargando la pila 2. Vaciando.\n");
        vaciarPila(&pila2);
    }

    if (!realizarSuma(&pila1, &pila2, &pilaRes)) {
        printf("Error cargando la pila de resultado. Vaciando.\n");
        vaciarPila(&pilaRes);
    }

    if (!cargarPilaEnTxt(&pilaRes, argv[ARG_TXT_RES]))
        printf("Error cargando el archivo de resultado.\n");

    return 0;
}

bool cargarPilaDeTxt (tPila* p, const char* nomArch) {

    FILE* archTxt = fopen(nomArch, "rt");
    char act;
    bool errCarga = false;

    if (archTxt == NULL)
        return false;

    act = fgetc(archTxt);

    while (!feof(archTxt) && !errCarga) {
        errCarga = !apilar(p, &act, sizeof(act));
        act = fgetc(archTxt);
    }

    fclose(archTxt);

    return !errCarga;
}

bool realizarSuma (tPila* pOp1, tPila* pOp2, tPila* pRes) {

    bool errCarga = false;
    char op1c, op2c, resc;
    int op1, op2, res, carry = 0;

    while (!errCarga && !pilaVacia(pOp1) && !pilaVacia(pOp2)) {

        desapilar(pOp1, &op1c, sizeof(char));
        desapilar(pOp2, &op2c, sizeof(char));

        op1 = op1c - '0';
        op2 = op2c - '0';
        res = op1 + op2 + carry;

        carry = res / 10;
        res -= carry * 10;

        // Convierte a char;
        resc = '0' + res;
        errCarga = !apilar(pRes, &resc, sizeof(char));
    }

    while (!errCarga && !pilaVacia(pOp1)) {

        desapilar(pOp1, &op1c, sizeof(char));
        op1 = op1c - '0';
        res = op1 + carry;

        carry = res / 10;
        res -= carry * 10;

        // Convierte a char;
        resc = '0' + res;
        errCarga = !apilar(pRes, &resc, sizeof(char));
    }

    while (!errCarga && !pilaVacia(pOp2)) {

        desapilar(pOp2, &op2c, sizeof(char));
        op2 = op2c - '0';
        res = op2 + carry;

        carry = res / 10;
        res -= carry * 10;

        // Convierte a char;
        resc = '0' + res;
        errCarga = !apilar(pRes, &resc, sizeof(char));
    }

    if (!errCarga && carry) {
        resc = '1';
        errCarga = !apilar(pRes, &resc, sizeof(char));
    }

    return !errCarga;
}

bool cargarPilaEnTxt (tPila* p, const char* nomArch) {

    FILE* archTxt = fopen(nomArch, "wt");
    char num;

    if (archTxt == NULL)
        return false;

    while (desapilar(p, &num, sizeof(char)))
        fprintf(archTxt, "%c", num);

    fprintf(archTxt, "%c", '\n');
    fclose(archTxt);

    return true;
}
