#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

static int count_spaces(const char * str){
	int result = 1;
	char *line = strdup(str);
	char *token = strtok(line, " ");
	while(token = strtok(NULL, " ")){
		result++;
	}
	return result;
}

static int myCompare(const void* a, const void* b){
	const char** a1 = (const char**) a;
	const char** b1 = (const char**) b;
	int a_sz = count_spaces(*a1);
	int b_sz = count_spaces(*b1);

	if (isdigit(*a1[0]) && isdigit(*b1[0])){
		if (a_sz != b_sz) return a_sz > b_sz;
	}
	else if (isdigit(*a1[0])) return -1;
	else if (isdigit(*b1[0])) return 1;
	return strcmp(*a1, *b1);
}

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
	
	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;

	char **lines = (char**) malloc(339 * sizeof(char*));
	int idx = 0;
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		lines[idx++] = strdup(line);
	}

	qsort(lines, 339, sizeof(char*), myCompare);

	for(int i = 0; i < 339; i++){
		printf("%s\n", lines[i]);
	}

	fclose(f);
	return 0;
}

