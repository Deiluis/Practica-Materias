#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <stddef.h>


int ordenarArchivo(const char* nombreArchivo, size_t tamReg, Cmp cmp);
int fusionarArchivos(const char* nombreArchivo1, const char* nombreArchivo2, const char* nombreArchivoFus, size_t tamReg, Cmp cmp);
int eliminarDuplicadosArchivoOrd(const char* nombreArchivo, size_t tamReg, Cmp cmp, Actualizar actualizar);


#endif // ARCHIVO_H
