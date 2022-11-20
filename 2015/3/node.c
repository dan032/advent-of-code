#include "node.h"

Node_t *node__create(int x, int y){
	Node_t *node = (Node_t*) malloc(sizeof(Node_t));
	node->x = x;
	node->y = y;
	node->next = NULL;
	node->length = 0;

	return node;
}

void node__prepend(Node_t **head, int x, int y){
	Node_t *node = node__create(x, y);
	node->next = *head;
	*head = node;
	(*head)->length = (*head)->next->length + 1;
}

int node__location_exists(Node_t *head, int x, int y){
	while(head){
		if (head->x == x && head->y == y) return TRUE;
		head = head->next;
	}
	return FALSE;
}

void node__free(Node_t *node){
	while(node){
		Node_t *tmp = node;
		node = node->next;
		free(tmp);
	}
}