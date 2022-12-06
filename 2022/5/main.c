#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>

#include "deque.h"

#define TRUE 1
#define FALSE 0
#define NUM_STACKS 9

void problem1(FILE *f);
void problem2(FILE *f);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));
	sprintf(path, "%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	problem1(f);
	rewind(f);
	problem2(f);	
	fclose(f);
	

	return 0;
}

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	Deque_t **stacks = (Deque_t**) calloc(NUM_STACKS, sizeof(Deque_t*));
	for(int i = 0; i < NUM_STACKS; i++){
		stacks[i] = deque_new();
	}

	int count = 0;
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		count += 1;
		int idx = 0;

		if (count < NUM_STACKS){
			for(int i = 0; i < strlen(line); i++){
				if (line[i] != ' ' && idx % 2 == 1){
					if (isalpha(line[i])){
						deque_pushback(stacks[idx/4], line[i]);
					}
				}
				idx += 1;
			}
		}
		else if (count == 9) continue;
		else{
			char *token = strtok(line, " ");
			int amount = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			int src = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			int dest = atoi(strtok(NULL, " "));

			for(int i = 0; i < amount; i++){
				char el = deque_popfront(stacks[src - 1]);
				deque_pushfront(stacks[dest-1], el);	
			}
		}
	}
	for(int i = 0; i < NUM_STACKS; i++){
		deque_print(stacks[i]);
		deque_free(stacks[i]);
		printf("\n");
	}
	free(stacks);
	printf("\n\n\n");
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	Deque_t **stacks = (Deque_t**) calloc(NUM_STACKS, sizeof(Deque_t*));
	for(int i = 0; i < NUM_STACKS; i++){
		stacks[i] = deque_new();
	}

	int count = 0;
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		count += 1;
		int idx = 0;

		if (count < NUM_STACKS){
			for(int i = 0; i < strlen(line); i++){
				if (line[i] != ' ' && idx % 2 == 1){
					if (isalpha(line[i])){
						deque_pushback(stacks[idx/4], line[i]);
					}
				}
				idx += 1;
			}
		}
		else if (count == 9) continue;
		else{
			char *token = strtok(line, " ");
			int amount = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			int src = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			int dest = atoi(strtok(NULL, " "));
			Deque_t *tmp = (Deque_t*) deque_new();

			for(int i = 0; i < amount; i++){
				char el = deque_popfront(stacks[src - 1]);
				deque_pushfront(tmp, el);	
			}

			for(int i = 0; i < amount; i++){
				char el = deque_popfront(tmp);
				deque_pushfront(stacks[dest - 1], el);	
			}
			deque_free(tmp);
		}
	}
	for(int i = 0; i < NUM_STACKS; i++){
		deque_print(stacks[i]);
		deque_free(stacks[i]);
		printf("\n");
	}
	free(stacks);

}
