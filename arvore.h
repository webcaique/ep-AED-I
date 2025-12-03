#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Boolean;

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
No * busca_AVL(Arvore * arvore, char* e);
void imprime(Arvore * arvore);
void display(Arvore * arvore);
void debug_on();
void debug_off();
