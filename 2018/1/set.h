#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <string.h>
#include "node.h"

#define CAPACITY 1000

typedef struct {
	Node_t** nodes;
} Set_t;

Set_t *set__create();
int set__add(Set_t *, int);
void set__free(Set_t *);

#endif