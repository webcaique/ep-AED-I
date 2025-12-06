#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busca_binaria(int* v, int e, int ini, int fim){
	if(fim < ini) return 0;  
	int meio = (fim-ini)/2;
	if(v[meio] == e) return 1;
	if(v[meio] < e) return busca_binaria(v, e, ini, meio-1);
	return busca_binaria(v, e, meio+1, fim);
}

int main(){
    int v[] = {1,2,3,4,5,6,7,8,9};
    if(busca_binaria(v, 10, 0, 9)) printf("Encontrado");
    else printf("Não encontrado");
    printf("\n");

}