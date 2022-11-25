#include "set.h"

Set_t *set__create(){
    Set_t *set = (Set_t*) calloc(1, sizeof(Set_t));
    set->nodes = (Node_t**) calloc(NUM_LISTS, sizeof(Node_t*));

    for(int i = 0; i < NUM_LISTS; i++){
        set->nodes[i] = node__create(LONG_MAX, LONG_MAX);
    }
    return set;
}

long get_index(long x, long y){
    return abs((x ^ y) % NUM_LISTS);
}

Node_t *get_node(Set_t* set, long x, long y){
    return set->nodes[get_index(x, y)];
}

int set__insert(Set_t* set,long x, long y){
    return node__pushback(get_node(set, x, y), x, y);
}
void set__free(Set_t* set){
    for(int i = 0; i < NUM_LISTS; i++){
        node__free(set->nodes[i]);
    }
    free(set->nodes);
    free(set);
}