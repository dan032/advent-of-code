#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
	struct Node *next;
	char *str;
	int start;
	int end;
	long length;
} Node_t;

Node_t *node__create(char*, int, int);
void node__prepend(Node_t**, char*, int, int);
int node__element_overlaps(Node_t*, char*, int);
void node__free(Node_t*);
void node__pushback(Node_t *, char *, int, int);