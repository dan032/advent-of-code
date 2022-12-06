#include "dequeue.h"

Dequeue_t *dequeue_new(){
    Dequeue_t *dq = (Dequeue_t*) calloc(1, sizeof(Dequeue_t));
    dq->front = node_new('\0');
    dq->back = node_new('\0');

    dq->front->next = dq->back;
    dq->back->prev = dq->front;
    return dq;
}

void dequeue_pushback(Dequeue_t *dq, char c){
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

void dequeue_pushfront(Dequeue_t *dq, char c){
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
char dequeue_popfront(Dequeue_t *dq){
    dq->size--;
    Node_t *temp = dq->front->next;
    char c = temp->value;
    dq->front->next = dq->front->next->next;
    free(temp);
    if (dq->front->next != NULL) dq->front->prev = NULL;
    return c;
}


void dequeue_free(Dequeue_t *dq){
    node_free(dq->front);
    free(dq);
}

void dequeue_print(Dequeue_t *dq){
    node_print(dq->front->next);
}