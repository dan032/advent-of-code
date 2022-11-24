#include "hashmap.h"

Hashmap_t *hashmap__create(){
    Hashmap_t *hashmap = (Hashmap_t*) calloc(1, sizeof(Hashmap_t));
    hashmap->nodes = (Node_t**) calloc(NUM_LISTS, sizeof(Node_t*));

    for(int i = 0; i < NUM_LISTS; i++){
        hashmap->nodes[i] = node__create("\0", 0);
    }
    return hashmap;
}

unsigned long generate_hash(char *id){
    unsigned long hash = 5381;
    int c;

    while(c = *id++){
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

int get_index(char *id){
    return abs(generate_hash(id)) % NUM_LISTS;
}

Node_t *hashmap__get_node(Hashmap_t *hm, char *id){
    return hm->nodes[get_index(id)];
}

long hashmap__upsert(Hashmap_t *hm, char *id, long value){
    return node__upsert(hashmap__get_node(hm, id), id, value);
}

void hashmap__free(Hashmap_t *hm){
    for(int i = 0; i < NUM_LISTS; i++){
        node__free(hm->nodes[i]);
    }
    free(hm->nodes);
    free(hm);
}

long hashmap__get_max_val(Hashmap_t *hm){
    long result = LONG_MIN;
    for(int i = 0; i < NUM_LISTS; i++){
        result = lmax(result, node__get_max_val(hm->nodes[i]));
    }
    return result;
}