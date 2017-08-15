#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hashtable.h"
#include "lista_prod.h"
#define CESTO_NAME_SIZE 10 // tamanho maximo de caracteres que o nome de um cesto pode ter
#define PROD_ARRAY_SIZE 10 // tamanho maximo de numero de produtos num array


//Ficheiro .h com a declaração das structs prod_buffer e diskbuffer, que como o nome indica servem como buffers para guardar a informação necessaria,
// de um elemento tabela para escrever num disco. 

//Struct contendo a informação de um produto.
struct prod_buffer{
  int quantity;
  long long code;
  float unit_price;
};


//Struct contendo toda a informação de um elementoTabela
struct diskbuffer{

	short exist;
	short deleted;
	char cesto[CESTO_NAME_SIZE];
	int idade;
	int prod_size;
	struct prod_buffer produtos[PROD_ARRAY_SIZE];

};

//prototipos de funçoes para transferencia da informação.
struct diskbuffer *EAtoDB(struct elementoTabela *);
struct elementoTabela *DBtoEA(struct diskbuffer *);