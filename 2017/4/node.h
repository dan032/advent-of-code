#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *next;
    char *word;
} Node_t;

Node_t *node__create(char*);
int node__pushback(Node_t*, char*);
void node__free(Node_t*);

#endif