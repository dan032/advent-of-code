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

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		
		int count = 0;
		int min = atoi(strtok(line, "-"));
		int max = atoi(strtok(NULL, " "));
		char c = strtok(NULL, ":")[0];
		char *password = strtok(NULL, "");

		for(int i = 0; i < strlen(password); i++){
			if (password[i] == c){
				count++;
			}
		}
		if (count >= min && count <= max) result++;

	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	
	int result = 0;
	while((read = getline(&line, &len, f)) != EOF){

		line[strcspn(line, "\n")] = 0;

		int idx1 = atoi(strtok(line, "-"));
		int idx2 = atoi(strtok(NULL, " "));
		char c = strtok(NULL, ":")[0];
		char *password = strtok(NULL, "");

		if (password[idx1] == c && password[idx2] == c) continue;
		if (password[idx1] == c || password[idx2] == c){
			result++;
		}
	}
	printf("%d\n", result);
}
