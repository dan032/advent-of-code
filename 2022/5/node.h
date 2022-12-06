#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node *next;
    struct Node *prev;
    char value;
} Node_t;

Node_t *node_new(char);
void node_free(Node_t*);
void node_print(Node_t*);

#endif