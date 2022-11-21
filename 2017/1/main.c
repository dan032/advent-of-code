#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define LINE_LEN 2120

void problem_1(FILE*);
void problem_2(FILE*);

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
	char c;
	int first = 0, idx = 0, num = 0, last = 0, result = 0;

	while((c = fgetc(f)) != EOF){
		if (c == '\n') break;
		num = c - '0';

		if (idx++ == 0) first = num;
		if (num == last) result += num;
		last = num;
	}
	printf("%d\n", result + (first == last ? first : 0));
}

void problem_2(FILE *f){
	int *arr = (int*) malloc(LINE_LEN * sizeof(int));
	char c;
	int idx = 0;
	int result = 0;

	while((c = fgetc(f)) != EOF){
		if (c == '\n') break;

		arr[idx++] = c - '0';
	}	

	int step = LINE_LEN / 2;
	idx = 0;

	while (idx < (LINE_LEN - step)){
		if (arr[idx] == arr[idx + step]) result += (2 * arr[idx]);
		idx++;
	}
	printf("%d\n", result);
	free(arr);
}