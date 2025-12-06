#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "defines.h"
#include "arvore.h"

#define TAMANHO 10000

int main(int argc, char ** argv){

	FILE * in;
	char** linhas = NULL;
	char * linha;
	char * copia_ponteiro_linha;
	char * quebra_de_linha;
	char * palavra;
	int contador_linha;
	int i;

	Arvore* arv = criar_arvore();

	if(argc == 2) {

		in = fopen(argv[1], "r"); // Abri o arquivo para leitura

		printf(">>>>> Carregando arquivo...\n");

		contador_linha = 0; // inicializa o contado de linhas
 		linha = (char *) malloc((TAMANHO + 1) * sizeof(char)); // define o tamanho da "linha"

		// Laço vai executar até ler todo o arquivo, em que vai passar cada linha na variável "linha"
		while(in && fgets(linha, TAMANHO, in)){
			
			if( (quebra_de_linha = strrchr(linha, '\n')) ) *quebra_de_linha = 0;

			//printf("linha %03d: '%s'\n", contador_linha + 1, linha);

			// fazemos uma copia do endereço que corresponde ao array de chars 
			// usado para armazenar cada linha lida do arquivo pois a função 'strsep' 
			// modifica o endereço do ponteiro a cada chamada feita a esta função (e 
			// não queremos que 'linha' deixe de apontar para o inicio do array).

			copia_ponteiro_linha = linha;

			// realoca o tamanho da vetor das linhas para cada linha adicional
			linhas = (char**)realloc(linhas,sizeof(char*)*(contador_linha+1));

			// aloca o tamanho exato da linha para cada local do vetor
			linhas[contador_linha] = (char*)malloc(sizeof(char)*(((int)strlen(linha))+1));

			// cópia da string
			strcpy(linhas[contador_linha], linha);

			// Irá ignorar barra(/) e travessão(-) no começo da cópia
			while( (palavra = strsep(&copia_ponteiro_linha, " /-.,")) ){
				// caso termine em um espaço em branco, ele volta o loop para a próxima palavra
				if(strcmp(palavra, "") == 0) continue;

				// Caso encontre a primeira letra em caixa alta, ela é reformatada para caixa baixa
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

				insere_AVL(arv, pal);

			}

			contador_linha++;

		}

		// Libera memória
		free(linha);
		free(copia_ponteiro_linha);
		free(palavra);
		fclose(in);

		printf(">>>>> Arquivo carregado!\n");

		// buffer que vai armazenar todo a frase que o usário digitar
		char* buffer = (char*)malloc(sizeof(char)*128);

		palavra = (char*)malloc(sizeof(char)*32);
		
		// Armazena o comando a ser digitado pelo usuário ("busca", "fim")
		char* cmd = (char*)malloc(sizeof(char)*6);
		// controlador de índice
		int i;
		while(TRUE) {
			
			printf("> ");
			fgets(buffer, 128, stdin);
			for(i = 0; buffer[i] != '\n'; i++);
			buffer[i] = '\0';
			sscanf(buffer, "%s %s", cmd, palavra);
			if(strcmp(cmd, "busca") == 0){
				continue;
			}

			if(strcmp("fim", cmd) == 0) break;
			printf("Opcao invalida!\n");
		}

		return 0;
	}

	return 1;
}