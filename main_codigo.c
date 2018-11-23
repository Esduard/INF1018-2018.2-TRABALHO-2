#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "gera_codigo.h"

typedef int (*funcp) (int x);

int main(void) {
  FILE *fp;
  unsigned char * code;
  funcp funcSBF;
  int res;
  /* Abre o arquivo para leitura */
  fp = fopen("/home/eduardo/inf1018/Trab2/testes/teste5.txt", "r");
  
  /* Gera o codigo */
  gera_codigo(fp, &code, &funcSBF);
  /* Chama a função gerada */
  int i;

  for(i=0;i<100;i++){
  	printf("%02x ", code[i]);
  	if(i % 10 == 0)
  		printf("\n");
  }


  res = (*funcSBF)(9);

  printf("res = %d\n", res);
  /* Libera a memória utilizada */
  //libera_codigo(code);
  
}