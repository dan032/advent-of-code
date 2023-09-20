#include <limits.h>
#include "set.h"

#define LIST_CAPACITY 1000

Set_t *set__create(){
    Set_t* set = (Set_t*) malloc(sizeof(Set_t));
    set->nodes = (Node_t**) malloc(LIST_CAPACITY * sizeof(Node_t*));

    for(int i = 0; i < LIST_CAPACITY; i++){
        set->nodes[i] = node__create(INT_MAX);
    }
    return set;
}

int set__get_index(int val){
    return abs(val % LIST_CAPACITY);
}

Node_t *set__get_node(Set_t* set, int val){
    int idx = set__get_index(val);
    // printf("%d", idx);
    return set->nodes[idx];
}

int set__add(Set_t *set, int val){
    return node__pushback(set__get_node(set, val), val);
}
void set__free(Set_t *set){
    for(int i = 0; i < LIST_CAPACITY; i++){
        node__free(set->nodes[i]);
    }
    free(set->nodes);
    free(set);
}