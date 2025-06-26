#include <stdio.h>
#include <stdlib.h>
#include "../TDAPalabra/SecuenciaPalabras.h"
#include "../../TDAVector/Vector.h"

#include <string.h>

#define ARG_ARCH_TXT 1

#define TODO_OK 0
#define ERR_EN_ARCHIVO 1
#define ERR_BUFFER_CORTO 2

#define BUFFER_TAM 254

typedef struct {
    Palabra pal;
    size_t cantApariciones;
} Entrada;

int contarYCargarPalindromos (FILE* arch, int* cont, Vector* diccionario);
void mostrarEntrada (const void* elem);
int compararEntrada (const void* e1, const void* e2);

// PracticaDefensa.exe consignaDef.csv
int main (int argc, char* argv[]) {

    int cont = 0, cod = TODO_OK;
    FILE* arch = fopen(argv[ARG_ARCH_TXT], "rt");
    Vector diccionario;

    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return ERR_EN_ARCHIVO;
    }

    if (!vectorCrear(&diccionario, sizeof(Entrada))) {
        printf("Error al crear el diccionario.\n");
        return SIN_MEM;
    }

    printf("Palindromos encontrados: ");

    cod = contarYCargarPalindromos(arch, &cont, &diccionario);

    vectorMostrar(&diccionario, mostrarEntrada);

    printf("En %s hay %d palindromos.\n", argv[ARG_ARCH_TXT], cont);

    fclose(arch);
    vectorDestruir(&diccionario);

    return cod;
}

int contarYCargarPalindromos (FILE* arch, int* cont, Vector* diccionario) {

    char buffer[BUFFER_TAM +1];
    int pos, cod = TODO_OK;
    SecuenciaPalabras sec;
    Palabra pal;
    Entrada ent;

    while (cod == TODO_OK && fgets(buffer, BUFFER_TAM, arch)) {

        if (!strrchr(buffer, '\n'))
            cod = ERR_BUFFER_CORTO;

        else {
            secuenciaPalabrasCargar(&sec, buffer);
            secuenciaPalabrasLeer(&sec, &pal);

            while (cod == TODO_OK && !secuenciaPalabrasFin(&sec)) {

                if (palabraEsPalindromo(&pal)) {

                    (*cont)++;

                    //strcpy(ent.pal.vPal, pal.vPal);

                    ent.pal = pal;

                    pos = vectorOrdBuscar(diccionario, &ent, compararEntrada);

                    if (pos == -1) {
                        ent.cantApariciones = 1;
                        cod = vectorOrdInsertar(diccionario, &ent, compararEntrada);
                    } else {
                        ent.cantApariciones++;
                        vectorModificarDePos(diccionario, pos, &ent);
                    }
                }

                secuenciaPalabrasLeer(&sec, &pal);
            }
        }
    }

    printf("\n\n");

    return cod;
}

void mostrarEntrada (const void* elem) {

    const Entrada* ent = elem;

    printf("Palabra: ");
    palabraMostrar((Palabra*) &ent -> pal);
    printf(", cantidad de apariciones: %Iu", ent -> cantApariciones);
    printf("\n");
}

int compararEntrada (const void* e1, const void* e2) {
    const Entrada* ent1 = e1;
    const Entrada* ent2 = e2;

    return palabraCompararI((Palabra*) &ent1 -> pal, (Palabra*) &ent2 -> pal);
}
