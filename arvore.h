#include "defines.h"

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
No * busca_AVL_rec(No * no, char * e, int* num_comparacoes);
No * busca_AVL(Arvore * arvore, char * e, int* num_comparacoes);
