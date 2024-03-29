/* Eduardo Motta 1720334 3WA */
/* Luiz Fellipe Augusto 1711256 3WA */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include"gera_codigo.h"

typedef int (*funcp) (int x);


static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

void gera_codigo (FILE *f, void **code, funcp *entry){

	unsigned char* codigo;

	codigo = (unsigned char *)malloc(sizeof(unsigned char) * 2048);
	if(codigo == NULL){
		printf("falha na alocacao do vetor codigo\n"); 
		exit(1);	
	}

	*code = codigo;
	*entry = (funcp)codigo;

	int line = 1;
  	int  c;
  	int contador_codigo = 0;
  	int contador_atu = 0;

  	/* chamada de funcao e alocacao de variaveis na pilha  */
  	unsigned char chamada[8] = {0x55,0x48,0x89,0xe5,0x48,0x83,0xec,0x20};

  	unsigned char fim[2] = {0xc9,0xc3};

	/* cada vetor da matriz corresponde ao codigo de maquina 
	referente a retornar uma v,p ou $ respectivamente*/
	unsigned char vet_mov_ret[3][5] = {{0x8b,0x45,0x00},{0x89,0xf8},{0xb8, 0x00, 0x00, 0x00, 0x00}};

	//vetor auxiliar de tamanhos de vet_mov_ret
	 int size_vet_mov_ret[3] ={3,2,5};

  	//vetor que guarda o endereco do inicio de cada funcao
  	unsigned char** vet_fun =(unsigned char**) malloc(sizeof(unsigned char*) * 10);
  	int tam_index_fun = 10;

  	int index_fun = 0;
  	
	while ((c = fgetc(f)) != EOF){
	
		contador_atu = 0;

		char varpc[3] = {'v','p','$'};

	    int index_varpc_1= 0 , index_varpc_2 = 0;

	    switch (c) {
	      case 'f': { /* function */
	        char c0;
	        if (fscanf(f, "unction%c", &c0) != 1)
	         	error("comando invalido", line);
	        
	        

	        vet_fun[index_fun] = &codigo[contador_codigo]; index_fun++;
	        if(index_fun == tam_index_fun){
	        	tam_index_fun += 10;
	        	vet_fun = (unsigned char**)realloc(vet_fun,sizeof(unsigned char*) * tam_index_fun);
	        }


	        /* a ultima funcao que entry receber sera a certa*/
	        *entry = (funcp)&codigo[contador_codigo];

	        while(contador_atu < 8){
	        	codigo[contador_codigo] = chamada[contador_atu];
	        	contador_codigo++;
	        	contador_atu++;
	        }
	        
	        break;
	      }
	      case 'e': { /* end */
	        char c0;
	        if (fscanf(f, "nd%c", &c0) != 1)
	          error("comando invalido", line);
	      	while(contador_atu < 2){
	        	codigo[contador_codigo] = fim[contador_atu];
	        	contador_codigo++;
	        	contador_atu++;
	        }


	        
	        break;
	      }
	      case 'r': {  /* retorno incondicional */
	        int idx0;
	        char var0;
	        if (fscanf(f, "et %c%d", &var0, &idx0) != 2) 
	          error("comando invalido", line);
	       

		

	        while(varpc[index_varpc_1] != var0){
	          	index_varpc_1++; if(index_varpc_1 == 3){ exit(1);}
	          }

	        while(contador_atu < size_vet_mov_ret[index_varpc_1]){
	        	codigo[contador_codigo] = vet_mov_ret[index_varpc_1][contador_atu];contador_codigo++;contador_atu++;
	        }
		//atribução de valores caso estejamos lidando com v ou $
	        if(index_varpc_1 == 0){
	          	codigo[contador_codigo-1] = 0x100 - (idx0 * 4 + 4); 
	          }
	        if(index_varpc_1 == 2){
	          	contador_codigo -= 4; 
	          	contador_atu = 0;
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx0 >> 8*(contador_atu);
	        		contador_codigo++;
	        		contador_atu++;
	        	}
	          }
	        break;
	      }
	      case 'z': {  /* retorno condicional */
	        int idx0, idx1;
	        char var0, var1;
	        if (fscanf(f, "ret %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4) 
	          error("comando invalido", line);
	       
			
			/* cada vetor da matriz corresponde ao codigo de maquina 
			referente a comparar 0 a uma v,p ou $ respectivamente*/
	        unsigned char vet_cmp_op1[3][10] ={{0x83,0x7d,0x00,0x00},
	        				   {0x83,0xff,0x00},
	        				   {0x41, 0xba, 0x00, 0x00, 0x00, 0x00,0x41, 0x83, 0xfa, 0x00}};
			
	        int size_vet_cmp_op1[3] ={4,3,10};

	        while(varpc[index_varpc_1] != var0){
	          	index_varpc_1++; if(index_varpc_1 == 3){ exit(1);}
	          }

	        while(varpc[index_varpc_2] != var1){
	          	index_varpc_2++; if(index_varpc_2 == 3){ exit(1);}
	          }

	        while(contador_atu < size_vet_cmp_op1[index_varpc_1]){
	        	codigo[contador_codigo] = vet_cmp_op1[index_varpc_1][contador_atu];contador_codigo++;contador_atu++;
	        }

	        if(index_varpc_1 == 0){
	          	codigo[contador_codigo-2] = 0x100 - (idx0 * 4 + 4); 
	          }
	        if(index_varpc_1 == 2){
	          	contador_codigo -= 8; 
	          	contador_atu = 0;
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx0 >> 8*(contador_atu);
	        		contador_codigo++;
	        		contador_atu++;
	        	}
	          }
	          contador_codigo += 4;
	        
	       	codigo[contador_codigo] = 0x75;contador_codigo++;
	        codigo[contador_codigo] = size_vet_mov_ret[index_varpc_2] + 2;contador_codigo++;


	        contador_atu = 0;

	        while(contador_atu < size_vet_mov_ret[index_varpc_2]){
	        	codigo[contador_codigo] = vet_mov_ret[index_varpc_2][contador_atu];contador_codigo++;contador_atu++;
	        }

	        if(index_varpc_2 == 0){
	          	codigo[contador_codigo-1] = 0x100 - (idx1 * 4 + 4); 
	          }
	        if(index_varpc_2 == 2){
	          	contador_codigo -= 4; 
	          	contador_atu = 0;
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx1 >> 8*(contador_atu);
	        		contador_codigo++;
	        		contador_atu++;
	        	}
	          }

	        codigo[contador_codigo] = 0xc9;contador_codigo++;contador_atu++;
		codigo[contador_codigo] = 0xc3;contador_codigo++;contador_atu++;
	        break;
	      }
	      case 'v': {  /* atribuicao */
	        int idx0;
	        char c0;
	        if (fscanf(f, "%d = %c",&idx0, &c0) != 2)
	          error("comando invalido",line);

	        if (c0 == 'c') { /* call */
	          int fnum, idx1;
	          char var1;
	          if (fscanf(f, "all %d %c%d\n", &fnum, &var1, &idx1) != 3)
	            error("comando invalido",line);
	          

	          //salvar parametro antes de sobescrever edi
	          unsigned  char vet_save_pilha[3] ={0x89, 0x7d, 0xe8};

	          while(contador_atu < 3){
	          	codigo[contador_codigo] = vet_save_pilha[contador_atu];contador_codigo++;contador_atu++;
	          }

	          contador_atu = 0;

		  /* cada vetor da matriz corresponde ao codigo de maquina 
		  referente a mover uma v,p ou $ para o %edi respectivamente*/		
	          unsigned char vet_mov_arg[3][5] ={{0x8b,0x7d,0x00},{0x00},{0xbf,0x00,0x00,0x00,0x00}};

	          int size_vet_mov_arg[3] = {3,1,5};

	        while(varpc[index_varpc_2] != var1){
	          	index_varpc_2++; if(index_varpc_2 == 3){ exit(1);}
	          }

	        if(index_varpc_2 != 1){
	        	while(contador_atu < size_vet_mov_arg[index_varpc_2]){
	        		codigo[contador_codigo] = vet_mov_arg[index_varpc_2][contador_atu];contador_codigo++;contador_atu++;
	        	}
	        	if(index_varpc_2 == 0)
	        		codigo[contador_codigo-1] = 0x100 - (idx1 * 4 + 4);
	        	
	        	else{
	          	contador_codigo -= 4; 
	          	contador_atu = 0;
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx1 >> 8*(contador_atu);
	        		contador_codigo++;
	        		contador_atu++;
	        	}
	          }
	        }

	        contador_atu = 0;

	        int dif = (unsigned char *)vet_fun[fnum] - (unsigned char*)(&codigo[contador_codigo] + 5);

	        codigo[contador_codigo] = 0xe8;contador_codigo++;contador_atu++;
	         for(contador_atu=0; contador_atu<4; contador_atu++){
				codigo[contador_codigo] = dif;
				dif = dif >> 8;
				contador_codigo++;
			}

	        //movl %eax, pilha
	        //vet_ret_pilha[3] ={0x89,0x45,0x00} sendo 0x00  -> 0x100 - (idx0 * 4 + 4);;

	        codigo[contador_codigo] = 0x89;contador_codigo++;contador_atu++;
	        codigo[contador_codigo] = 0x45;contador_codigo++;contador_atu++;
	        codigo[contador_codigo] = 0x100 - (idx0 * 4 + 4);contador_codigo++;contador_atu++;

	        //movl -18(%rbp), %edi

		codigo[contador_codigo] = 0x8b;contador_codigo++;contador_atu++;
	        codigo[contador_codigo] = 0x7d;contador_codigo++;contador_atu++;
	        codigo[contador_codigo] = 0xe8;contador_codigo++;contador_atu++;
	        	        
	        
	    	}
	        else { /* op aritim */

	    	char vet_op[3] = {'+', '-', '*'};

	    	int index_op = 0;

	          int idx1, idx2;
	          char var1 = c0, var2, op;
	          if (fscanf(f, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
	            error("comando invalido", line);
	         
	          while(varpc[index_varpc_1] != var1){
	          	index_varpc_1++; if(index_varpc_1 == 3){ exit(1);}
	          }

	          while(vet_op[index_op] != op){
	          	index_op++; if(index_op == 3){ exit(1);}
	          }

	          while(varpc[index_varpc_2] != var2){
	          	index_varpc_2++; if(index_varpc_2 == 3){ exit(1);}
	          }
			
			/* cada vetor da matriz corresponde ao codigo de maquina 
			referente a mover uma v,p ou $ para o %r10d respectivamente */
	          unsigned char vet_mov_op1[3][6] = {{0x44 ,0x8b, 0x55,0x00},{0x41, 0x89, 0xfa},{0x41 ,0xba, 0x00, 0x00, 0x00, 0x00}};

	          int size_vet_mov_op1[3] = {4,3,6};

	          while(contador_atu < size_vet_mov_op1[index_varpc_1]){
	          	codigo[contador_codigo] = vet_mov_op1[index_varpc_1][contador_atu];contador_codigo++;contador_atu++;
	          }

	          if(index_varpc_1 == 0){
	          	codigo[contador_codigo-1] = 0x100 - (idx1 * 4 + 4); 
	          }
	          if(index_varpc_1 == 2){
	          	contador_codigo -= 4; 
	          	contador_atu = 0;
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx1 >> 8*(contador_atu);
	        		contador_codigo++;
	        		contador_atu++;
	        	}
	          }

	          contador_atu = 0;
			  
			/* o vetor de ordem 3 tem sua primeira ordem correspondente as operacoes de 
			soma,subtracao ou multiplicacao, a segunda ordem corresponde a uma v, p ou $ respectivamente. 
			
			
			todos os codigos fazem referencia a uma operacao a ser realizada com um varpc e armazenada no %r10d
			
			*/
	          unsigned char vet_op_op2[3][3][7] ={{{0x44,0x03,0x55,0x00},{0x41,0x01,0xfa},{0x41,0x81,0xc2,0x00,0x00,0x00,0x00}},
	          					{{0x44,0x2b,0x55,0x00},{0x41,0x29,0xfa},{0x41,0x81,0xea,0x00,0x00,0x00,0x00}},
	          					{{0x44,0x0f,0xaf,0x55,0x00},{0x44,0x0f,0xaf,0xd7},{0x45,0x69,0xd2,0x00,0x00,0x00,0x00}}};
		//matriz auxiliar de tamanhos de cada codigo	
	          int size_vet_op_op2[3][3] = {{4,3,7},{4,3,7},{5,4,7}};

		  //variavel para otimizar operacoes com constantes
	          int multi_byte = ((idx2 >= 128) | (idx2 <= -128)? 1:0);

	          if((index_varpc_2 == 2) & (multi_byte == 0)){ //condicional para operacoes aritimeticas com constantes menores que 128
	          	while(contador_atu < 4){
	          	codigo[contador_codigo] = vet_op_op2[index_op][2][contador_atu];contador_codigo++;contador_atu++;
	          } 
	          }
	          else{
	          	while(contador_atu < size_vet_op_op2[index_op][index_varpc_2]){
	          		codigo[contador_codigo] = vet_op_op2[index_op][index_varpc_2][contador_atu];contador_codigo++;contador_atu++;          	
	          }
	          }	
	          	
	          

	          if(index_varpc_2 == 0){
	          	codigo[contador_codigo-1] = 0x100 - (idx2 * 4 + 4);
	          }
	          if(index_varpc_2 == 2){
	          	if(multi_byte == 1){
	          		contador_atu = 0;
	          		contador_codigo -= 4; 
	          	while(contador_atu < 4){
	        		codigo[contador_codigo] = idx2 >> 8*(contador_atu);contador_codigo++;contador_atu++;
	        	}
	          	}
	          	else{ 
	          		codigo[contador_codigo-1] = idx2;
	          		if(index_op != 2) //correcao do codigo de maquina de operacoes aritimeticas com constantes menores que 128
	          			codigo[contador_codigo-3] = 0x83;
	          		else
	          			codigo[contador_codigo-3] = 0x6b;
	          	}
	          	
	          }  
			
	          contador_atu = 0;

		  //move o conteudo de %r10d para a variavel correspondente de idx0		
	          unsigned char vet_res[4] ={0x44,0x89,0x55,0x00};

	          while(contador_atu < 4){
	          	codigo[contador_codigo] = vet_res[contador_atu];contador_codigo++;contador_atu++;
	          }

	          codigo[contador_codigo-1] = 0x100 - (idx0 * 4 + 4);


	        }
	        break;
	      }
	      default: error("comando desconhecido", line);
	    }
    	line ++;
    	fscanf(f, " ");
  	}
  	codigo = (unsigned char *)realloc(codigo,sizeof(unsigned char) * contador_codigo);
	free(vet_fun);
}


void libera_codigo (void *p){
	free(p);
}


