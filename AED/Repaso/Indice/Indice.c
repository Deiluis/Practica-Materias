#include "Indice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned tamIdx;
    FILE* archIdx;
} tIdxExtra;

void _recorrerIndiceInorden(tIndice* indice, Acc acc, void* extra);
void _guardarIndice(void* idx, void* extra);
int _cargarIndice(tIndice* indice, int limi, int lims, FILE* arch, void* reg, unsigned tamReg);
void _eliminarRaizIndice(tIndice* indice);
int _alturaIndice(const tIndice* indice);

void crearIndice(tIndice* indice) {
    *indice = NULL;
}

int generarIndice(tIndice* indice, const char* nomArchOr, const char* nomArchIdx, unsigned tamOr, unsigned tamIdx, Conv conv, Cmp cmp) {

    FILE *archOr, *archIdx;
    tIdxExtra idxExtra;
    void *reg, *idx;
    int pos = 0, cod = TODO_OK;

    archOr = fopen(nomArchOr, "rb");

    if (!archOr)
        return ERR_ARCHIVO;

    archIdx = fopen(nomArchIdx, "wb");

    if (!archIdx) {
        fclose(archOr);
        return ERR_ARCHIVO;
    }

    reg = malloc(tamOr);

    if (!reg) {
        fclose(archOr);
        fclose(archIdx);
        return SIN_MEM;
    }

    idx = malloc(tamIdx);

    if (!idx) {
        free(reg);
        fclose(archOr);
        fclose(archIdx);
        return SIN_MEM;
    }

    fread(reg, tamOr, 1, archOr);

    while (cod == TODO_OK && !feof(archOr)) {

        if (conv(idx, reg, pos))
            cod = ponerEnIndice(indice, idx, tamIdx, cmp);

        fread(reg, tamOr, 1, archOr);
        pos++;
    }

    if (cod == TODO_OK) {
        idxExtra.tamIdx = tamIdx;
        idxExtra.archIdx = archIdx;

        // Guardo en el archivo indice los registros.
        _recorrerIndiceInorden(indice, _guardarIndice, &idxExtra);
    }

    // Tenga error o no, vacia el indice.
    vaciarIndice(indice);

    free(reg);
    free(idx);
    fclose(archOr);
    fclose(archIdx);

    return TODO_OK;
}

int guardarIndice(const tIndice* indice, const char* nomArch, unsigned tamReg) {

    FILE* arch;
    tIdxExtra idxExtra;

    arch = fopen(nomArch, "wb");

    if (!arch)
        return ERR_ARCHIVO;

    idxExtra.tamIdx = tamReg;
    idxExtra.archIdx = arch;

    _recorrerIndiceInorden((tIndice*) indice, _guardarIndice, &idxExtra);

    fclose(arch);

    return TODO_OK;
}

int cargarIndice(tIndice* indice, const char* nomArch, unsigned tamReg) {

    FILE* arch = fopen(nomArch, "rb");
    int cantReg, cod;
    void* reg;

    if (!arch)
        return ERR_ARCHIVO;

    reg = malloc(tamReg);

    if (!reg) {
        fclose(arch);
        return SIN_MEM;
    }

    fseek(arch, 0l, SEEK_END);
    cantReg = ftell(arch) / tamReg;

    cod = _cargarIndice(indice, 0, cantReg -1, arch, reg, tamReg);

    if (cod != TODO_OK)
        vaciarIndice(indice);

    free(reg);
    fclose(arch);

    return cod;
}

bool buscarIndice(const tIndice* indice, void* info, unsigned tamInfo, Cmp cmp) {

    int comp;

    if (*indice == NULL)
        return false;

    while (*indice && (comp = cmp(info, (*indice) -> info)) != 0) {

        if (comp < 0)
            indice = &((*indice) -> izq);
        else
            indice = &((*indice) -> der);
    }

    if (comp != 0)
        return false;

    memcpy(info, (*indice) -> info, MIN(tamInfo, (*indice) -> tamInfo));

    return true;
}

int ponerEnIndice(tIndice* indice, const void* info, unsigned tamInfo, Cmp cmp) {

    tNodoA* nue;
    int comp;

    if (*indice == NULL) {

        nue = malloc(sizeof(tNodoA));

        if (!nue)
            return SIN_MEM;

        nue -> info = malloc(tamInfo);

        if (!nue -> info) {
            free(nue);
            return SIN_MEM;
        }

        nue -> tamInfo = tamInfo;
        nue -> der = nue -> izq = NULL;
        memcpy(nue -> info, info, tamInfo);

        *indice = nue;

        return TODO_OK;
    }

    comp = cmp(info, (*indice) -> info);

    if (comp == 0)
        return DUPLICADO;

    if (comp > 0)
        return ponerEnIndice(&((*indice) -> der), info, tamInfo, cmp);
    else
        return ponerEnIndice(&((*indice) -> izq), info, tamInfo, cmp);
}

