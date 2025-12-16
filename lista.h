#include "defines.h"

// Estrutura para lista sequencial
typedef struct {

	Palavra** array;
	int tamanho;		

} ListaSequencial;

ListaSequencial * cria_lista();
void destroi_lista(ListaSequencial * lista);
int busca(ListaSequencial * lista, char* e);
Boolean insere_lista(ListaSequencial * lista, Palavra* e, int* num_comparacoes, int* contador_palavra);