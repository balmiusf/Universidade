#include <string.h>
#include <stdio.h>	
#include <stdbool.h>
#include <stdlib.h>
#include "diskbuffer.h"
#define TEMPSIZE 100000			//tamanho do array temporario de cestos
#define HASHTABLE_SIZE 200003	//tamanho da hashtable
#define PROD_ARRAY_SIZE 10      //tamanho do array temporario de produtos
#define OPERATION_SIZE 2        //array de operacoes
#define CESTO_NAME_SIZE 10      // tamanho maximo de caracteres que o nome de um cesto pode ter

/*
Fuction Name: Hash_from_disk

Description: Função que escreve a informação necessaria do disco referente a uma struct hashtable.
 a ordem da informação no disco está ordenada por:
array de structs diskbuffer | int (referente a idade) | int (referente a carga da hashtable).
 Em cada struct, usa a função EAtoDB(disk.c) para 
transformar a informação em structs diskbuffer, escrevendo-as depois no disco.

Arguments:apontador para struct hashtable. string contendo o nome do ficheiro binario.

return value: -
*/

void Hash_to_disk(struct hashtable *hashtable, char filename[])
{	
	 struct diskbuffer *disk = malloc(sizeof(struct diskbuffer)); // apontador para a struct diskbuffer onde vai ser guardada a informação para escrever do disco
	  FILE *file= fopen(filename, "w");
	  if (file !=NULL)	
	  {
	  	//coversão da informaçao da hashtable em structs diskbuffers, escrevendo-as uma a uma o disco
	  	for ( int x = 0; x < HASHTABLE_SIZE; x++ )
	  	{
	  		struct diskbuffer *disk = malloc(sizeof(struct diskbuffer));
	  		disk=EAtoDB(hashtable->tabela[x]);
	  		fwrite(disk, sizeof(struct diskbuffer), 1, file);
	  	}
	  	//escrita do resto da informação
	  	int op=hashtable->op;
		int ocupados=hashtable->ocupados;
		fwrite(&op, sizeof(int), 1, file);
		fwrite(&ocupados, sizeof(int), 1, file);
	  }
  fclose(file);
  free(disk);
}


/*
Fuction Name: Hash_from_disk

Description: Função que carrega a informação necessaria do disco referente a uma struct hashtable. 
a ordem da informação no disco está ordenada por:
array de structs diskbuffer | int (referente a idade) | int (referente a carga da hashtable). 
Em cada struct, usa a função DBtoEA(disk.c) para 
transformar a informação em structs elementoTabela, 
escrevendo-os depois no array elementoTabela da hashtable. 

Arguments:string contendo o nome do ficheiro binario.

return value: apontador para uma struct hashtable.
*/

struct hashtable *Hash_from_disk(char filename[])
{

    struct diskbuffer *Diskread = malloc(sizeof(struct diskbuffer)); // struct onde vai ser guardada a informação lida do disco
	struct hashtable *table=hashtable_new(); // struct onde vai ser escrita a informãção convertida
	FILE *file= fopen(filename, "r");

    if (file != NULL) 
    {
    	//ciclo para conversão e escrita da informação, usando a função DBtoEA()(disk.c)
       for ( int x = 0; x < HASHTABLE_SIZE; x++ ) 
       {
    		fread(Diskread, sizeof(struct diskbuffer), 1, file);
    		if(Diskread->exist!=66)
  		  		table->tabela[x]=DBtoEA(Diskread);
    	
    	}

    	//leitura do resto da informação
    	int op;
    	int ocupados;	
    	fread(&op, sizeof(int), 1, file);
    	fread(&ocupados,sizeof(int),1,file);
    	table->op=op;
    	table->ocupados=ocupados;
    	fclose(file);
    	free(Diskread);
	
	}

	return table;
}
// apos executada uma operaçao, incrementar a idade de todos os cestos da hashtable
void act_cest(int op, struct cesto *cesto)
{	
	cesto->idade=op;
}

/*
Function name: criacao_cesto
Description: insere um cesto na hashtable, se ja existir na hashtable indica que existe
Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void criacao_cesto(struct hashtable *hashtable, char id[])
{
	if(!hashtable_insert(hashtable,id)) 
		printf("+ cesto %s existente\n",id);
	else
		printf("+ cesto %s criado\n",id);
}

/*
Function name: introducao_cesto
Description: introduz um produto no cesto
	procura na hashtable pelo cesto e procura o na lista de produtos
	se encontrar incrementa quantidade, caso contrario e inserido na lista
Arguments: apontador da hashtable, nome do cesto
return value: nada
*/

