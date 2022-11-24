#include "node.h"

Node_t *node__create(char* tid, long value){
    Node_t* node = (Node_t*) calloc(1, sizeof(Node_t));
    char *id = (char*) calloc(strlen(tid)+1, sizeof(char));
    strcpy(id, tid);
    node->next = NULL;
    node->id = id;
    node->value = value;

    return node;
}

long node__upsert(Node_t* head, char* id, long value){
    Node_t *prev = NULL;
    while(head){
        if (strcmp(head->id, id) == 0){
            head->value += value;
            return head->value;
        }
        prev = head;
        head = head->next;
    }
    prev->next = node__create(id, value);
    return 0;
}

void node__free(Node_t* head){
    while(head){
        Node_t *tmp = head;
        head = head->next;
        free(tmp->id);
        free(tmp);
    }
}

long lmax(long a, long b){
    return a > b ? a : b;
}

long node__get_max_val(Node_t *head){
    long res = LONG_MIN;

    while(head){
        res = lmax(res, head->value);
        head = head->next;
    }
    return res;
}