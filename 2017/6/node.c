#include "node.h"

#define TRUE 1
#define FALSE 0

Node_t *node__create(char* word, int idx){
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    char *word_mem = (char*) calloc(strlen(word) + 1, sizeof(char));
    strcpy(word_mem, word);
    node->next = NULL;
    node->word = word_mem;
    node->length = 0;
    node->idx = idx;

    return node;
}

int node__pushback(Node_t* head, char* word, int idx){
    Node_t *node = node__create(word, idx);
    Node_t *prev = NULL;
    head->length++;
    
    while(head){
        if (strcmp(head->word, word) == 0){
            // printf("%s | %s\n", head->word, word);
            return abs(idx - head->idx);
        }
        prev = head;
        head = head->next;
    }
    prev->next = node;
    return 0;
}
void node__free(Node_t *node){
    free(node->word);
    free(node);
}