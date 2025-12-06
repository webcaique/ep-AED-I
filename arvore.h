#include "defines.h"

typedef struct {
    int* list;
    int size;
} ListaLinhas;

typedef struct {
    char* _palavra;
    ListaLinhas* linhas;
    int ocorrencias;
} Palavra;

typedef struct _no {
    Palavra* palavra;
    int altura;
    struct _no* esq;
    struct _no* dir;
} No;

typedef struct {
    No* raiz;
} Arvore;

Arvore* criar_arvore();
Boolean insere_AVL(Arvore * arvore, Palavra* e);