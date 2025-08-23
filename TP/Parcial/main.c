/*****************************************************************************************************************
** Apellido/s, Nombre/s:                               													**
** DNI:                                                   													**
******************************************************************************************************************
** Corrección																								   	**
****************																							   	**

******************************************************************************************************************
** Nota:
*****************************************************************************************************************/

//#define SOLUCION_DOC
#define SOLUCION_ALU


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Comun.h>
#include <Cadena.h>
#include <Vector.h>
#include <Archivo.h>
#include <SolucionParcialFabricasComputadorasTopicos.h>

#define PROD_COR "Productos-cor.dat"
#define PROD_CHU_TXT "Productos-chu.txt"
#define CLI_COR "Clientes-cor.dat"
#define CLI_CHU "Clientes-chu.dat"
#define PROD_FUS "Productos-fus.dat"
#define CLI_FUS "Clientes-fus.dat"

#define TAM_LINEA 100
#define TAM_NOMBRE_ARCH 20

#define ERR_LINEA_CORTA 5

typedef int (*Cmp_ALU) (const void* reg1, const void* reg2);
typedef void (*Imp_ALU) (const void* reg1);
typedef void (*Act_ALU) (void* reg1, const void* reg2);

// Funciones principales
int procesarArchivos_ALU(
	const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
	const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
	const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus);

int convTxtABin_ALU (const char* nomArchTxt, const char* nomArchBin);
int txtVABin_ALU (char* linea, Producto* prod);
void cambiarExtension_ALU (const char* nomArchOr, const char* ext, char* nomArchModif);
int compararProds_ALU (const void* reg1, const void* reg2);
int compararClientes_ALU (const void* reg1, const void* reg2);
int merge_ALU (
    const char* nomArch1, const char* nomArch2,
    const char* nomArchMerge, size_t tamReg, Cmp_ALU cmpReg
);
void imprimirProducto_ALU (const void* reg1);
void imprimirCliente_ALU (const void* reg1);
void actualizarProductos_ALU (void* reg1, const void* reg2);

// Primitivas de TDA Vector
int vectorCargarDeBin_ALU (Vector* v, size_t tamElem, const char* nomArch);
void vectorMostrar_ALU (Vector* v, Imp_ALU imp);
int vectorOrdenar_ALU (Vector* v, Cmp_ALU cmp);
int vectorGuardarEnBin_ALU (Vector* v, const char* nomArch);
void vectorOrdElimDup_ALU (Vector* v, Cmp_ALU cmp, Act_ALU act);
void vectorEliminarDePos_ALU (Vector* v, int pos);
void vectorDestruir_ALU (Vector* v);


// Auxiliares
void* buscarMenor_ALU (void* ini, void* fin, size_t tamElem, Cmp_ALU cmp);
void intercambiar_ALU (void* elem1, void* elem2, void* aux, size_t tamElem);

int main()
{
    int resp = generarArchivos();

    if(resp != TODO_OK)
    {
        printf("Error al generar los archivos");
        return resp;
    }

    puts("Archivos Pre Fusion:\n");

    puts(PROD_COR);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_COR);

    puts("\n");

    puts(PROD_CHU_TXT);
    puts("=========================================");
    mostrarArchivoProductosTxt(PROD_CHU_TXT);

    puts("\n");

    puts(CLI_COR);
    puts("=========================================");
    mostrarArchivoClientes(CLI_COR);

    puts("\n");

    puts(CLI_CHU);
    puts("=========================================");
    mostrarArchivoClientes(CLI_CHU);


    #ifdef SOLUCION_DOC
        resp = procesarArchivos(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #else
        resp = procesarArchivos_ALU(PROD_COR, PROD_CHU_TXT, CLI_COR, CLI_CHU, PROD_FUS, CLI_FUS);
    #endif

    if(resp != TODO_OK)
    {
        printf("Error al procesar los archivos");
        return resp;
    }

    puts("\n\nArchivos Post Fusion:\n");

    puts(PROD_FUS);
    puts("=========================================");
    mostrarArchivoProductosBin(PROD_FUS);

    puts("\n");

    puts(CLI_FUS);
    puts("=========================================");
    mostrarArchivoClientes(CLI_FUS);

    return 0;
}

