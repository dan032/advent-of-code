#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

typedef struct{
    Node_t *front;
    Node_t *back;
    int size;
} Deque_t;

Deque_t *deque_new();
void deque_pushback(Deque_t*, char);
char deque_popfront(Deque_t*);
void deque_free(Deque_t*);
void deque_print(Deque_t*);
void deque_pushfront(Deque_t *dq, char c);
#endif