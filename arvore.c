#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvore.h"

//--------------- PRINT AVANÇADO --------------------------//


Boolean __debug__ = FALSE;
void debug_on() { __debug__ = TRUE; }
void debug_off() { __debug__ = FALSE; }

#define ROWS 256
#define COLS 4096

int balanco(No * no);

int display_rec(char ** buffer, No * no, int level, double h_position){

	char * ptr;
	int i, col, a, b;
	double offset;

	if(no){
		col = (int)(h_position * COLS);
		offset = 1.0 / pow(2, level + 2);

		ptr = buffer[1 + level * 3] + col;
		sprintf(ptr, "%s %d (%d)", no->palavra->_palavra, no->palavra->ocorrencias, balanco(no));
		*(ptr + strlen(ptr)) = ' ';

		if(no->esq || no->dir) *(buffer[2 + level * 3] + col + 1) = '|';

		if(no->esq){
		
			i = (int)((h_position - offset) * COLS);
			*(buffer[3 + level * 3] + 1 + i) = '|';
			i++;
			for(; i <= col; i++) *(buffer[3 + level * 3] + 1 + i) = '-';
		}
		
		if(no->dir){

			for(i = col; i < (int)((h_position + offset) * COLS); i++) *(buffer[3 + level * 3] + 1 + i) = '-';
			*(buffer[3 + level * 3] + 1 + i) = '|';
		}

		a = display_rec(buffer, no->esq, level + 1, h_position - offset);
		b = display_rec(buffer, no->dir, level + 1, h_position + offset);

		if(a > b) return a;
		return b;
	}

	return level;
}

void display_no(No * no){

	int i, j, r;

	char ** buffer = (char **) malloc(ROWS * sizeof(char *));

	for(i = 0; i < ROWS; i++) {

		buffer[i] = (char *) malloc((COLS + 1) * sizeof(char));

		for(j = 0; j < COLS; j++) buffer[i][j] = ' ';
		buffer[i][j] = '\0';
	}

	FILE* file = freopen("arquivo.out", "w", stdout);

	r = display_rec(buffer, no, 0, 0.5);

	if(__debug__) getchar();

	for(i = 0; i < 3 * r; i++) printf("%s\n", buffer[i]);
	printf("-----------------------------------------------------------------------------------------------\n");
}

void display(Arvore * arvore){

	display_no(arvore->raiz);
}

//------------------ Criação da árvore ------------------//
Arvore* criar_arvore(){
    Arvore* arv = (Arvore*)malloc(sizeof(Arvore));
    if(!arv) return NULL;
    arv->raiz = NULL;
    
    return arv;
}

//------------------ Impressão da árvore ------------------//
void imprime_rec(No * no){

	// percurso in-ordem para a impressão dos elementos

	if(no){
		imprime_rec(no->esq);
		printf("\n%s\n", no->palavra->_palavra);
		imprime_rec(no->dir);
	}
}

void imprime(Arvore * arvore){

	printf("Elementos na arvore:");
	imprime_rec(arvore->raiz);
	printf("\n");
}


//------------------ Busca ------------------//
No * busca_AVL_rec(No * no, char* e){

	if(no){
		
		if(strcmp(no->palavra->_palavra, e) == 0) return no;
		if(strcmp(no->palavra->_palavra, e)) return busca_AVL_rec(no->esq, e);
		return busca_AVL_rec(no->dir, e);
	}

	return NULL;
}

No * busca_AVL(Arvore * arvore, char* e){
	
	return busca_AVL_rec(arvore->raiz, e);
}

//--------------- Balanço --------------------//
int max(int a, int b){

	return a > b ? a : b;
}

int balanco(No * no){

	if(no->esq && no->dir) return (no->dir->altura) - (no->esq->altura);
	if(no->esq) return -1 * (no->esq->altura + 1);
	if(no->dir) return no->dir->altura + 1;
	return 0;
}

void atualiza_altura(No * no){

	// assuminos que todos os nós na (sub)arvore definida por 'no' já estão com suas alturas atualizadas.

	if(no->esq && no->dir) no->altura = max(no->esq->altura, no->dir->altura) + 1;
	else if(no->dir) no->altura = no->dir->altura + 1;
	else if(no->esq) no->altura = no->esq->altura + 1;
	else no->altura = 0;
}

