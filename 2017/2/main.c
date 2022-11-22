#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define LINE_LEN 16

void problem_1(FILE*);
void problem_2(FILE*);

int min(int a, int b);
int max(int a, int b);

static int cmp(const void *a, const void *b);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(50 * sizeof(char));

	sprintf(path, "/home/dan/Desktop/advent-of-code/%s", argv[1]);
	printf("%s\n", path);

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
	return 0;
}

void problem_1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	char *token = NULL;
	int total = 0;

	while((read = getline(&line, &len, f)) != EOF){
		token = strtok(line, " ");
		int curr = atoi(token);
		int minVal = curr;
		int maxVal = curr;

		while(token != NULL){
			token = strtok(NULL, " ");
			if (token == NULL) break;
			curr = atoi(token);
			minVal = min(minVal, curr);
			maxVal = max(maxVal, curr);
		}

		total += (maxVal - minVal);
	}
	printf("%d\n", total);
}

void problem_2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	int total = 0, idx = 0, result = 0;;

	int *arr = (int*) calloc(LINE_LEN, sizeof(int));

	while((read = getline(&line, &len, f)) != EOF){
		token = strtok(line, " ");
		arr[idx++] = atoi(token);

		while(token != NULL){
			token = strtok(NULL, " ");
			if (token == NULL) break;
			arr[idx++] = atoi(token);
		}

		for(int i = 0; i < LINE_LEN; i++){
			for(int j = i + 1; j < LINE_LEN; j++){
				if (arr[i] == 0 || arr[j] == 0) continue;
				if (arr[i] % arr[j] == 0){
					result += (arr[i] / arr[j]);
				}
				else if (arr[j] % arr[i] == 0){
					result += (arr[j] / arr[i]);
				}
			}
		}
		memset(arr, 0, LINE_LEN);
		idx = 0;
	}
	printf("%d\n", result);
}

int min(int a, int b){
	return a < b ? a : b;
}

int max(int a, int b){
	return a > b ? a : b;
}

static int cmp(const void *a, const void *b){
	return (*(const int*) a - *(const int*)b);
}