void introducao_cesto(struct hashtable *hashtable, char id[], long long code, short amount, float price)
{
	struct cesto *cesto = hashtable_find(hashtable,id); //procura o cesto
	if (cesto == NULL)
		printf("+ cesto %s inexistente\n",id); 
	else
	{
		struct prod *prod = prod_contains(cesto->list_prod, code);

		if (prod != NULL)	
			prod->quantity += amount; //se existir incrementa
		else
			list_prod_insert(cesto->list_prod, code, amount, price); //adiciona o produto a lista caso contrario
	
		printf("+ %d unidade(s) de %010lld introduzida(s) no cesto %s\n", amount, code, id);
		act_cest(hashtable->op,cesto); //actualiza
	}
}

/*
Function name: cancelemento_encomenda
Description: se o existir na hashtable e' removido
Arguments: apontador da hashtable, nome do cesto
return value: nada
*/

void cancelamento_encomenda(struct hashtable *hashtable, char id[])
{
	struct cesto *cesto = hashtable_find(hashtable,id); //procura o cesto
	if(cesto != NULL)
	{
		hashtable_remove(hashtable,id); //se existir remove (cancela a encomenda)
		printf("+ cesto %s cancelado\n",id);
	}
	else
		printf("+ cesto %s inexistente\n",id);
}

