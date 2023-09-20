#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *next;
    int frequency;
} Node_t;

Node_t *node__create(int);
int node__pushback(Node_t*, int);
void node__free(Node_t*);

#endif