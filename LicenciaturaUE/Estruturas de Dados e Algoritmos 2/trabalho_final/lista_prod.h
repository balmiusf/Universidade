#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// struct contendo a informacao de um produto
struct prod
{
  struct prod *N; // aponta para o proximo produto
  short quantity;
  long long code;
  float unit_price;

};

// struct contendo a informacao de uma lista de produtos

struct list_prod
{
  short size;
  struct prod *first;
};

// funcoes
struct list_prod *list_prods_new();
bool list_prod_empty(struct list_prod *);
struct prod *prod_contains(struct list_prod *, long long c);
void list_prod_remove(struct list_prod *, long long c);
void list_prod_destroy(struct list_prod *);
void list_prod_insert(struct list_prod *, long long c, short q, float price ); 
void list_prod_print(struct list_prod *);
struct prod *list_prod_nth(struct list_prod *, short n);