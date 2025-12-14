#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvore.h"
#include "lista.h"

#define TAMANHO 10000

int main(int argc, char ** argv){

	FILE * in;
	char** linhas;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;
	int contador_linha;
	int i;
	

	if(argc == 2) {

		in = fopen(argv[1], "r");

		printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0;
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char));
		ListaSequencial* lista = cria_lista();

		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			//printf("linha %03d: '%s'\n", contador_linha + 1, linha);

			// fazemos uma copia do endereço que corresponde ao array de chars 
			// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
			// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
			// não queremos que 'linha' deixe de apontar para o inicio do array).

			copia_ponteiro_linha = linha;

			linhas = (char**)realloc(linhas,sizeof(char*)*(contador_linha+1));
			linhas[contador_linha] = (char*)malloc(sizeof(char)*(TAMANHO+1));
			strcpy(linhas[contador_linha], linha);


			while( (palavra = strsep(&copia_ponteiro_linha, " /-")) ){
				if(strcmp(palavra, "") == 0) continue;
				for(i = 0; palavra[i] != '\0' && palavra[i] != '.' && palavra[i] != ','; i++);
				if(palavra[i] != '\0'){
					palavra[i] = '\0';
					palavra[i+1] = ' ';
				}

				if((int)palavra[0] < 91) palavra[0] += 32; 

				// antes de guardar a palavra em algum tipo de estrutura usada
				// para implementar o índice, será necessário fazer uma copia
				// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
				// substring dentro da string 'linha', e a cada nova linha lida
				// o conteúdo da linha anterior é sobreescrito.

				printf("\t\t'%s'\n", palavra);

				Palavra* pal = (Palavra*)malloc(((int)sizeof(Palavra)));
				pal->_palavra = (char*)malloc(((int)sizeof(char)*((int)strlen(palavra)+1)));
				strcpy(pal->_palavra, palavra);
				pal->linhas = (ListaLinhas*)malloc(((int)sizeof(ListaLinhas)));
				pal->linhas->list = (int*)malloc(((int)sizeof(int)));
				pal->linhas->list[0] = contador_linha;
				pal->linhas->size = 1; 
				pal->ocorrencias = 1;


				
				insere_lista(lista,e);
			}

			contador_linha++;

		}

		printf(">>>>> Arquivo carregado!\n");

		return 0;
	}


	return 1;
}