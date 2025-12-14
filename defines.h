#define TRUE 1
#define FALSE 0

typedef int Boolean;

// Lista que vai armazenar as linhas em que a palavra está
typedef struct {
    int* list;
    int size;
} ListaLinhas;

// Struct que vai armazenar dados da palavra: texto, a lista da linhas e quantidade de ocorrência
typedef struct {
    char* _palavra;
    ListaLinhas* linhas;
    int ocorrencias;
} Palavra;