No * rotacaoL(No * p){

	No * v;
	No * u = p->esq;
		
	if(balanco(u) == -1) { // rotação LL

		p->esq = u->dir;
		u->dir = p;
		p->altura -= 2;
		return u;
	}
	else if(balanco(u) == 1) { // rotação LR
	
		v = u->dir;

		u->dir = v->esq;
		v->esq = u;
		p->esq = v->dir;
		v->dir = p;

		p->altura -= 2;
		u->altura -= 1;
		v->altura += 1;

		return v;
	}

	return NULL;
}

No * rotacaoR(No * p){

	No * v;
	No * u = p->dir;
		
	if(balanco(u) == 1) { // rotação RR

		p->dir = u->esq;
		u->esq = p;
		p->altura -= 2;
		return u;
	}
	else if(balanco(u) == -1) { // rotação RL
	
		v = u->esq;

		u->esq = v->dir;
		v->dir = u;
		p->dir = v->esq;
		v->esq = p;

		p->altura -= 2;
		u->altura -= 1;
		v->altura += 1;

		return v;
	}

	return NULL;
}

//------------ INSERÇÃO ----------------------//

Boolean busca_binaria(int* v, int e, int ini, int fim){
	if(fim < ini) return FALSE;  
	int meio = (fim-ini)/2;
	if(v[meio] == e) return TRUE;
	if(v[meio] < e) return busca_binaria(v, e, ini, meio-1);
	return busca_binaria(v, e, meio+1, fim);
}

Boolean insere_AVL_rec(Arvore * arvore, No * raiz, No * pai, No * novo){

	Boolean r;
	No * rot;
	
	if(strcmp(novo->palavra->_palavra, raiz->palavra->_palavra) != 0){
		if(strcmp(novo->palavra->_palavra, raiz->palavra->_palavra) < 0){

			if(raiz->esq){

				r = insere_AVL_rec(arvore, raiz->esq, raiz, novo);
				atualiza_altura(raiz);
			
				if(abs(balanco(raiz)) >= 2) {

					printf("No %s desbalanceado! h = %d, bal = %d\n", raiz->palavra->_palavra, raiz->altura, balanco(raiz));

					rot = rotacaoL(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}
	
				return r;
			}
			else {
				raiz->esq = novo;
				if(!raiz->dir) raiz->altura = 1;
			}
		}
		else{
			if(raiz->dir){
		
				r = insere_AVL_rec(arvore, raiz->dir, raiz, novo);
				atualiza_altura(raiz);
			
				if(abs(balanco(raiz)) >= 2){

					printf("No %s desbalanceado! h = %d, bal = %d\n", raiz->palavra->_palavra, raiz->altura, balanco(raiz));

					rot = rotacaoR(raiz);

					if(pai){
						if(pai->esq == raiz) pai->esq = rot;
						if(pai->dir == raiz) pai->dir = rot;
					}
					else arvore->raiz = rot;
				}

				return r; 
			}
			else {
				raiz->dir = novo;
				if(!raiz->esq) raiz->altura = 1;
			}
		}
	
		return TRUE;
	} else {
		ListaLinhas* linhasRaiz = raiz->palavra->linhas;
		int linhaNovo = novo->palavra->linhas->list[0];
		if(!busca_binaria(linhasRaiz->list, linhaNovo, 0, linhasRaiz->size)){
			linhasRaiz->list = (int*)realloc(linhasRaiz->list, ++linhasRaiz->size);
			linhasRaiz->list[linhasRaiz->size-1] = linhaNovo;
		}
		raiz->palavra->ocorrencias++;
	}

	return FALSE;
}

Boolean insere_AVL(Arvore * arvore, Palavra* e){

	No * novo = (No *) malloc(sizeof(No));
	
	novo->palavra = e;
	novo->esq = novo->dir = NULL;
	novo->altura = 0;

	if(arvore->raiz) return insere_AVL_rec(arvore, arvore->raiz, NULL, novo);
		
	arvore->raiz = novo;
	return TRUE;
}