int procesarArchivos_ALU(
	const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
	const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
	const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus)
{
    char nomArchProdsChuDat[TAM_NOMBRE_ARCH +1];
    int cod;
    Vector vProdsCor, vProdsChu, vClientesCor, vClientesChu, vProdsFus, vClientesFus;

    cambiarExtension_ALU(nombreArchivoProductosChu, "dat", nomArchProdsChuDat);
    cod = convTxtABin_ALU(nombreArchivoProductosChu, nomArchProdsChuDat);

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vProdsCor, sizeof(Producto), nombreArchivoProductosCor);

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vProdsChu, sizeof(Producto), nomArchProdsChuDat);

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vClientesCor, sizeof(Cliente), nombreArchivoClientesCor);

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vClientesChu, sizeof(Cliente), nombreArchivoClientesChu);

    if (cod != TODO_OK)
        return cod;

    vectorOrdenar_ALU(&vProdsCor, compararProds_ALU);
    vectorOrdenar_ALU(&vProdsChu, compararProds_ALU);
    vectorOrdenar_ALU(&vClientesCor, compararClientes_ALU);
    vectorOrdenar_ALU(&vClientesChu, compararClientes_ALU);

    cod = vectorGuardarEnBin_ALU(&vProdsCor, nombreArchivoProductosCor);

    if (cod != TODO_OK)
        return cod;

    cod = vectorGuardarEnBin_ALU(&vProdsChu, nomArchProdsChuDat);

    if (cod != TODO_OK)
        return cod;

    cod = vectorGuardarEnBin_ALU(&vClientesCor, nombreArchivoClientesCor);

    if (cod != TODO_OK)
        return cod;

    cod = vectorGuardarEnBin_ALU(&vClientesChu, nombreArchivoClientesChu);

    if (cod != TODO_OK)
        return cod;

    vectorDestruir_ALU(&vProdsCor);
    vectorDestruir_ALU(&vProdsChu);
    vectorDestruir_ALU(&vClientesCor);
    vectorDestruir_ALU(&vClientesChu);


    // Merge de productos
    cod = merge_ALU(
      nombreArchivoProductosCor,
      nomArchProdsChuDat,
      nombreArchivoProductosFus,
      sizeof(Producto),
      compararProds_ALU
    );

    if (cod != TODO_OK)
        return cod;

    // Merge de clientes
    cod = merge_ALU(
      nombreArchivoClientesCor,
      nombreArchivoClientesChu,
      nombreArchivoClientesFus,
      sizeof(Cliente),
      compararClientes_ALU
    );

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vProdsFus, sizeof(Producto), nombreArchivoProductosFus);

    if (cod != TODO_OK)
        return cod;

    cod = vectorCargarDeBin_ALU(&vClientesFus, sizeof(Cliente), nombreArchivoClientesFus);

    if (cod != TODO_OK)
        return cod;

    //vectorOrdEliminarDuplicados(&vProdsFus, compararProds_ALU, actualizarProductos_ALU);
    //vectorOrdEliminarDuplicados(&vClientesFus, compararClientes_ALU, NULL);

    vectorOrdElimDup_ALU(&vProdsFus, compararProds_ALU, actualizarProductos_ALU);
    vectorOrdElimDup_ALU(&vClientesFus, compararClientes_ALU, NULL);

    cod = vectorGuardarEnBin_ALU(&vProdsFus, nombreArchivoProductosFus);

    if (cod != TODO_OK)
        return cod;

    cod = vectorGuardarEnBin_ALU(&vClientesFus, nombreArchivoClientesFus);

    if (cod != TODO_OK)
        return cod;

    vectorDestruir_ALU(&vProdsFus);
    vectorDestruir_ALU(&vClientesFus);

	return TODO_OK;
}

int convTxtABin_ALU(const char* nomArchTxt, const char* nomArchBin) {

    FILE* archTxt = fopen(nomArchTxt, "rt");

    if (!archTxt)
        return ERR_ARCHIVO;

    FILE* archBin = fopen(nomArchBin, "wb");

    if (!archTxt) {
        fclose(archTxt);
        return ERR_ARCHIVO;
    }

    char linea[TAM_LINEA +1];
    int cod = TODO_OK;
    Producto prod;

    while (cod == TODO_OK && fgets(linea, TAM_LINEA, archTxt)) {

        cod = txtVABin_ALU(linea, &prod);

        if (cod == TODO_OK)
            fwrite(&prod, sizeof(Producto), 1, archBin);
    }

    fclose(archTxt);
    fclose(archBin);

    return cod;
}

