#ifndef CARACTER_H
#define CARACTER_H

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') || (c) == 'Á' || (c) == 'á' || (c) == 'É' || (c) == 'é' || (c) == 'Í' || (c) == 'í' || (c) == 'Ó' || (c) == 'ó' || (c) == 'Ú' || (c) == 'ú' || (c) == 'Ñ' || (c) == 'ñ')

#define esDigito(c) ((c) >= '0' && (c) <= '9')

#endif //CARACTER_H
