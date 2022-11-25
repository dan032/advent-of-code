#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "node.h"

#define NUM_LISTS 1000

typedef struct {
    Node_t **nodes;
} Set_t;

Set_t *set__create();
int set__insert(Set_t*,long, long);
void set__free(Set_t*);

#endif