#include "node.h"

#define TRUE 1
#define FALSE 0

Node_t *node__create(int frequency) {
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    node->next = NULL;
    node->frequency = frequency;
    return node;
}
int node__pushback(Node_t* head, int frequency){
    Node_t *node = node__create(frequency);
    Node_t *prev = NULL;

    while(head){
        // printf("%d ----> %d\n", head->frequency, frequency);
        if (head->frequency == frequency) return FALSE;
        prev = head;
        head = head->next;
    }
    prev->next = node;
    return TRUE;
}
void node__free(Node_t* node){
    free(node);
}
