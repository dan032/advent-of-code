#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "set.h"

#define TRUE 1
#define FALSE 0

static int cmp(const void *a, const void *b){
	return (*(const char*) a - *(const char*)b);
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

	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		Set_t *set = set__create();

		token = strtok(line, " ");
		qsort(token, strlen(token), sizeof(char), cmp);
		set__insert(set, token);

		int valid = TRUE;
		while(token != NULL){
			token = strtok(NULL, " ");
			if (token == NULL) break;
			token[strcspn(token, "\n")] = 0;
			qsort(token, strlen(token), sizeof(char), cmp);
			if (set__insert(set, token) == 0){
				valid = FALSE;
				break;
			}
		}

		if(valid) result++;
		set__free(set);
	}

	printf("%d\n", result);
	fclose(f);
	return 0;
}

