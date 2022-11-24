#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1

typedef struct Node {
    struct Node *next;
    char *id;
    long value;
} Node_t;

Node_t *node__create(char*, long);
long node__upsert(Node_t*, char*, long);
void node__free(Node_t*);
long node__get_max_val(Node_t*);
long lmax(long, long);
#endif