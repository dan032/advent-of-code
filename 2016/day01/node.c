#include "node.h"

Node_t *node__create(long x, long y){
    Node_t *node = (Node_t*) calloc(1, sizeof(Node_t));
    node->x = x;
    node->y = y;
    return node;
}

int node__pushback(Node_t* head, long x, long y){
    Node_t *prev = NULL;
    while(head){
        if (head->x == x && head->y == y) return FALSE;
        prev = head;
        head = head->next;
    }
    prev->next = node__create(x, y);
    return TRUE;
}

void node__free(Node_t* head){
    while(head){
        Node_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}