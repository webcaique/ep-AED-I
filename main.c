#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "defines.h"
#include "arvore.h"
#include "lista.h"

#define TAMANHO 10000

int main(int argc, char ** argv){

	char** linhas = NULL;
	
	
	FILE * in;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;
	int contador_linha;
	int i;
	int contador_palavra = 0;
	int num_comparacoes = 0;
	int p;

	Arvore* arv = NULL;
	ListaSequencial* lista = NULL;
	
	
	if(argc == 3) {
		arv = criar_arvore();
		lista = cria_lista();
		in = fopen(argv[1], "r"); /*Abri o arquivo para leitura*/
		


		contador_linha = 0; /*inicializa o contado de linhas*/
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char)); /*define o tamanho da "linha"*/

		/*Laço vai executar até ler todo o arquivo, em que vai passar cada linha na variável "linha"*/
		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			/*rintf("linha %03d: '%s'\n", contador_linha + 1, linha);*/

			/*fazemos uma copia do endereço que corresponde ao array de chars */
			/*usado para armazenar cada linha lida do arquivo pois a função 'strsep' */
			/*modifica o endereço do ponteiro a cada chamada feita a esta função (e */
			/*não queremos que 'linha' deixe de apontar para o inicio do array).*/

			copia_ponteiro_linha = linha;

			/*realoca o tamanho da vetor das linhas para cada linha adicional*/
			linhas = (char**)realloc(linhas,sizeof(char*)*(contador_linha+1));

			/*aloca o tamanho exato da linha para cada local do vetor*/
			linhas[contador_linha] = (char*)malloc(sizeof(char)*(((int)strlen(linha))+1));

			/*cópia da string*/
			strcpy(linhas[contador_linha], linha);

			// Irá ignorar barra(/) e travessão(-) no começo da cópia
			while( (palavra = strsep(&copia_ponteiro_linha, " /.-,():")) ){
				// caso termine em um espaço em branco, ele volta o loop para a próxima palavra
				if(strcmp(palavra, "") == 0) continue;
				for(p = 0; palavra[p] != '\0' && palavra[p] != '\n'; p++);
				if(palavra[p] == '\n') printf("%s", palavra);
				

				// Caso encontre a primeira letra em caixa alta, ela é reformatada para caixa baixa
				for(int i = 0; palavra[i] != '\0'; i++){
					if((int)palavra[i] < 91 && (int)palavra[i] > 64) palavra[i] += 32;
				}

				// antes de guardar a palavra em algum tipo de estrutura usada
				// para implementar o índice, será necessário fazer uma copia
				// da mesma, uma vez que o ponteiro 'palavra' aponta para uma 
				// substring dentro da string 'linha', e a cada nova linha lida
				// o conteúdo da linha anterior é sobreescrito.

				Palavra* pal = (Palavra*)malloc(((int)sizeof(Palavra)));
				pal->_palavra = (char*)malloc(((int)sizeof(char)*((int)strlen(palavra)+1)));
				strcpy(pal->_palavra, palavra);
				pal->linhas = (ListaLinhas*)malloc(((int)sizeof(ListaLinhas)));
				pal->linhas->list = (int*)malloc(((int)sizeof(int)));
				pal->linhas->list[0] = contador_linha;
				pal->linhas->size = 1;
				pal->ocorrencias = 1;

				
				if(strcmp(argv[2], "lista") == 0){
					insere_lista(lista, pal, &num_comparacoes);
				} else if(strcmp(argv[2], "arvore") == 0){
					insere_AVL(arv, pal, &num_comparacoes);
				}

				contador_palavra++;
			}

			contador_linha++;

		}
		
		printf("Arquivo: '%s' \n", argv[1]);
		printf("Tipo de indice: '%s' \n", argv[2]);
		printf("Numero de linhas no arquivo: %d \n", contador_linha);
		printf("Total de palavras unicas indexadas: %d \n", contador_palavra);
		if(arv->raiz != NULL) printf("Altura da arvore: %d\n", arv->raiz->altura);
		else if(lista) printf("Tamanho da lista: %d\n",lista->tamanho);
		printf("Numero de comparacoes realizadas para a construcao do indice: %d \n", num_comparacoes);


		/*Libera memória*/
		free(linha);
		free(copia_ponteiro_linha);
		free(palavra);
		fclose(in);


		/*buffer que vai armazenar todo a frase que o usário digitar*/
		char* buffer = (char*)malloc(sizeof(char)*128);
		// busca algo

		palavra = (char*)malloc(sizeof(char)*32);
		
		/*Armazena o comando a ser digitado pelo usuário ("busca", "fim")*/
		char* cmd = (char*)malloc(sizeof(char)*6);
		// controlador de índice

		num_comparacoes = 0;
		No* jorge;
		Palavra* busc;
		
		while(TRUE) {
			
			printf("> ");
			fgets(buffer, 128, stdin);
			for(i = 0; buffer[i] != '\n'; i++);
			buffer[i] = '\0';
			for(int i = 0; buffer[i] != '\0'; i++){
				if((int)buffer[i] < 91 && (int)buffer[i] > 64) buffer[i] += 32;
			}
			
			sscanf(buffer, "%s %s", cmd, palavra);
			
			if(strcmp(cmd, "busca") == 0){
				if(strcmp(argv[2], "arvore") == 0) {
					jorge = busca_AVL(arv, palavra, &num_comparacoes);
					if(jorge) busc = jorge->palavra;
					else busc = NULL;
				} else if(strcmp(argv[2], "lista") == 0){
					num_comparacoes = busca(lista, palavra);
					if(num_comparacoes >= 0){
						busc = lista->array[num_comparacoes];
						num_comparacoes++;
					}
					else {
						busc = NULL;
						num_comparacoes = lista->tamanho;
					}
					
				}
				
				if(busc){
					printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", busc->ocorrencias, busc->_palavra);
					for(int j = 0; j < busc->linhas->size; j++){
						printf("%05d: %s\n", busc->linhas->list[j]+1, linhas[busc->linhas->list[j]]);
					}
				} else {
					printf("Palavra '%s' nao encontrada.\n", palavra);
				}
				printf("Numero de comparacoes: %d\n", num_comparacoes);
				
				continue;
			}
			if(strcmp("fim", cmd) == 0) break;

			printf("Opcao invalida!\n");
			
		}

		return 0;
	}

	return 1;
}