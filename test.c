#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char palavra1[] = {'b','u','s','c','a','\0'};
    char palavra2[] = {'b','u','s','c','a',' ','\0'};
    printf("\n%d\n\n", strncmp(palavra1, palavra2, 5));
}