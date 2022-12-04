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
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		char *p1 = strtok(line, ",");

		int c = atoi(strtok(NULL, "-"));
		int d = atoi(strtok(NULL, ""));

		int a = atoi(strtok(p1, "-"));
		int b = atoi(strtok(NULL, ""));


		if ((a <= c && b >= d) || (c <= a && d >= b)) result += 1;
	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		char *p1 = strtok(line, ",");

		int c = atoi(strtok(NULL, "-"));
		int d = atoi(strtok(NULL, ""));

		int a = atoi(strtok(p1, "-"));
		int b = atoi(strtok(NULL, ""));

		if ((a <= c && b >= c) || (c <= a && d >= a)) result += 1;

	}
	printf("%d\n", result);
}
