#include <stdlib.h>
#include "node.h"

#define CAPACITY 10000

typedef struct {
	Node_t **nodes;
	int unique_elements;
} Hashmap_t;

Hashmap_t *hashmap__create();
void hashmap__add(Hashmap_t *, int, int);
void hashmap__free(Hashmap_t *);
void hashmap__print_distribution(Hashmap_t*);