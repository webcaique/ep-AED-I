#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "defines.h"

ListaSequencial * cria_lista(){
	
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->tamanho = 0;

	return lista;
}

void destroi_lista(ListaSequencial * lista){

	free(lista);
}


int busca(ListaSequencial * lista, char* e){

	int i;
	// uasr i para contador de comparações
	for(i = 0; i < lista->tamanho; i++){

		if(strcmp(lista->array[i]->_palavra, e) == 0) return i;
	}

	return -1; // caso não ache, usar o tamanho para indicar a quantidade de comparações
}

Boolean insere_lista(ListaSequencial * lista, Palavra* e, int* num_comparacoes, int* contador_palavra){

	int i;
	
	(*num_comparacoes)++;
	//verifica se há já a palavra na estrutura
	if((i = busca(lista, e->_palavra)) >= 0){
		(*num_comparacoes)+= i > 0? i: lista->tamanho;
		// verifica se há nova linha
		if(lista->array[i]->linhas->list[lista->array[i]->linhas->size-1] < e->linhas->list[0]){
			lista->array[i]->linhas->list = (int*)realloc(lista->array[i]->linhas->list, sizeof(int)*(lista->array[i]->linhas->size+1));
			lista->array[i]->linhas->list[lista->array[i]->linhas->size] = e->linhas->list[0]; 	
			lista->array[i]->linhas->size++;
		}
		lista->array[i]->ocorrencias++;
		
		free(e->linhas->list);
		free(e->linhas);
		free(e -> _palavra);
		free(e);
		
		return TRUE;
	}
	(*contador_palavra)++;

	lista->tamanho++;
	lista->array = (Palavra**)realloc(lista->array, sizeof(Palavra*)*lista->tamanho); // novo tamalho do array
	lista->array[lista->tamanho-1] = (Palavra*)malloc(sizeof(Palavra));
	lista->array[lista->tamanho-1] = e;
	
	return FALSE;
}
