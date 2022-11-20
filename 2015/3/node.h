#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
	struct Node *next;
	int x;
	int y;
} Node_t;

Node_t *node__create(int, int);
void node__prepend(Node_t**, int, int);
int node__location_exists(Node_t*, int, int);
void node__free(Node_t*);