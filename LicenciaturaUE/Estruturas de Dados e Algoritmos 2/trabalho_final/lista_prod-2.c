#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lista_prod.h"

/*
Function name: prod_new()
Description: cria um novo produto, aloca espaco e inicializa os seus parametros
Arguments: nenhuns 
return value: apontador do produto
*/

struct prod *prod_new()
{
  struct prod *prod = malloc(sizeof(*prod));
  prod->N = NULL;
  prod->quantity = 0;
  prod->code = 0;
  prod->unit_price = 0.0;
  return prod;
}

/*
Function name: list_prods_new()
Description: cria uma nova lista de produtos
Arguments: nenhuns
return value: apontador da lista de produtos
*/

struct list_prod *list_prods_new()
{
  struct list_prod *list_prod = malloc(sizeof(*list_prod));
  list_prod->size = 0;
  list_prod->first = prod_new();
  return list_prod;
}

/*
Function name: list_prod_new()
Description: cria um novo produto, aloca espaco e inicializa os seus parametros
Arguments: nenhuns
return value: apontador do produto
*/

bool list_prod_empty(struct list_prod* list_prod)
{
  return list_prod->size == 0;
}

/*
Function name: prod_contains()
Description: verifica se o produto existe na lista
Arguments: lista e o codigo do produto
return value: se encontrar retorna o apontador do produto, caso contrario null
*/
struct prod *prod_contains(struct list_prod* list_prod, long long code)
{
  struct prod *temp;
  temp=list_prod->first->N;
  
  while( temp!=NULL )
    {
      if( temp->code == code )
	       return temp;
	
      temp=temp->N;

    }
  return NULL;

}

/*
Function name: list_prod_nth
Description: devolve o apontador do objecto correspondente a posicao n
Arguments: lista e a posicao do produto
return value: se encontrar retorna o apontador do produto, caso contrario null
*/
struct prod *list_prod_nth(struct list_prod* list_prod, short n)
{
  struct prod *node = list_prod->first->N;
  short curr = 0;
  while(curr < n )
  {
      node = node->N;
    curr++;
  }

  return node;
}

/*
Function name: list_prod_insert
Description: insere o produto na posicao a seguir ao header
Arguments: apontador da lista lista e o codigo do produto, quantidade, preco
return value: nada
*/
void list_prod_insert (struct list_prod* list_prod, long long code, short quantity, float price ) 
{
  struct prod *prod = prod_new(); 
  prod->quantity = quantity;
  prod->code = code;
  prod->unit_price = price;

  prod->N = list_prod->first->N;
  list_prod->first->N = prod;

  list_prod->size++;

}

/*
Function name: prod_free()
Description: liberta o espaco alocado pelo produto
Arguments: apontador do produto
return value: nada
*/
void prod_free(struct prod *prod)
{
  free(prod);
}

/*
Function name: prod_destroy()
Description: liberda o espaco recursivamente alocado pelos nos
Arguments: apontador do produto
return value: nada
*/
void prod_destroy(struct prod *prod)
{
  if (prod != NULL)
    prod_destroy(prod->N);

  prod_free(prod);
}


/*
Function name: list_prod_destroy()
Description: liberta o espaco alocado pela lista
Arguments: apontador da llista
return value: nada
*/
void list_prod_destroy(struct list_prod *list_prod)
{
  prod_destroy(list_prod->first);
  free(list_prod);
}


/*
Function name: list_prod_remove()
Description: remove o produto da lista
Arguments: apontador da lista e o codigo do produto
return value: nada
*/

void list_prod_remove(struct list_prod* list_prod, long long c)
{
  struct prod *temp = list_prod->first;
  struct prod *anotherTemp;

  while(temp->N != NULL) // enquanto houver produtos na lista                                                      
  {
    if(temp->N->code == c) // se for igual termina o ciclo
      break;
   
    temp = temp->N; 
  } 

  anotherTemp = temp->N->N; 
  prod_free(temp->N);  
  temp->N = anotherTemp; 

  list_prod->size--;
}

