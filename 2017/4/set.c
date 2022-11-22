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

int str__get_sum(char *word){
    int total = 0;
    for(int i = 0; i < strlen(word); i++) total += word[i] - '0';
    return total;
}

int set__get_index(char *word){
    return (str__get_sum(word) ^ NUM_LISTS) % NUM_LISTS;
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