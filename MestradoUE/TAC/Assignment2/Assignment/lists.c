#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

static SingleNode node_new(frame n)
{
	SingleNode node = (SingleNode) malloc(sizeof(*node));

	node->next = NULL;
	node->v = n;

	return node;
}

list list_new()
{
	list l = (list) malloc(sizeof(*l));

	l->header = (SingleNode) node_new(NULL);
	l->size = 0;

	return l;
}

void list_insert( list list, frame k)
{
	SingleNode newNode = node_new(k);

	newNode->next = list->header->next;
	list->header->next = newNode;

	list->size++;
}

// returns the frame given index and removes it from list since no longer needed
frame getFrame(list list, int i)
{
	SingleNode node = list->header->next;
	int j = 0;
	while(j < i){
		node = node->next;
		j++;
	}
	frame fr = node->v;
	free(node);	// free it (no longer needed after using it)
	return fr;
}