/*
Function name: retirar_artigos
Description: se o cesto existir na hashtable procura o produto
se o produto existir e a quantidade a remover for inferior a quantidade existente faz-se a diferenca,
caso contrario retorna mensagem de erros se a quantidade 
a remover for igual a quantidade exitente entao remove-se
o produto da lista
Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void retirar_artigos(struct hashtable *hashtable, char id[], long long codigo, short amount)
{
	struct cesto *cesto = hashtable_find(hashtable,id); //procura o cesto
	if(cesto != NULL)
	{
		struct prod *prod = prod_contains(cesto->list_prod, codigo); //procura o artigo
		if(prod == NULL) //se nao existir
			printf("+ produto %010lld ausente do cesto %s\n",codigo, id);
		else
		{
			if(prod->quantity < amount) //se a quantidade a remover for maior a quantidade existente
				printf("+ quantidade de %010lld no cesto %s menor que %d\n",codigo,cesto->cesto,amount);
			else // caso contrario 
			{
				prod->quantity = prod->quantity - amount;
				printf("+ %d unidade(s) de %010lld retirada(s) do cesto %s\n",amount,codigo,id);
				if(prod->quantity == 0) //se for igual a 0, retira o produto
					list_prod_remove(cesto->list_prod, codigo);
			}
		}
		act_cest(hashtable->op,cesto);
	}
	else
		printf("+ cesto %s inexistente\n",id);
}

// faz sort por codigo de produto
void insertionSort_VC(struct prod *v[], int size)
{
	struct prod *aux;
	for (int i = 1; i < size; i++)
	{
		aux = v[i];
		int j = i;
		while ( j > 0 && aux->code < v[j-1]->code)
		{
			v[j]=v[j-1];
			j--;
 		}
 		
		v[j] = aux;
	}
}

/*
Function name: visualizacao_cesto

Description: procura o cesto na hashtable
se existe e a lista de produtos estiver vazia retorna mensagem que esta vazio
se nao esiver vazia copia para um array temporario todo o conteudo da lista
e aplica-se o insertion sort e imprime o conteudo

Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void visualizacao_cesto(struct hashtable *hashtable, char id[] )
{
	float valortotal = 0; // valor total do cesto de compras
	struct cesto *cesto = hashtable_find(hashtable, id);
	struct prod *array_prod[PROD_ARRAY_SIZE];  // array temporario 
	if(cesto != NULL && !list_prod_empty(cesto->list_prod))
	{
		printf("VC %s\n",id);
		
		//adiciona todos os produtos ao array para o preparar para o sort
		for(int i = 0; i < cesto->list_prod->size; i++)
			array_prod[i] = list_prod_nth(cesto->list_prod,i); 

		insertionSort_VC(array_prod,cesto->list_prod->size);

		for(int i = 0; i < cesto->list_prod->size; i++) 
		{
			 printf("%010lld %3hu %8.2f %8.2f\n", array_prod[i]->code, array_prod[i]->quantity,
			 array_prod[i]->unit_price,
			 array_prod[i]->quantity * array_prod[i]->unit_price);
      		
      		valortotal+=array_prod[i]->quantity * array_prod[i]->unit_price;
		}
  		printf("%.2f\n",valortotal);
	}

	else if(cesto != NULL && list_prod_empty(cesto->list_prod)) // se a lista estiver vazia
		printf("+ cesto %s vazio\n", id);
	else
		printf("+ cesto %s inexistente\n",id);

	if(cesto != NULL)
		act_cest(hashtable->op,cesto); // actualiza a idade 
}

/*
Function name: realizacao_encomenda

Description: procura o cesto na hashtable
se o cesto existe e lista estiver vazia retorna mensagem de erro
se o cesto existe a lista estiver nao vazia remove da hashtable
se o cesto existe actualiza a idade

Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void realizacao_encomenda(struct hashtable *hashtable, char id[])
{
	struct cesto *cesto = hashtable_find(hashtable, id);
	if(cesto != NULL && !list_prod_empty(cesto->list_prod)) // se a lista nao estiver vazia
	{
		hashtable_remove(hashtable,id); //remove o cesto
		printf("+ efectuada venda do cesto %s\n",id);
	}
	else if(cesto != NULL && list_prod_empty(cesto->list_prod)) // se a lista estiver vazia
		printf("+ cesto %s vazio\n", id);
	else
		printf("+ cesto %s inexistente\n",id);

	if(cesto != NULL)
		act_cest(hashtable->op,cesto);
}

// sort pelas idades
void insertionSort_LC(struct cesto *v[], int size)
{
	struct cesto *aux;
	for (int i = 1; i < size; i++)
	{
		aux = v[i];
		int j = i;
		while ( j > 0 && aux->idade < v[j-1]->idade)
		{
			v[j]=v[j-1];
			j--;
 		}
 		
		v[j] = aux;
	}
}

/*
Function name: limpeza_cesto

Description: percorre a hashtable a procura de cestos com idade acima de "idade"
insere esses cestos num array, aplica-se o insertion sort e remove-se todos
esses cestos no array

Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void limpeza_cesto(struct hashtable *hashtable, int idade)
{	
	int tempcounter=0;
	struct cesto *cesto[TEMPSIZE]; // array temporario de cestos
	for(int i = 0; i < HASHTABLE_SIZE; i++) 
	{
		if(hashtable->tabela[i] != NULL && !hashtable->tabela[i]->deleted)
		{
			if(hashtable->tabela[i]->cesto->idade < (hashtable->op - idade))
			{
				// se a condicao se verificar adicionar ao array 
            	cesto[tempcounter] = hashtable->tabela[i]->cesto; 
            	tempcounter++;
            }
		}
	}

	insertionSort_LC(cesto,tempcounter); // sort

	if(tempcounter == 0)
	  printf("+ sem cestos com idade superior a %d\n", idade);
	else
	{
		printf("LC %hu\n",idade);
		for ( int x= 0; x < tempcounter; x++)
		{
	  		printf("%s\n",cesto[x]->cesto);
	       	hashtable_remove(hashtable,cesto[x]->cesto); // cada vez que imprime remove da hashtable o cesto
		}
	}
}

int main()
{
	
	struct hashtable *table=Hash_from_disk("data"); 
	char cesto_name[CESTO_NAME_SIZE+1], operation[OPERATION_SIZE+1];
	short quantity;
	long long code;
	int idade;
	float price;
	
	// ler inputs do ficheiros
	// primeiro scan, verifica o tipo de operacao
	// as restantes verificam o resto dos inputs
	while(scanf("%s",operation) == 1) 
	{
		if (strcmp(operation,"CC") == 0) 
		{
			scanf("%s",cesto_name);
			criacao_cesto(table, cesto_name);
		} 
		else if (strcmp(operation,"IC") == 0) 
		{
			scanf("%s %010lld %hu %f",cesto_name,&code,&quantity,&price);
			introducao_cesto(table, cesto_name,code,quantity,price);
		} 
		else if (strcmp(operation,"RC") == 0) 
		{
			scanf("%s %010lld %hu",cesto_name,&code,&quantity);
			retirar_artigos(table, cesto_name,code,quantity);
		} 
		else if (strcmp(operation,"VC") == 0)
		{
			scanf("%s",cesto_name);
			visualizacao_cesto(table, cesto_name);
		}
		else if (strcmp(operation,"EC") == 0) 
		{
			scanf("%s",cesto_name);
			realizacao_encomenda(table, cesto_name);
		} 
		else if (strcmp(operation,"XC") == 0) 
		{
			scanf("%s",cesto_name);
			cancelamento_encomenda(table,cesto_name);
		} 
		else if (strcmp(operation,"LC") == 0)
		{
			scanf("%d",&idade);
			limpeza_cesto(table, idade);
		} else // se a operacao for "XX" 
			break;

		table->op++; // ao fim de cada operacao incrementa o numero de operacoes feitas ate agora
 	}

	Hash_to_disk(table,"data");
	destroy_hashtable(table);

	return 0;
}
