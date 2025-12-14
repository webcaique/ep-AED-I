#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvore.h"

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
	}
	else {
		/*
				_palavra = golfe
				linhas
				 list = [1,2, 4]
				 size = 3
				ocorrencias =>3

				_palavra = golfe
				linhas
				 list = [4]
				 size = 1
				ocorrencias =>1
		 */
		/*
		raiz => a nó;
		raiz->palavra => estrutra Palavra
		raiz->palavra->linhas => a estruturas ListaLinhas
		raiz->palavra->linhas->list => o vetor que vai armazenar as linhas em que a palavra aparece
		*/
		/*
		raiz->palavra->linhas->list => lista das linhas que a palavra apareceu
		novo->palavra->linhas->list[0] => a linha onde a palavra foi encontrada denovo
		0, raiz->palavra->linhas->size => início e fim da lista das linhas (tamanho), respectivamente
		*/
		if(!busca_binaria(raiz->palavra->linhas->list, novo->palavra->linhas->list[0], 0, raiz->palavra->linhas->size)){
			(raiz->palavra->linhas->size)++;
			raiz->palavra->linhas->list = (int*)realloc(raiz->palavra->linhas->list, ((int)sizeof(int))*(raiz->palavra->linhas->size));
			raiz->palavra->linhas->list[(raiz->palavra->linhas->size)-1] = novo->palavra->linhas->list[0];
		}
		(raiz->palavra->ocorrencias)++;

		free(novo->palavra->linhas->list);
		free(novo->palavra->linhas);
		free(novo->palavra->_palavra);
		free(novo->palavra);
		free(novo);
	}

	return FALSE;
}

Boolean insere_AVL(Arvore * arvore, Palavra* e){

	No * novo = (No *) malloc(sizeof(No));

	novo->palavra = e;
	novo->altura = 0;
	novo->dir = NULL;
	novo->esq = NULL;

	if(arvore->raiz) return insere_AVL_rec(arvore, arvore->raiz, NULL, novo);
		
	arvore->raiz = novo;
	return TRUE;
}