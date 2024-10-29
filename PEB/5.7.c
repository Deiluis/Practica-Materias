#include <stdio.h>

typedef struct {
    int codigo;
    char descripcion[31];
    float precio;
} sProductos;

int main () {
    sProductos producto, *pProd;
    pProd = &producto;

    printf("Ingrese el codigo de producto: ");
    scanf("%d", &producto.codigo);
    fflush(stdin);
    printf("Ingrese la descripcion del producto: ");
    gets(producto.descripcion);
    printf("Ingrese el precio del producto: ");
    scanf("%f", &producto.precio);

    printf("Codigo: %d\n", (*pProd).codigo);
    printf("Descripcion: %s\n", (*pProd).descripcion);
    printf("Precio: $%.2f\n", (*pProd).precio);

    printf("Codigo: %d\n", pProd->codigo);
    printf("Descripcion: %s\n", pProd->descripcion);
    printf("Precio: $%.2f\n", pProd->precio);

    return 0;
}