int txtVABin_ALU (char* linea, Producto* prod) {

    char* act = strrchr(linea, '\n');

    if (!act)
        return ERR_LINEA_CORTA;

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act +1, "%d", &prod -> stock);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act +1, "%f", &prod -> precio);

    *act = '\0';
    act = strrchr(linea, '|');
    strcpy(prod -> descripcion, act +1);

    *act = '\0';
    strcpy(prod -> codigo, linea);

    return TODO_OK;
}

void cambiarExtension_ALU(const char* nomArchOr, const char* ext, char* nomArchModif) {

    strcpy(nomArchModif, nomArchOr);

    // Ya se sabe que el nombre de archivo viene con extension.
    char* punto = strrchr(nomArchModif, '.');
    strcpy(punto +1, ext);
}

int compararProds_ALU (const void* reg1, const void* reg2) {
    const Producto* p1 = reg1;
    const Producto* p2 = reg2;

    return strcmp(p1 -> codigo, p2 -> codigo);
}

int compararClientes_ALU (const void* reg1, const void* reg2) {
    const Cliente* c1 = reg1;
    const Cliente* c2 = reg2;

    return c1 -> codigo - c2 -> codigo;
}

int merge_ALU (const char* nomArch1, const char* nomArch2, const char* nomArchMerge, size_t tamReg, Cmp_ALU cmpReg) {

    FILE* arch1 = fopen(nomArch1, "rb");

    if (!arch1)
        return ERR_ARCHIVO;

    FILE* arch2 = fopen(nomArch2, "rb");

    if (!arch2) {
        fclose(arch1);
        return ERR_ARCHIVO;
    }

    FILE* archMerge = fopen(nomArchMerge, "wb");

    if (!nomArchMerge) {
        fclose(arch1);
        fclose(arch2);
        return ERR_ARCHIVO;
    }

    void* reg1 = malloc(tamReg);

    if (!reg1) {
        fclose(arch1);
        fclose(arch2);
        fclose(archMerge);
        return SIN_MEM;
    }

    void* reg2 = malloc(tamReg);

    if (!reg2) {
        fclose(arch1);
        fclose(arch2);
        fclose(archMerge);
        free(reg1);
        return SIN_MEM;
    }

    int comp;

    fread(reg1, tamReg, 1, arch1);
    fread(reg2, tamReg, 1, arch2);

    while (!feof(arch1) && !feof(arch2)) {

        comp = cmpReg(reg1, reg2);

        if (comp == 0) {
            fwrite(reg1, tamReg, 1, archMerge);
            fwrite(reg2, tamReg, 1, archMerge);

            fread(reg1, tamReg, 1, arch1);
            fread(reg2, tamReg, 1, arch2);
        }

        else if (comp < 0) {
            fwrite(reg1, tamReg, 1, archMerge);
            fread(reg1, tamReg, 1, arch1);
        }

        else {
            fwrite(reg2, tamReg, 1, archMerge);
            fread(reg2, tamReg, 1, arch2);
        }
    }

    // Por si se acaba alguno de los archivos, carga los registros del que quede.
    while (!feof(arch1)) {
        fwrite(reg1, tamReg, 1, archMerge);
        fread(reg1, tamReg, 1, arch1);
    }

    while (!feof(arch2)) {
        fwrite(reg2, tamReg, 1, archMerge);
        fread(reg2, tamReg, 1, arch2);
    }

    fclose(arch1);
    fclose(arch2);
    fclose(archMerge);
    free(reg1);
    free(reg2);

    return TODO_OK;
}

void imprimirProducto_ALU (const void* reg1) {
    const Producto* p = reg1;
    printf("%s %s %f %d\n", p -> codigo, p -> descripcion, p -> precio, p -> stock);
}

void imprimirCliente_ALU (const void* reg1) {
    const Cliente* c = reg1;
    printf("%d %s\n", c -> codigo, c -> apellidoYNombre);
}

