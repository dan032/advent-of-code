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
	char *line = NULL;

	int x = 0, result = 0, first = TRUE;
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		if (first){
			first = FALSE;
			x += 3;
			continue;
		}

		if (line[x % strlen(line)] == '#') result++;
		x += 3;
	}

	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	int increments[5][2] = {
		{1, 1},
		{3, 1},
		{5, 1},
		{7, 1},
		{1, 2}
	};
	long results[5] = {0};
	int idx = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		for(int i = 0; i < 5; i++){
			if ((idx) % increments[i][1] != 0) continue;
			if (line[(increments[i][0] * idx)% strlen(line)] == '#') results[i]++;
		}
		idx++;
	}
	if (line[(increments[4][0] * (idx - 1))% strlen(line)] == '#') results[4]++;
	printf("%ld\n", results[0] * results[1] * results[2] * results[3] * results[4]);
}
