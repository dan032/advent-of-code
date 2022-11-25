#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct Node {
    struct Node *next;
    long x;
    long y;
} Node_t;

Node_t *node__create(long, long);
int node__pushback(Node_t*, long, long);
void node__free(Node_t*);

#endif