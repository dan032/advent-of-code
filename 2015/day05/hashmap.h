#include <stdlib.h>
#include <string.h>
#include "node.h"

#define CAPACITY 1000

typedef struct {
	Node_t **nodes;
	int unique_elements;
} Hashmap_t;

Hashmap_t *hashmap__create();
int hashmap__add(Hashmap_t *, char*, int, int);
void hashmap__free(Hashmap_t *);
void hashmap__print_distribution(Hashmap_t*);