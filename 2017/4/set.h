#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

#define NUM_LISTS 1000

typedef struct {
    Node_t **lists;
} Set_t;

Set_t *set__create();
int set__insert(Set_t*, char*);
void set__free(Set_t*);
void set__print_distribution(Set_t *st);
#endif