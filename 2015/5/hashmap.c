#include "hashmap.h"
#include <stdio.h>

Hashmap_t *hashmap__create(){
	Hashmap_t *hm = (Hashmap_t*) malloc(sizeof(Hashmap_t));
	hm->nodes = (Node_t**) malloc(CAPACITY * sizeof(Node_t*));

	for(int i = 0; i < CAPACITY; i++){
		char *s = "";
		hm->nodes[i] = node__create(s, -1, -1);
	}
	return hm;
}

int hashmap__get_str_sum(char *str){
	int sum = 0;
	for(int i = 0; i < strlen(str); i++) sum += str[i] - 'a';
	return sum;
}

int hashmap__get_index(char* str){
	return abs(hashmap__get_str_sum(str) % CAPACITY);
}

Node_t **hashmap__get_node(Hashmap_t *hm, char *str){
	return &hm->nodes[hashmap__get_index(str)];
}

int hashmap__add(Hashmap_t *hm, char *str, int s, int e){
	Node_t* n = *hashmap__get_node(hm, str);
	int overlaps = node__element_overlaps(n, str, s);
	if (overlaps) return FALSE;

	node__prepend(hashmap__get_node(hm, str), str, s, e);
	return TRUE;
}

void hashmap__free(Hashmap_t *hm){
	for(int i = 0; i < CAPACITY; i++){
		node__free(hm->nodes[i]);
	}
	free(hm);
}

void hashmap__print_distribution(Hashmap_t *hm){
	for(int i = 0; i < CAPACITY; i++){
		long amount = hm->nodes[i]->length;
		if (amount) printf("List %d: %ld\n", i + 1, amount);
	}
}
