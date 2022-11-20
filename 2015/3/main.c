#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>

#define CAPACITY 10000
#define TRUE 1
#define FALSE 0

void problem_1(FILE *f);
void problem_2(FILE *f);
void increment_coordinates(int *, int *, char);

typedef struct Node {
	struct Node *next;
	int x;
	int y;
	int head;
} Node_t;

typedef struct {
	Node_t **nodes;
	int mod;
	int unique_elements;
} Hashmap_t;

Node_t *node__create(int x, int y, int is_head){
	Node_t *node = (Node_t*) malloc(sizeof(Node_t));
	node->x = x;
	node->y = y;
	node->head = is_head;
	node->next = NULL;

	return node;
}

void node__pushback(Node_t *head, int x, int y){
	Node_t *prev = NULL;
	Node_t *node = node__create(x, y, FALSE);
	
	while(head){
		prev = head;
		head = head->next;
	}
	prev->next = node;
}

int node__key_exists(Node_t *head, int x, int y){
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

Hashmap_t *hashmap__create(int mod){
	Hashmap_t *hm = (Hashmap_t*) malloc(sizeof(Hashmap_t));
	hm->mod = mod;
	hm->nodes = (Node_t**) malloc(CAPACITY * sizeof(Node_t*));
	hm->unique_elements = 1;

	for(int i = 0; i < CAPACITY; i++){
		hm->nodes[i] = node__create(0, 0, TRUE);
	}
	return hm;
}

int hashmap__get_index(Hashmap_t *hm, int x, int y){
	return abs((x + y) % hm->mod);
}

Node_t *hashmap__get_node(Hashmap_t *hm, int x, int y){
	return hm->nodes[hashmap__get_index(hm, x, y)];
}

int hashmap__key_exists(Hashmap_t *hm, int x, int y){
	return node__key_exists(hashmap__get_node(hm, x, y), x, y);
}

void hashmap__add(Hashmap_t *hm, int x, int y){
	int exists = hashmap__key_exists(hm, x, y);
	if (exists) return;

	node__pushback(hashmap__get_node(hm, x, y), x, y);
	hm->unique_elements++;
}

void hashmap__free(Hashmap_t *hm){
	for(int i = 0; i < CAPACITY; i++){
		node__free(hm->nodes[i]);
	}
	free(hm);
}

int main(int argc, char *argv[]){
	char *path = (char*) malloc(50 * sizeof(char));
	sprintf(path, "/home/dan/Desktop/advent-of-code/%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}
	
	problem_1(f);
	rewind(f);
	problem_2(f);
	fclose(f);
	free(path);
	return 0;
}

void problem_1(FILE *f){
	char c;
	int x = 0;
	int y = 0;

	Hashmap_t *hm = hashmap__create(2371);

	while((c = fgetc(f)) != EOF){
		increment_coordinates(&x, &y, c);
		hashmap__add(hm, x, y);
	}

	printf("%d\n", hm->unique_elements);
	hashmap__free(hm);
}

void problem_2(FILE *f){
	char c;
	int santa_x = 0;
	int santa_y = 0;

	int robot_x = 0;
	int robot_y = 0;

	int turn = 0;
	Hashmap_t *hm = hashmap__create(2371);

	while((c = fgetc(f)) != EOF){
		if (turn % 2 == 0){
			increment_coordinates(&santa_x, &santa_y, c);
			hashmap__add(hm, santa_x, santa_y);
		}
		else{
			increment_coordinates(&robot_x, &robot_y, c);
			hashmap__add(hm, robot_x, robot_y);
		}
		turn++;
	}

	printf("%d\n", hm->unique_elements);
	hashmap__free(hm);
}

void increment_coordinates(int *x, int *y, char c){
	if (c == '>') (*x)++;
	if (c == '<') (*x)--;
	if (c == '^') (*y)++;
	if (c == 'v') (*y)--;
}