void actualizarProductos_ALU (void* reg1, const void* reg2) {
    Producto* p1 = (Producto*) reg1;
    Producto* p2 = (Producto*) reg2;

    p1 -> stock += p2 -> stock;
    p1 -> precio = p1 -> precio > p2 -> precio ? p1 -> precio : p2 -> precio;
}

// Primitivas de TDA Vector

int vectorCargarDeBin_ALU (Vector* v, size_t tamElem, const char* nomArch) {

    FILE* archBin = fopen(nomArch, "rb");

    if (!archBin)
        return ERR_ARCHIVO;

    fseek(archBin, 0, SEEK_END);

    size_t cantReg = ftell(archBin) / tamElem;
    void* vec = malloc(cantReg * tamElem);

    if (vec == NULL) {
        v -> vec = NULL;
        v -> cap = 0;
        v -> ce = 0;
        v -> tamElem = 0;
    }

    rewind(archBin);
    fread(vec, tamElem, cantReg, archBin);

    v -> vec = vec;
    v -> cap = cantReg;
    v -> ce = cantReg;
    v -> tamElem = tamElem;

    fclose(archBin);

    return TODO_OK;
}

void vectorMostrar_ALU (Vector* v, Imp_ALU imp) {

    void* i;
    void* ult = v -> vec + (v -> ce -1) * v -> tamElem;

    for (i = v -> vec; i <= ult; i += v -> tamElem)
        imp(i);
}

int vectorOrdenar_ALU (Vector* v, Cmp_ALU cmp) {

    void* aux = malloc(v -> tamElem);

    if (!aux)
        return SIN_MEM;

    void* i;
    void* m;
    void* ult = v -> vec + (v -> ce -1) * v -> tamElem;

    for (i = v -> vec; i < ult; i += v -> tamElem) {
        m = buscarMenor_ALU(i, ult, v -> tamElem, cmp);
        intercambiar_ALU(i, m, aux, v -> tamElem);
    }

    free(aux);

    return TODO_OK;
}

int vectorGuardarEnBin_ALU (Vector* v, const char* nomArch) {

    FILE* archBin = fopen(nomArch, "wb");

    if (!archBin)
        return ERR_ARCHIVO;

    fwrite(v -> vec, v -> tamElem, v -> ce, archBin);
    fclose(archBin);

    return TODO_OK;
}

void vectorOrdElimDup_ALU (Vector* v, Cmp_ALU cmp, Act_ALU act) {

    void* i = v -> vec;
    void* ult = v -> vec + (v -> ce -1) * v -> tamElem;
    int pos;
    void* dup;

    while (i < ult) {

        if (cmp(i, i + v -> tamElem) == 0) {

            dup = i + v -> tamElem;

            if (act)
                act(i, dup);

            pos = (dup - v -> vec) / v -> tamElem;

            vectorEliminarDePos_ALU(v, pos);

            ult -= v -> tamElem;

        } else
            i += v -> tamElem;
    }
}

void vectorEliminarDePos_ALU (Vector* v, int pos) {

    if (pos >= 0 && pos <= v -> ce -1) {

        void* posElim = v -> vec + pos * v -> tamElem;
        void* fin = v -> vec + v -> ce * v -> tamElem;

        void* posSiguiente = posElim + v -> tamElem;

        memmove(posElim, posSiguiente, fin - posSiguiente);
        v -> ce--;
    }
}


void vectorDestruir_ALU (Vector* v) {
    free(v -> vec);
    v -> vec = NULL;
    v -> cap = 0;
    v -> ce = 0;
    v -> tamElem = 0;
}

// Auxiliares

void* buscarMenor_ALU (void* ini, void* fin, size_t tamElem, Cmp_ALU cmp) {

    void *m = ini, *j;

    for (j = ini; j <= fin; j += tamElem) {
        if (cmp(j, m) < 0)
            m = j;
    }

    return m;
}

void intercambiar_ALU (void* elem1, void* elem2, void* aux, size_t tamElem) {
    memcpy(aux, elem1, tamElem);
    memcpy(elem1, elem2, tamElem);
    memcpy(elem2, aux, tamElem);
}
