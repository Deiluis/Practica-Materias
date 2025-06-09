#define FORMATO_GENERAL "%[^;];%[^;];%[^;]"

#define BUFFER_TAM 255

#define PERIODO_TAM 11
#define NIVEL_TAM 31
#define INDICE_TAM 17

typedef struct {
    char periodo[PERIODO_TAM];
    char nivel[NIVEL_TAM];
    char indiceICC[INDICE_TAM];
} Registro;

// Registro* registroInicializar(Registro* reg);
// void registroDestruir(Registro* reg);