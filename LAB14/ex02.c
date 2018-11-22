#include <stdio.h>
#include <stdlib.h>

unsigned char codigo[6] = {0x83, 0xC7, 0x01,0x89,0xF8,0xC3};

typedef int (*funcp)(int x);


int main(void){
	int i;
	funcp f = (funcp)codigo;
	i = (*f)(10);
	
	printf("Funcao 10 retorna %d\n",i);
	
	
	return 0;
}
