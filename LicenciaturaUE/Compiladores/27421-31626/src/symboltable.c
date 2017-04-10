#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "apt.h"

typedef struct vars *vars;
typedef struct funcs *funcs;

typedef struct hashTable *hashTable;
typedef struct ht_node *ht_node;


struct vars{
//	char *nome;
	enum type_kind kind;
};


struct funcs{

//	char *nome;
	vars *args[20];

	enum type_kind kind;
};

 struct hashTable{
	int size;
	hashTable *old;		// points to old hashtable
	hashTable *next;	// points to new hashtable
	ht_node table[3007];
};


 struct ht_node{
	int ocupado;
	char *id;
	union{
		vars vars;
		funcs func;
	}node;
};

int hash(char word[], int size)
{
  int h = 0;
  int i = 0;

  while (word[i] != '\0')
    {
      h += word[i];
      i++;
    }
  int c;

  if(size ==0)
  	c = 0;
  else
  	c = h % size;

  return h % size;
}


struct ht_node *ht_node_new(char *id, vars var, funcs fun)
{
	ht_node node = (ht_node) malloc(sizeof(*node));

	if(var == NULL)
		node->node.vars = var;
	else
		node->node.func =fun;

	node->ocupado = 1;

	return node;
}	

struct hashTable *hashtable_new()
{
	hashTable tabela = (hashTable) malloc(sizeof(*tabela));

	int i;
	for(i = 0; i < 3007; i++)
		tabela->table[i] = NULL;

	tabela->size = 0;

	return tabela;
}


struct vars *ht_node_new_var(type type)
{
	vars var = (vars) malloc(sizeof(*var));

	var->kind = type->kind;

	return var;
}

struct funcs *ht_node_new_func(hashTable ht, type type, ht_nodes args[10])
{
	funcs func = (funcs) malloc(sizeof(*func));
	func->kind = type->kind;

	new_scope(args);

	return func;
}

// gera uma nova hashtable dentro de uma hashtable
void new_scope(hashTable ht, vars args[n])
{
	hashTable ht2 = hashtable_new();
	int i;
	ht2->next = NULL;	//apontador para a frente
	ht2->old = ht;	// apontador para tras
	ht->next = ht2;	// apontador para a frente
	for(i = 0; i < n ; i++)
		hashTable_insert_var(ht2,args[i]);	// args vao para a tabela

}



void hashtable_free(hashTable hashTable)
{
	int i;
	for(i = 0; i < 3007; i++)
		if(hashTable->table[i] != NULL)
			free(hashTable->table[i]);

	free(hashTable);
}

void hashTable_insert_var(hashTable ht, char *id,type type)
{
	int hsh= hash(id,ht->size);

	while(true)
	{
		if(ht->table[hsh]->ocupado == 0){
			
			vars var = ht_node_new_var(type);
			ht->table[hsh]->ocupado = 1;
			ht->table[hsh] = ht_node_new(id,var,NULL);
			
			break;
		}
		else
		{
			int i = 0;
			while(ht->table[hsh]->ocupado != 1)
			{
				i++;
				i %= 3007;
			}
		}
	}

	ht->size++;

}

void hashTable_insert_var_2(hashTable ht, belos_ids ids,type type)
{
	belos_ids root = ids;

	while(root != NULL)
	{
		hashTable_insert_var(ht,root->u.many_ids.id,type->kind);
		root = root->u.many_ids.more_ids;
	}
}

ht_node hashtable_look(hashTable ht, char *id, type type)
{
		int hsh = hash(id,ht->size);
		while(true)
		{
			if(ht->table[hsh]->ocupado == 1)
				return	ht->table[hsh];			
			else
			{
				int i = 0;
				while(ht->table[hsh]->ocupado != 0)
				{
					i++;
					i %= 3007;
				}
			}
		}

		return NULL;
}


bool hashtable_check_all(hashTable ht, char *id, type type)
{
	ht_node *node;
	while(ht->next != NULL)
	{
		node = hashtable_look(ht,id,type);
		if (node == NULL)
			ht = ht->next;
		else
			return true;
	}
	return false;
}

void hashTable_insert_func(hashTable ht, char *id, type type, vars args[])
{
	int hsh = hash(id,ht->size);
	
	while(true)
	{
		if(ht->table[hsh]->ocupado == 0)
		{
			funcs fun = ht_node_new_func(ht,type->kind,args);
			ht->table[hsh]->ocupado = 1;
			ht->table[hsh] = ht_node_new(id,NULL,fun);
			break;
		}
		else
		{
			hsh = 0;
			while(ht->table[hsh]->ocupado != 1)
			{
				hsh++;
				hsh %= 3007;
			}
		}
	}
	ht->size++;
}