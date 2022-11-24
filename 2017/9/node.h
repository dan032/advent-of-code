#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    char value;
} Node_t;

Node_t *node__create(char);
void node__push_front(Node_t**, char);
char node__head_val(Node_t*);
void node__pop_front(Node_t**);
void node__free(Node_t*);

#endif