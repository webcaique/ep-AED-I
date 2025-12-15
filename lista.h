#include "defines.h"

#define FALSE 0
#define TRUE 1

typedef struct {

	Palavra** array;
	int tamanho;		

} ListaSequencial;

ListaSequencial * cria_lista();
void destroi_lista(ListaSequencial * lista);
int busca(ListaSequencial * lista, char* e);
Boolean insere_lista(ListaSequencial * lista, Palavra* e);