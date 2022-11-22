#include "node.h"

#define TRUE 1
#define FALSE 0

Node_t *node__create(char* word){
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    char *word_mem = (char*) calloc(strlen(word) + 1, sizeof(char));
    strcpy(word_mem, word);
    node->next = NULL;
    node->word = word_mem;
    return node;
}

int node__pushback(Node_t* head, char* word){
    Node_t *node = node__create(word);
    Node_t *prev = NULL;

    while(head){
        if (strcmp(head->word, word) == 0) return FALSE;
        prev = head;
        head = head->next;
    }
    prev->next = node;
    return TRUE;
}
void node__free(Node_t *node){
    free(node->word);
    free(node);
}