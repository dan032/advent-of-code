#include "node.h"
#include <string.h>
#include <stdio.h>


Node_t *node__create(char *str, int s, int e){
	Node_t *node = (Node_t*) malloc(sizeof(Node_t));
	node->str = str;
	node->start = s;
	node->end = e;
	node->next = NULL;
	node->length = 0;

	return node;
}

void node__pushback(Node_t *head, char *str, int s, int e){
	Node_t *node = node__create(str, s, e);
	Node_t *prev = NULL;
	while(head){
		prev = head;
		head = head->next;
	}
	prev->next = node;
}

void node__prepend(Node_t **head, char *str, int s, int e){
	Node_t *node = node__create(str, s, e);
	node->next = *head;
	*head = node;
	(*head)->length = (*head)->next->length + 1;
}

int node__element_overlaps(Node_t *head, char *str, int s){
	while(head){
		if (strcmp(head->str, str) == 0 && head->end != s) return TRUE;
		head = head->next; 
	}
	return FALSE;
}

void node__free(Node_t *node){
	while(node){
		Node_t *tmp = node;
		node = node->next;
		// free(node->str);
		free(tmp);
	}
}