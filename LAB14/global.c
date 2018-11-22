#include <stdio.h>



unsigned char codigo[6] = {0x83,0xc7, 0x01, 0x89, 0xf8, 0xc3}; 

typedef int (*funcp) (int x); /* funcp eh um ponteiro para funcao que recebe como argumento um int e retorna um int */


int add (int x){
	return x + 1;
}

int main(void){

	funcp f = (funcp)codigo;

	int i = (*f)(10);

	printf("i = %d\n", i);


	
	codigo[0] = 0xe8;

	int dif = (unsigned char *)&add - (codigo + 5);
	printf("dif = %d\n", dif);

	codigo[1] = dif;
	printf("cod 1 = %x\n", codigo[1]); 
	codigo[2] = dif >> 8;
	codigo[3] = dif >> 16;
	codigo[4] = dif >> 24;
	
	f = (funcp)codigo;

	i = (*f)(10);

	printf("i = %d\n", i);

	return 0;
}
