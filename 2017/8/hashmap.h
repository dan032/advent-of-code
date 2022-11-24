#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "node.h"

#define NUM_LISTS 1000

typedef struct {
    Node_t **nodes;
} Hashmap_t;

Hashmap_t *hashmap__create();
long hashmap__upsert(Hashmap_t*, char*, long);
void hashmap__free(Hashmap_t*);
long hashmap__get_max_val(Hashmap_t*);
#endif