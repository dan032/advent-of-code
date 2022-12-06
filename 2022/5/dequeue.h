#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

typedef struct{
    Node_t *front;
    Node_t *back;
    int size;
} Dequeue_t;

Dequeue_t *dequeue_new();
void dequeue_pushback(Dequeue_t*, char);
char dequeue_popfront(Dequeue_t*);
void dequeue_free(Dequeue_t*);
void dequeue_print(Dequeue_t*);
void dequeue_pushfront(Dequeue_t *dq, char c);
#endif