#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "gera_codigo.h"

typedef int (*funcp) (int x);

int main(void) {
  FILE *fp;
  unsigned char* code;
  funcp funcSBF;
  int res;
  //printf("cheguei 1\n");
  /* Abre o arquivo para leitura */
  fp = fopen("/home/eduardo/inf1018/inf1018-trab-2-2018.2/testes/teste22.txt", "r");
  if(fp == NULL){
    printf("falha abertura arq\n"); exit(1);
   //printf("cheguei 2\n");
  }
  /* Gera o codigo */
  gera_codigo(fp, &code, &funcSBF);
  /* Chama a função gerada */
  int i;
 //printf("cheguei 3\n");
  for(i=0;i<200;i++){
  	printf("%02x ", code[i]);
  	if(i % 10 == 0)
  		printf("\n");
  }
 //printf("cheguei 4\n");
  printf("\n");
  
    printf("entry = %02lx", (unsigned char*)funcSBF - (unsigned char*)code);
  printf("\n");

  res = (*funcSBF)(0);

  printf("res = %d\n", res);
  /* Libera a memória utilizada */
  //libera_codigo(code);
  return 0;
  
}
