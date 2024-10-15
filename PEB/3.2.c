#include <stdio.h>
#include <string.h>

void leerTexto(char[], int);

int main () {
    char nombre[31], apellido[31], nomcomp[63];

    printf("Ingrese su nombre: ");
    leerTexto(nombre, 31);
    printf("Ingrese su apellido: ");
    leerTexto(apellido, 31);

    strcpy(nomcomp, nombre);
    strcat(nomcomp, ", ");
    strcat(nomcomp, apellido);

    printf("Su nombre completo es %s", nomcomp);
    return 0;
}

void leerTexto(char texto[], int tam) {
    int i = 0;
    
    fflush(stdin);
    fgets(texto, tam, stdin);

    while (texto[i] != '\0') {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}