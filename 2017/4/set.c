#include "set.h"


Set_t *set__create(){
    Set_t *set = (Set_t*) calloc(1, sizeof(Set_t));
    set->lists = (Node_t**) calloc(NUM_LISTS, sizeof(Node_t*));
    char *empty = "";
    for(int i = 0; i < NUM_LISTS; i++){
        set->lists[i] = node__create(empty);
    }
    return set;
}

unsigned long str__get_hash(char *word){
    unsigned long hash = 5381;
    int c;

    while (c = *word++){
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int set__get_index(char *word){
    return str__get_hash(word) % NUM_LISTS;
}

Node_t *set__get_head(Set_t *set, char *word){
    return set->lists[set__get_index(word)];
}

int set__insert(Set_t *set, char* word){
    return node__pushback(set__get_head(set, word), word);
}
void set__free(Set_t *set){
    for(int i = 0; i < NUM_LISTS; i++) node__free(set->lists[i]);
    free(set);
}

void set__print_distribution(Set_t *st){
	for(int i = 0; i < NUM_LISTS; i++){
		long amount = st->lists[i]->length;
		if (amount) printf("List %d: %ld\n", i + 1, amount);
	}
}