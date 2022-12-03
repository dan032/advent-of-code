#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

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

void arr_reset(int *arr){
	for(int i = 0; i < 26; i++) arr[i] = 0;
}

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int arr[26] = {0};
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		if (line[0] == '\n'){
			for(int i = 0; i < 26; i++){
				if (arr[i] > 0) result++;
			}
			arr_reset(arr);
			continue;
		}
		line[strcspn(line, "\n")] = 0;

		for(int i = 0; i < strlen(line); i++){
			arr[line[i] - 'a']++;
		}
	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int arr[26] = {0};
	int result = 0, idx = 0;
	while((read = getline(&line, &len, f)) != EOF){
		if (line[0] == '\n'){
			for(int i = 0; i < 26; i++){
				if (arr[i] == idx) result++;
			}
			arr_reset(arr);
			idx = 0;
			continue;
		}
		line[strcspn(line, "\n")] = 0;

		for(int i = 0; i < strlen(line); i++){
			if (arr[line[i] - 'a'] == idx)
				arr[line[i] - 'a'] = idx + 1;
		}
		idx++;
	}
	printf("%d\n", result);
}
