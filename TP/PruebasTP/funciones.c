#include "funciones.h"

/*Para la primera parte solo faltaria, agregar el campo extra, implementar el TDA fecha y corregir la "construccion" de Registro*/


/*Funcion general, procesa el archivo de indices generales*/
int corregirFormatoDeIndicesGeneral (FILE* archivo)
{
    Registro reg;
    char buffer[BUFFER_TAM];
    char valorClasificador[CLASIFICADOR_TAM];
    char aBuscar = '\n';
    char* dirDeRetorno;

    char nGeneral[] = "Nivel general";
    char capitulos[] = "Capítulos";

    fgets(buffer, BUFFER_TAM, archivo);

    dirDeRetorno = buscarEnVector(buffer, BUFFER_TAM, sizeof(char), &aBuscar, cmpChar);

    if (!dirDeRetorno)
        return ERR_BUFFER_CORTO;

    while (!feof(archivo)) {
        sscanf(buffer, FORMATO_GENERAL, reg.periodo, reg.nivel, reg.indiceICC);
        
        corregirFormatoDeFecha(&reg);
        agregarCeroALaIzquierda(&reg);
        corregirFormatoDecimal(&reg);
        desencriptarNivelGeneral(&reg);
        normalizarNivelSinGuiones(&reg);

        stringCopiar(
            valorClasificador, 
            stringComparar(reg.nivel, nGeneral) == 0 ? nGeneral : capitulos
        );

        agregarCampo(&reg, "Clasificador", valorClasificador);
        
        //printf("Fecha: %s Nivel: %s Indice: %s\n", reg.periodo, reg.nivel, reg.indiceICC);

        fseek(archivo, -sizeof(Registro), SEEK_CUR);
        fprintf(archivo, "%s;%s;%s", reg.periodo, reg.nivel, reg.indiceICC);

        fgets(buffer, BUFFER_TAM, archivo);
    }

    return TODO_OK;
}

int corregirFormatoDeIndicesObra (FILE* archivo) {
    Registro reg;
    char buffer[BUFFER_TAM];
    char aBuscar = '\n';
    char* dirDeRetorno;

    fgets(buffer, BUFFER_TAM, archivo);

    dirDeRetorno = buscarEnVector(buffer, BUFFER_TAM, sizeof(char), &aBuscar, cmpChar);

    if (!dirDeRetorno)
        return ERR_BUFFER_CORTO;

    while (!feof(archivo)) {
        sscanf(buffer, FORMATO_GENERAL, reg.periodo, reg.nivel, reg.indiceICC);
        
        corregirFormatoDeFecha(&reg);
        agregarCeroALaIzquierda(&reg);
        corregirFormatoDecimal(&reg);

        fseek(archivo, -sizeof(Registro), SEEK_CUR);
        fprintf(archivo, "%s;%s;%s", reg.periodo, reg.nivel, reg.indiceICC);

        fgets(buffer, BUFFER_TAM, archivo);
    }

    return TODO_OK;
}


/*Funcion general, corrige el formato de la fecha de dd/mm/aaaa a dd-mm-aaaa */
char* corregirFormatoDeFecha(Registro* reg)
{
    char* p = reg->periodo;

    while(*p){
        if(*p == '/'){
            *p = '-';
        }

        p++;
    }

    return reg->periodo;
}

/*Funcion general, agrega los "leading zeroes" a los valores de la fecha*/
/*Como contra, la fecha pasa a ser un valor int, no se si estaria bien*/
char* agregarCeroALaIzquierda(Registro* reg)
{
    char* p = reg->periodo;
    int d, m, a;
    
    sscanf(p, "\"%d-%d-%d\"\n", &d, &m, &a);
    
    sprintf(p, "%04d-%02d-%02d", a, m, d);

    return reg->periodo;
}

/*Funcion general, desarrolla el proceso de decriptacion del campo nivel general*/
char* desencriptarNivelGeneral (Registro* reg)
{
    size_t contador = 0;
    char* p = reg->nivel;
    
    printf("A - %s\n", p);
    
    while(*p){
        if(esLetra(p)){
            if (contador % 2 == 0){
                *p += 2;
            }
            else{
                *p += 4;
            }

            if(*p > 'z'){
                *p = 'a' + (*p - 'z' - 1);
            }
        }
        
        contador++;
        p++;
    }

    return reg->nivel;
}

/*Funcion general, normaliza el campo nivel general desencriptado y remueve los guiones*/
char* normalizarNivelSinGuiones(Registro* reg)
{
    char* p = reg->nivel;
    
    p++;

    *p = aMayus(p);
    
    while(*p){
        if(*p == '_'){
            *p = ' ';
        }

        p++;
    }
    
    return reg->nivel;
}

/*Funcion general, corrige el formato del campo indice de f*,f* a f*.f* */
char* corregirFormatoDecimal(Registro* reg)
{
    char* p = reg->indiceICC;

    while(*p){
        if(*p == ','){
            *p = '.';
        }

        p++;
    }

    return reg->indiceICC;
}

// Utilitarias

void* buscarEnVector (void* vec, size_t cantElem, size_t tamElem, void* elem, Cmp cmp) {

    int pos = -1;
    void* i = vec;
    void* ult = vec + (cantElem -1) * tamElem;

    while (cmp(i, elem) != 0 && i <= ult)
        i += tamElem;
    
    if (cmp(i, elem) == 0)
        return i;

    return NULL;
}

char* stringComparar (char* str1, char* str2) {
    
}

// Auxiliares

/*Funcion auxiliar, para saber si un char es letra, igual que isalpha form ctype.h*/
int esLetra (char* c)
{
    char aux = aMayus(c);
    return (aux >= 'A' && aux <= 'Z');
}

/*Funcion auxiliar, pasa el caracter a mayúsculas */
char aMayus (char* c)
{
    char aux = *c;
    aux -= 32;
    return aux;
}

/*
 * Realiza la comparación entre dos char.
*/
int cmpChar (void* a, void* b) {
    char* c1 = a;
    char* c2 = b;

    return *c1 - *c2;
}