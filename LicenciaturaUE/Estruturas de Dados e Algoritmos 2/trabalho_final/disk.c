#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "diskbuffer.h"
#define CESTO_NAME_SIZE 10 // tamanho maximo de caracteres que o nome de um cesto pode ter
#define PROD_ARRAY_SIZE 10 // tamanho maximo de numero de produtos num array


struct elementoTabela *elementoTabela_new(char nome[]);
struct prod *prod_new();
struct list_prod *list_prods_new();

/*
Fuction Name: EAtoDB
Description: Função recebe um apontador para uma struct elementoTabela, e devovle um apontador para uma struct diskbuffer,
passando a informação de uma struct para outra.
Arguments: um apontador para struct elementoTabela.
return value: um apontador para struct diskbuffer
*/

struct diskbuffer *EAtoDB(struct elementoTabela *EA){

	struct diskbuffer *temp = malloc(sizeof(struct diskbuffer)); //apontador para a struct a ser returnado
	struct prod *delete; // apontador usado na passagem de produtos da lista de produtos para um array prod_buffer
	 if(EA == NULL)
	{
		temp->exist = 66;// flag para controlar se o elementoTabela contem informação.
	}
	else
	{
	// igualar os valores das duas structs
	temp->deleted = EA->deleted;
	strcpy(temp->cesto,EA->cesto->cesto);
	temp->idade = EA->cesto->idade;
	temp->prod_size = EA->cesto->list_prod->size;

	//Passagem da informação de todos os produtos da lista de produtos do cesto do elementoTabela, para um array prod_buffer
	if(EA->cesto->list_prod->first->N != NULL)
	{
		delete = EA->cesto->list_prod->first->N->N;
		EA->cesto->list_prod->first = EA->cesto->list_prod->first->N;
		for (int x = 0; x < temp->prod_size; x++)
		{
			temp->produtos[x].quantity = EA->cesto->list_prod->first->quantity;
			temp->produtos[x].code = EA->cesto->list_prod->first->code;
			temp->produtos[x].unit_price = EA->cesto->list_prod->first->unit_price;
			
			if(delete!=NULL)
			{
				EA->cesto->list_prod->first = delete;
				delete = delete->N;
			
			}
		}
	}
	}	
	return temp;
}

/*
Fuction Name: DBtoEA
Description: Função recebe um apontador para uma struct diskbuffer, e devovle um apontador para uma struct elementoTabela,
passando a informação de uma struct para outra.
Arguments: um apontador para struct diskbuffer
return value: um apontador para struct elementoTabela
*/

struct elementoTabela *DBtoEA(struct diskbuffer *DB){
	struct elementoTabela *temp = elementoTabela_new(DB->cesto); //apontador para a struct a ser returnado
	struct prod *add; // apontador usado na passagem de produtos da lista de produtos para um array prod_buffer
	 
	// igualar os valores das duas structs
	temp->deleted = DB->deleted;
	temp->cesto->idade = DB->idade;
	temp->cesto->list_prod->size = DB->prod_size;
	temp->cesto->list_prod->first->N = prod_new();
	add = temp->cesto->list_prod->first->N;

	//Passagem da informação de todos os produtos do array prod_buffer da struct diskbuffer para a lista_produtos do cesto do elementoTabela
	if(DB->prod_size!=0)
	{
		for(int x = 0; x < DB->prod_size ; x++)
		{
		add->quantity = DB->produtos[x].quantity;
		add->code = DB->produtos[x].code;
		add->unit_price = DB->produtos[x].unit_price;
		add->N = prod_new();
		add = add->N;
		}
	}
		
	return temp;
	}
