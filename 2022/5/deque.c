#include "deque.h"

Deque_t *deque_new(){
    Deque_t *dq = (Deque_t*) calloc(1, sizeof(Deque_t));
    dq->front = node_new('\0');
    dq->back = node_new('\0');

    dq->front->next = dq->back;
    dq->back->prev = dq->front;
    return dq;
}

void deque_pushback(Deque_t *dq, char c){
    if (dq->size == 0){
        dq->size++;
        Node_t *node = node_new(c);
        dq->front->next = node;
        dq->back->prev = node;
        return;
    }
    Node_t *tail_prev = dq->back->prev;
    Node_t *node = node_new(c);
    dq->back->prev->next = node;
    node->prev = tail_prev;
    dq->back->prev = node;

    dq->size++;
}

void deque_pushfront(Deque_t *dq, char c){
    if (dq->size == 0){
        dq->size++;
        Node_t *node = node_new(c);
        dq->front->next = node;
        dq->back->prev = node;
        return;
    }

    Node_t *front_next = dq->front->next;
    Node_t *node = node_new(c);
    dq->front->next->prev = node;
    node->next = front_next;
    dq->front->next = node;
    dq->size++;
}
char deque_popfront(Deque_t *dq){
    dq->size--;
    Node_t *temp = dq->front->next;
    char c = temp->value;
    dq->front->next = dq->front->next->next;
    free(temp);
    if (dq->front->next != NULL) dq->front->prev = NULL;
    return c;
}


void deque_free(Deque_t *dq){
    node_free(dq->front);
    free(dq);
}

void deque_print(Deque_t *dq){
    node_print(dq->front->next);
}