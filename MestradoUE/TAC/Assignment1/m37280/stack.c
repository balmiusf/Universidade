#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define SIZE 30

int stack[SIZE];
int top = -1;

void pop2()
{
   	if(top != -1)
        top--;
   	else
        printf("Error\n");
}

int pop()
{
    int v;
    
    if(top != -1)
    {
        v = stack[top];
        top--;
        return v;
    }
    else
        printf("Stack Error\n");
    
    return 0;
}

void push(int v)
{
    if(top != SIZE)
    {
        top++;
        stack[top] = v;
    }
    else
        printf("Stack Error.\n");
}
