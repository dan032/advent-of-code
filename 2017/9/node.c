#include "node.h"

Node_t *node__create(char c){
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    node->value = c;
    return node;
}

void node__push_front(Node_t **head, char c){
    Node_t *node = node__create(c);
    node->next = *head;
    *head = node;
}

char node__head_val(Node_t *head){
    return head->next->value;
}

void node__pop_front(Node_t **head){
    Node_t* tmp = (*head)->next;
    (*head)->next = (*head)->next->next;
    free(tmp);
}
void node__free(Node_t* head){
    while(head){
        Node_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}