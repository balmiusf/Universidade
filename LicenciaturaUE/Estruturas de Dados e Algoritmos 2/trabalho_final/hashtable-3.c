#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "lista_prod.h"
#define HASHTABLE_SIZE 200003 // tamanho da hashtable
#define CESTO_NAME_SIZE 10    // tamanho maximo de caracteres que o nome de um cesto pode ter

/*
Function name: cesto_destroy
Description: liberta o espaco ocupado pelo cesto
Arguments: apontador do cesto
return value: nada
*/
void cesto_destroy(struct cesto *cesto)
{
	list_prod_destroy(cesto->list_prod);
	free(cesto);
}

/*
Function name: elementoTabela_destroy
Description: liberta o espaco ocupado pelo elementoTabela
Arguments: apontador do elementoTabela
return value: nada
*/
void elementoTabela_destroy(struct elementoTabela *elementoTabela)
{
	cesto_destroy(elementoTabela->cesto); 
	free(elementoTabela);
}

/*
Function name: destroy_hashtable
Description: liberta o espaco ocupado pela hashtable
Arguments: apontador da hashtable
return value: nada
*/
void destroy_hashtable(struct hashtable *hashtable)
{
	for(int i = 0; i < HASHTABLE_SIZE; i++)
	{
		if(hashtable->tabela[i] != NULL)
			elementoTabela_destroy(hashtable->tabela[i]);
	}

	free(hashtable);
}

/*
Function name: cesto_new
Description: cria um novo cesto
Arguments: nome do cesto
return value: apontador do cesto
*/
struct cesto *cesto_new(char id[])
{
	struct cesto *cesto = malloc(sizeof(struct cesto));
	cesto->list_prod = list_prods_new();
	strcpy(cesto->cesto,id);
	cesto->idade = 0;

	return cesto;
}

/*
Function name: elementoTabela_new
Description: aloca espaco para um novo elementoTabela e inicializa os campos
Arguments: nome do cesto
return value: apontador do elementoTabela
*/
struct elementoTabela *elementoTabela_new(char id[])
{
	struct elementoTabela *elementoTabela = malloc(sizeof(struct elementoTabela));
	elementoTabela->cesto = cesto_new(id);
	elementoTabela->deleted = false;
	return elementoTabela;
}

/*
Function name: hashtable_new
Description: aloca espaco para uma nova hashtable e inicializa os campos
Arguments: nome do cesto
return value: apontador do cesto
*/
struct hashtable *hashtable_new()
{
	struct hashtable *hashtable = malloc(sizeof(struct hashtable));
	hashtable->ocupados = 0;
	hashtable->op = 0;

	for(int i = 0; i < HASHTABLE_SIZE;i++)
		hashtable->tabela[i] = NULL;

	return hashtable;
}

/* funcao de hash
 djb2 -> hashcode de Dan Bernstein
 (nao da nossa autoria) */
int myhash(char str[])
{
    unsigned long long hash = 5381;
   	int c = 0;

    while ((c = *str++))
   	    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

// segunda funcao de hash
int myhash2(char cesto[])
{
	return 13-(myhash(cesto) % 13);	
}

// duplo hashing
int procPos(struct hashtable *hashtable, char id[])
{
	int hash = myhash(id); // primeiro hash
	int hash2 = myhash2(id); // segundo hash
	int hash_final = 0;
	int x = 0;
	
	//verifica se a posicao e diferente de null
	while(hashtable->tabela[hash_final] != NULL) 
	{
		// verifica se o nome do cesto e diferente
		if(strcmp(hashtable->tabela[hash_final]->cesto->cesto,id) != 0) 
		{
			// se for aplica duplo hashing
			hash_final = (hash + x*hash2) % HASHTABLE_SIZE;
			x++;
			if(hash_final < 0)
				hash_final *= (-1);

		}else
			break;
	}
	return hash_final;
}

/*
Function name: ocupados
Description: numero de posicoes ocupadas na hashtable
Arguments: nome do cesto
return value: apontador do cesto
*/
int ocupados(struct hashtable *hashtable)
{
	return hashtable->ocupados;
}

/*
Function name: hashtable_search
Description: procura o cesto na hashtable
Arguments: apontador da hashtable, nome do cesto
return value: booleano
*/
bool hashtable_search(struct hashtable *hashtable, char cesto[])
{
	int pos = procPos(hashtable,cesto);
	
	return (hashtable->tabela[pos] != NULL && !hashtable->tabela[pos]->deleted);
}

/*
Function name: hashtable_insert
Description: insere o cesto na hashtable. Ha duas formas de inserir: 
	- insere num espaco vazio na hashtable
	- encontra um espaco nao vazia mas tem a flag deleted a true, neste caso liberta o espaco alocado e cria um novo elementoTabela
Arguments: apontador da hashtable, nome do cesots
return value: booleano
*/
bool hashtable_insert(struct hashtable *hashtable, char cesto[])
{
	int pos = procPos(hashtable,cesto);
	if (hashtable->tabela[pos] == NULL) // se ainda nao existir
	{
		hashtable->tabela[pos] = elementoTabela_new(cesto); // cria um novo elementoTabela
		// altera a idade para o numero de operacoes
		hashtable->tabela[pos]->cesto->idade=hashtable->op; 
		hashtable->ocupados++; // incrementa ocupados

		return true;
	}

// se a posicao na tabela estiver ocupada mas a flag sinalizar que esta "apagado"
	else if (hashtable->tabela[pos]->deleted) 
	{
		// liberta o espaco
		elementoTabela_destroy(hashtable->tabela[pos]);
		// cria um novo elementoTabela
		hashtable->tabela[pos] = elementoTabela_new(cesto);
		// altera a idade para o numero de operacoes
		hashtable->tabela[pos]->cesto->idade=hashtable->op;
		hashtable->ocupados++; 

		return true;
	}

	return false; //caso ja exista na tabela
}

/*
Function name: hashtable_remove
Description: altera a flag
Arguments: apontador da hashtable, nome do cesto
return value: nada
*/
void hashtable_remove(struct hashtable *hashtable, char cesto[])
{
	int pos = procPos(hashtable,cesto);
	if(hashtable->tabela[pos] != NULL)
	{
		hashtable->tabela[pos]->deleted = true; // altera a flag
		hashtable->ocupados--;
	}
}


/*
Function name: hashtable_find
Description: devolve o apontador referente ao nome do cesto
Arguments: apontador da hashtable, nome do cesto
return value: apontador do cesto, ou null se nao encontrar
*/
struct cesto *hashtable_find(struct hashtable *hashtable, char cesto[])
{
	if(!hashtable_search(hashtable,cesto))
		return NULL;
	
	return hashtable->tabela[procPos(hashtable,cesto)]->cesto;  
}

