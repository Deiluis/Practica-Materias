#include <stdio.h>
#include <stdlib.h>

// Nombres de archivos
#define NOMBRE_ARCH_INDICES_GENERAL "indices_icc_general_capitulos.txt"
#define NOMBRE_ARCH_INDICES_OBRA "Indices_items_obra.txt"
#define NOMBRE_ARCH_AUXILIAR "auxiliar.tmp"

#define FORMATO_GENERAL "%[^;];%[^;];%[^;]"

// Estados de retorno
#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_BUFFER_CORTO 2


// Tamaños para strings
#define BUFFER_TAM 255

#define PERIODO_TAM 11
#define NIVEL_TAM 31
#define INDICE_TAM 17
#define CLASIFICADOR_TAM 14

// Booleanos
#define bool int
#define false 0
#define true 1


typedef struct{
    char periodo[PERIODO_TAM];
    char nivel[NIVEL_TAM];
    char indiceICC[INDICE_TAM];
    char clasificador[CLASIFICADOR_TAM];
} Registro;


typedef int (*Cmp) (void* a, void* b);

int corregirFormatoDeIndicesGeneral(FILE* archivo);
int corregirFormatoDeIndicesObra (FILE* archivo);

char* corregirFormatoDeFecha(Registro* registro);
char* agregarCeroALaIzquierda(Registro* registro);
char* desencriptarNivelGeneral(Registro* registro);
char* normalizarNivelSinGuiones(Registro* registro);
char* corregirFormatoDecimal(Registro* registro); 

void* buscarEnVector (void* vec, size_t cantElem, size_t tamElem, void* elem, Cmp cmp);

int esLetra(char* c);
char aMayus(char* c);