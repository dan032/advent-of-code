#include "hashmap.h"

Hashmap_t *hashmap__create(int mod){
	Hashmap_t *hm = (Hashmap_t*) malloc(sizeof(Hashmap_t));
	hm->mod = mod;
	hm->nodes = (Node_t**) malloc(CAPACITY * sizeof(Node_t*));
	hm->unique_elements = 1;

	for(int i = 0; i < CAPACITY; i++){
		hm->nodes[i] = node__create(0, 0);
	}
	return hm;
}

int hashmap__get_index(Hashmap_t *hm, int x, int y){
	return abs((x + y) % hm->mod);
}

Node_t **hashmap__get_node(Hashmap_t *hm, int x, int y){
	return &hm->nodes[hashmap__get_index(hm, x, y)];
}

int hashmap__location_exists(Hashmap_t *hm, int x, int y){
	return node__location_exists(*hashmap__get_node(hm, x, y), x, y);
}

void hashmap__add(Hashmap_t *hm, int x, int y){
	int exists = hashmap__location_exists(hm, x, y);
	if (exists) return;

	node__prepend(hashmap__get_node(hm, x, y), x, y);
	hm->unique_elements++;
}

void hashmap__free(Hashmap_t *hm){
	for(int i = 0; i < CAPACITY; i++){
		node__free(hm->nodes[i]);
	}
	free(hm);
}
