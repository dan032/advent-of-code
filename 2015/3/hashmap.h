#include <stdlib.h>
#include "node.h"

#define CAPACITY 10000

typedef struct {
	Node_t **nodes;
	int mod;
	int unique_elements;
} Hashmap_t;

Hashmap_t *hashmap__create(int mod);
void hashmap__add(Hashmap_t *hm, int x, int y);
void hashmap__free(Hashmap_t *hm);