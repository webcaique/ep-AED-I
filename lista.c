#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

ListaSequencial * cria_lista(){
	
	ListaSequencial * lista =  (ListaSequencial *) malloc (sizeof(ListaSequencial));
	lista->tamanho = 0;

	return lista;
}

void destroi_lista(ListaSequencial * lista){

	free(lista);
}


int busca(ListaSequencial * lista, Palavra* e){

	int i;
	// uasr i para contador de comparações
	for(i = 0; i < lista->tamanho; i++){

		if(strcmp(lista->array[i]->_palavra, e->_palavra) == 0) return i;
	}

	return -1; // caso não ache, usar o tamanho para indicar a quantidade de comparações
}

Boolean insere_lista(ListaSequencial * lista, Palavra* e){

	int i;

	if(i = busca(lista, e) >= 0){
		printf("\nAQUI1\n");
		if(lista->array[i]->linhas->list[lista->array[i]->linhas->size-1] < e->linhas->list[0]){
			printf("\nAQUI2\n");
			lista->array[i]->linhas->list = (int*)realloc(lista->array[i]->linhas->list, sizeof(int)*(lista->array[i]->linhas->size+1));
			lista->array[i]->linhas->list[lista->array[i]->linhas->size] = e->linhas->list[0]; 	
			lista->array[i]->linhas->size++;
		}
		printf("\nAQUI3\n");
		lista->array[i]->ocorrencias++;
		printf("\nAQUI3.5\n");
		free(e->linhas->list);
		free(e->linhas);
		free(e -> _palavra);
		free(e);
		printf("\nAQUI3.9\n");
		
		return TRUE;
	}

	printf("\nAQUI4\n");
	
	lista->tamanho++;
	lista->array = (Palavra**)realloc(lista->array, sizeof(Palavra*)*lista->tamanho);
	lista->array[lista->tamanho-1] = (Palavra*)malloc(sizeof(Palavra));
	lista->array[lista->tamanho-1] = e;
	printf("\nAQUI5\n");

	
	return FALSE;
}
