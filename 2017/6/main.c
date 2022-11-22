#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#include "set.h"

#define LEN 16

int find_largest(int *arr, size_t arr_len);
char *generate_string(int *arr, size_t arr_len);
void redistribute(int * arr, int max_idx, size_t arr_len);

int main(int argc, char *argv[]){
	FILE *f;
	if (argc > 1){
		char *path = (char*) malloc(100 * sizeof(char));
		sprintf(path, "%s", argv[1]);

		f = fopen(path, "r");
		
		if (f == NULL)
		{
			printf("File not found\n");
			return 1;
		}

		ssize_t read;
		size_t len;
		char *line = NULL, *token = NULL;
		int *arr = (int*) calloc(LEN, sizeof(int));
		int idx = 0;
		read = getline(&line, &len, f);
		line[strcspn(line, "\n")] = 0;

		token = strtok(line, " ");
		arr[idx++] = atoi(token);

		while(token != NULL){
			token = strtok(NULL, " ");
			if(token == NULL) break;
			arr[idx++] = atoi(token);
		}

		Set_t *set = set__create();

		int result = 0;
		idx = 0;
		while(1){
			redistribute(arr, find_largest(arr, LEN), LEN);
			char *a = generate_string(arr, LEN);
			if (result = set__insert(set, a, idx++)) break;
		}
		printf("%d --- %d\n", result, idx);
		set__free(set);
		fclose(f);
	}

	return 0;
}

int find_largest(int *arr, size_t arr_len){
	int val = INT_MIN;
	int idx = -1;

	for(int i = 0; i < arr_len; i++){
		if (arr[i] > val){
			val = arr[i];
			idx = i;
		}
	}
	return idx;
}

char *generate_string(int *arr, size_t arr_len){
	char * res = (char*) calloc(65, sizeof(char));
	int idx = 0;
	for(int i = 0; i < arr_len; i++){
		char d[3];
		sprintf(d, "%d", arr[i]);
		for(int j = 0; j < strlen(d); j++){
			res[idx++] = d[j];
		}
		res[idx++] = '-';
	}
	res[idx] = '\0';
	return res;
}

void redistribute(int * arr, int max_idx, size_t arr_len){
	int amount = arr[max_idx];
	arr[max_idx] = 0;
	int idx = ++max_idx;

	while(amount > 0){
		arr[idx++ % arr_len]++;
		amount--;
	}
}