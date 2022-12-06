#include "node.h"

Node_t *node_new(char c){
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    node->next = NULL;
    node->prev = NULL;
    node->value = c;
    return node;
}

void node_free(Node_t *head){
    while(head){
        Node_t *node = head;
        head = head->next;
        free(node);
    }
}

void node_print(Node_t *head){
    while(head){
        printf("%c|", head->value);
        head = head->next;
    }
}