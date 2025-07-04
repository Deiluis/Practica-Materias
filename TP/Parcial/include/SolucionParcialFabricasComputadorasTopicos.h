#ifndef SOLUCION_1ER_PARCIAL_FABRICAS_COMPUTADORAS_H
#define SOLUCION_1ER_PARCIAL_FABRICAS_COMPUTADORAS_H


typedef struct
{
    char codigo[21];
    char descripcion[51];
    float precio;
    int stock;
}
Producto;


typedef struct
{
    int codigo;
    char apellidoYNombre[201];
}
Cliente;


int generarArchivos();
void mostrarArchivoProductosBin(const char* nombreArchivo);
void mostrarArchivoProductosTxt(const char* nombreArchivo);
void mostrarArchivoClientes(const char* nombreArchivo);
int procesarArchivos(
    const char* nombreArchivoProductosCor, const char* nombreArchivoProductosChu,
    const char* nombreArchivoClientesCor, const char* nombreArchivoClientesChu,
    const char* nombreArchivoProductosFus, const char* nombreArchivoClientesFus);
int productosTxtABin(const char* nombreArchivoTxt, const char* nombreArchivoBin);
int cmpProductos(const void* prod1, const void* prod2);
int cmpClientes(const void* cli1, const void* cli2);
void actualizarProductos(void* pvActualizado, const void* pvActualizador);


#endif // SOLUCION_1ER_PARCIAL_FABRICAS_COMPUTADORAS_H
