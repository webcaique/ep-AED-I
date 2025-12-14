#include "defines.h"

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

// Nó que vai armazenar a palavra
typedef struct _no {
    Palavra* palavra;
    int altura;
    struct _no* esq;
    struct _no* dir;
} No;

// Árvore
typedef struct {
    No* raiz;
} Arvore;

Arvore* criar_arvore();
Boolean insere_AVL(Arvore * arvore, Palavra* e);
No * busca_AVL_rec(No * no, char * e);
No * busca_AVL(Arvore * arvore, char * e);
