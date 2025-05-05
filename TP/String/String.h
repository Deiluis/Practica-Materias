#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include <stddef.h>
#include <stdbool.h>

#define MAX_LONGITUD 50

typedef struct
{
    char contenido[MAX_LONGITUD + 1];
    size_t longitud;
} String;

// Primitivas
void stringCrear (String* str);
size_t stringLongitud (const String* str);
const char* stringContenido (const String* str);
String stringCopiar (String* dest, const String* orig);
String stringCopiarLiteral (String* dest, const char* orig);
String stringConcat (String* str1, const String* str2);
String stringConcatLiteral (String* str1, const char* str2);
String stringSubstring (const String* str, const int inicio, const int fin);
int stringComparar (const String* str1, const String* str2);
int stringCompararI (const String* str1, const String* str2);
int stringIndiceDe (const String* str, const String* exp);
bool stringIncluye (const String* str, const String* exp);
bool stringEmpiezaCon (const String* str, const String* exp);
bool stringTerminaCon (const String* str, const String* exp);
int stringIndiceDeLiteral (const String* str, const char* exp);
bool stringIncluyeLiteral (const String* str, const char* exp);
String stringAMayuscula (String* str);
String stringAMinuscula (String* str);
String stringCapitalizar (String* str);
char stringCaracterEn (const String* str, const int pos);

// Utilitarias
bool esMayuscula (char letra);
bool esMinuscula (char letra);
char aMayuscula (char letra);
char aMinuscula (char letra);
size_t longitudLiteral (const char* str);

#endif // STRING_H_INCLUDED
