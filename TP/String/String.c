#include "String.h"

// Primitivas
void stringCrear (String* str) {
    char* primerLetra = str -> contenido;

    str -> longitud = 0;
    *primerLetra = '\0';
}

size_t stringLongitud (const String* str) {
    return str -> longitud;
}

const char* stringContenido (const String* str) {
    return str -> contenido;
}

String stringCopiar (String* dest, const String* orig) {

    const char* letraActualOrig = orig -> contenido;
    char* letraActualDest = dest -> contenido;

    while (*letraActualOrig != '\0') {

        *letraActualDest = *letraActualOrig;

        letraActualOrig++;
        letraActualDest++;
    }

    *letraActualDest = '\0';
    dest -> longitud = letraActualDest - dest -> contenido;

    return *dest;
}

String stringCopiarLiteral (String* dest, const char* orig) {

    const char* letraActualOrig = orig;
    char* letraActualDest = dest -> contenido;
    int i = 0;

    while (*letraActualOrig != '\0' && i < MAX_LONGITUD) {

        *letraActualDest = *letraActualOrig;

        letraActualOrig++;
        letraActualDest++;
        i++;
    }

    *letraActualDest = '\0';
    dest -> longitud = i;

    return *dest;
}

String stringConcat (String* str1, const String* str2) {

    if (str1 -> longitud < MAX_LONGITUD) {
        const char* letraActualStr2 = str2 -> contenido;
        char* letraActualStr1 = str1 -> contenido + str1 -> longitud;

        while (*letraActualStr2 != '\0' && str1 -> longitud < MAX_LONGITUD) {
            *letraActualStr1 = *letraActualStr2;

            letraActualStr2++;
            letraActualStr1++;
            str1 -> longitud++;
        }

        *letraActualStr1 = '\0';
    }

    return *str1;
}

String stringSubstring (const String* str, const int inicio, const int fin) {

    String substr;
    *(substr.contenido) = '\0';
    substr.longitud = 0;

    if (inicio <= fin && inicio >= 0) {

        const char* letraActualStr = str -> contenido + inicio;
        char* letraActualSubstr = substr.contenido;
        int finAjustado = fin <= str -> longitud -1 ? fin : str -> longitud -1;
        const char* ult = str -> contenido + finAjustado;

        while (letraActualStr <= ult) {
            *letraActualSubstr = *letraActualStr;

            letraActualStr++;
            letraActualSubstr++;
            substr.longitud++;
        }

        *letraActualSubstr = '\0';
    }

    return substr;
}

String stringConcatLiteral (String* str1, const char* str2) {

    if (str1 -> longitud < MAX_LONGITUD) {
        const char* letraActualStr2 = str2;
        char* letraActualStr1 = str1 -> contenido + str1 -> longitud;

        while (*letraActualStr2 != '\0' && str1 -> longitud < MAX_LONGITUD) {
            *letraActualStr1 = *letraActualStr2;

            letraActualStr2++;
            letraActualStr1++;
            str1 -> longitud++;
        }

        *letraActualStr1 = '\0';
    }

    return *str1;
}

int stringComparar (const String* str1, const String* str2) {

    if (str1 -> longitud != str2 -> longitud)
        return str1 -> longitud - str2 -> longitud;

    const char* letraActualStr1 = str1 -> contenido;
    const char* letraActualStr2 = str2 -> contenido;

    while (*letraActualStr1 != '\0' && *letraActualStr1 - *letraActualStr2 == 0) {
        letraActualStr1++;
        letraActualStr2++;
    }

    return *letraActualStr1 - *letraActualStr2;
}

int stringCompararI (const String* str1, const String* str2) {

    if (str1 -> longitud != str2 -> longitud)
        return str1 -> longitud - str2 -> longitud;

    const char* letraActualStr1 = str1 -> contenido;
    const char* letraActualStr2 = str2 -> contenido;

    while (*letraActualStr1 != '\0' && aMayuscula(*letraActualStr1) - aMayuscula(*letraActualStr2) == 0) {
        letraActualStr1++;
        letraActualStr2++;
    }

    return aMayuscula(*letraActualStr1) - aMayuscula(*letraActualStr2);
}

int stringIndiceDe(const String* str, const String* exp) {

    int pos = -1;
    
    const char* letraActualStr = str -> contenido;
    const char* letraActualExp = exp -> contenido;

    if (exp -> longitud > 0) {
        int coincidencias = 0;

        while (*letraActualStr != '\0' && coincidencias < exp -> longitud) {

            if (*letraActualStr == *letraActualExp) {
                coincidencias++;
                letraActualExp++;
            } else {
                coincidencias = 0;
                letraActualExp = exp -> contenido;
            }
                
            letraActualStr++;
        }

        if (coincidencias == exp -> longitud)
            pos = letraActualStr - coincidencias - str -> contenido;
    }

    return pos;
}

bool stringIncluye(const String* str, const String* exp) {
    return stringIndiceDe(str, exp) > -1;
}

bool stringEmpiezaCon (const String* str, const String* exp) {
    return stringIndiceDe(str, exp) == 0;
}

bool stringTerminaCon (const String* str, const String* exp) {
    return stringIndiceDe(str, exp) == str -> longitud - exp -> longitud;
}

int stringIndiceDeLiteral(const String* str, const char* exp) {
    String strexp;
    *(strexp.contenido) = '\0';
    strexp.longitud = 0;

    stringCopiarLiteral(&strexp, exp);
    return stringIndiceDe(str, &strexp);
}

bool stringIncluyeLiteral(const String* str, const char* exp) {
    return stringIndiceDeLiteral(str, exp) > -1;
}

String stringAMayuscula (String* str) {

    char* letraActual = str -> contenido;

    while (*letraActual != '\0') {
        *letraActual = aMayuscula(*letraActual);
        letraActual++;
    }

    return *str;
}

String stringAMinuscula (String* str) {
    char* letraActual = str -> contenido;

    while (*letraActual != '\0') {
        *letraActual = aMinuscula(*letraActual);
        letraActual++;
    }

    return *str;
}

String stringCapitalizar (String* str) {
    char* primeraLetra = str -> contenido;
    *primeraLetra = aMayuscula(*primeraLetra);
    return *str;
}

char stringCaracterEn (const String* str, const int pos) {
    char letra = '\0';

    if (pos >= 0 && pos < str -> longitud) {
        const char* pLetra = str -> contenido + pos;
        letra = *pLetra;
    }

    return letra;
}

// Utilitarias
bool esMayuscula (char letra) {
    return letra >= 'A' && letra <= 'Z';
}

bool esMinuscula (char letra) {
    return letra >= 'a' && letra <= 'z';
}

char aMayuscula (char letra) {
    if (esMinuscula(letra))
        return letra - ('a' - 'A');

    return letra;
}

char aMinuscula (char letra) {
    if (esMayuscula(letra))
        return letra + ('a' - 'A');

    return letra;
}

size_t longitudLiteral (const char* str) {

    size_t longitud = 0;
    char* strP = (char*) str;

    while (*strP != '\0') {
        longitud++;
        strP++;
    }
        
    return longitud;
}