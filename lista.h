#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef int Elemento;

typedef struct {
    int* list;
    int size;
} ListaLinhas;

typedef struct {
    char* _palavra;
    ListaLinhas* linhas;
    int ocorrencias;
} Palavra;
	
typedef struct {

	Palavra** array;
	int tamanho;		

} ListaSequencial;

ListaSequencial * cria_lista();
void destroi_lista(ListaSequencial * lista);
int busca(ListaSequencial * lista, Palavra* e);
Boolean insere_lista(ListaSequencial * lista, Palavra* e);