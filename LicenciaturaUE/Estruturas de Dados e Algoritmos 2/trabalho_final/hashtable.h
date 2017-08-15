//* hashtable interface */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define HASHTABLE_SIZE 200003 // tamanho da hashtable
#define CESTO_NAME_SIZE 10 // tamanho maximo de caracteres que o nome de um cesto pode ter


// struct contendo a informacao de um cesto
struct cesto
{
	char cesto[CESTO_NAME_SIZE+1];
	struct list_prod *list_prod;
	int idade;
};

// struct contend a informacao de um elementoTabela
struct elementoTabela
{
	struct cesto *cesto;
	bool deleted;
};

// struct contendo a informacao de uma hashtable

struct hashtable
{
	struct elementoTabela *tabela[HASHTABLE_SIZE];
	int op;
	int ocupados;
};

// funcoes
struct elementoTabela *elementoTabela_new(char nome[]);
void cesto_destroy(struct cesto *);
void elementoTabela_destroy(struct elementoTabela *);
void destroy_hashtable(struct hashtable *);
struct cesto *cesto_new();
struct hashtable *hashtable_new();
void hashtable_destroy(struct hashtable *);
bool hashtable_empty(struct hashtable *);
void hashtable_remove(struct hashtable *, char nome[]);
bool hashtable_insert(struct hashtable *, char nome[]);
int proPos(struct hashtable *, char[]);
void tornarVazia(struct hashtable *);
bool hashtable_search(struct hashtable *, char nome[]);
int ocupados(struct hashtable *);
struct cesto *hashtable_find(struct hashtable *, char nome[]);


