#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

#define TRUE 1
#define FALSE 0

typedef struct {
    Node_t *head;
    long size;
} Stack_t;

Stack_t *stack__create();
void stack__push(Stack_t*, char);
char stack__top(Stack_t*);
int void stack__pop(Stack_t*);
void stack__free(Stack_t*);
int stack__empty(Stack_t*);


#endif