bool sacarDeIndice(tIndice* indice, void* info, unsigned tamInfo, Cmp cmp) {

    int comp;

    if (*indice == NULL)
        return false;

    while (*indice && (comp = cmp(info, (*indice) -> info)) != 0) {

        if (comp < 0)
            indice = &((*indice) -> izq);
        else
            indice = &((*indice) -> der);
    }

    if (comp != 0)
        return false;

    memcpy(info, (*indice) -> info, MIN(tamInfo, (*indice) -> tamInfo));

    free((*indice) -> info);

    if (!(*indice) -> izq && !(*indice) -> der) {
        free(*indice);
        *indice = NULL;
    } else
        _eliminarRaizIndice(indice);

    return true;
}

void vaciarIndice(tIndice* indice) {

    if (*indice == NULL)
        return;

    vaciarIndice(&((*indice) -> izq));
    vaciarIndice(&((*indice) -> der));

    free((*indice) -> info);
    free(*indice);

    *indice = NULL;
}

void mostrarIndice(const tIndice* indice, Acc acc) {
    _recorrerIndiceInorden((tIndice*) indice, acc, NULL);
}

void _recorrerIndiceInorden(tIndice* indice, Acc acc, void* extra) {

    if (*indice == NULL)
        return;

    _recorrerIndiceInorden(&((*indice) -> izq), acc, extra);
    acc((*indice) -> info, extra);
    _recorrerIndiceInorden(&((*indice) -> der), acc, extra);
}

void _guardarIndice(void* idx, void* extra) {
    tIdxExtra* idxExtra = (tIdxExtra*) extra;
    fwrite(idx, idxExtra->tamIdx, 1, idxExtra->archIdx);
}

int _cargarIndice(tIndice* indice, int limi, int lims, FILE* arch, void* reg, unsigned tamReg) {

    int cod, pos = (limi + lims) / 2;
    tNodoA* nue;

    if (limi > lims)
        return TODO_OK;

    // Lee del archivo el registro.
    fseek(arch, pos * tamReg, SEEK_SET);
    fread(reg, tamReg, 1, arch);

    // Crea el nodo para guardar.
    nue = (tNodoA*) malloc(sizeof(tNodoA));

    if (!nue)
        return SIN_MEM;

    nue -> info = malloc(tamReg);

    if (!nue -> info) {
        free(nue);
        return SIN_MEM;
    }

    // Guarda la info.
    nue -> tamInfo = tamReg;
    nue -> der = nue -> izq = NULL;
    memcpy(nue -> info, reg, tamReg);

    *indice = nue;

    cod = _cargarIndice(&((*indice) -> izq), limi, pos -1, arch, reg, tamReg);

    if (cod != TODO_OK)
        return cod;

    return _cargarIndice(&((*indice) -> der), pos +1, lims, arch, reg, tamReg);
}

void _eliminarRaizIndice(tIndice* indice) {

    int hi, hd;
    tIndice* reemp;
    tNodoA* elim;

    if (*indice == NULL)
        return;

    reemp = indice;

    hi = _alturaIndice(&((*indice) -> izq));
    hd = _alturaIndice(&((*indice) -> der));

    if (hi > hd) {

        indice = &((*indice) -> izq);

        while ((*indice) -> der)
            indice = &((*indice) -> der);

    } else {

        indice = &((*indice) -> der);

        while ((*indice) -> izq)
            indice = &((*indice) -> izq);

    }

    (*reemp) -> info = (*indice) -> info; // No te olvides, no se copian los bytes, se engancha a otro lado el puntero.
    (*reemp) -> tamInfo = (*indice) -> tamInfo; // No te olvides de copiar el tamanio, pueden ser elementos de diferente tam.
    elim = *indice;

    *indice = (*indice) -> izq ? (*indice) -> izq : (*indice) -> der;

    free(elim);
}

int _alturaIndice(const tIndice* indice) {

    int hi, hd;

    if (*indice == NULL)
        return 0;

    hi = _alturaIndice(&((*indice) -> izq));
    hd = _alturaIndice(&((*indice) -> der));

    return MAX(hi, hd) +1;
}
