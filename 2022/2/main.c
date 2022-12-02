#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define WIN 6
#define TIE 3
#define LOSE 0

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

void problem1(FILE *f);
void problem2(FILE *f);

int main(int argc, char *argv[]){
	FILE *f;
	if (argc > 1){
		char *path = (char*) malloc(100 * sizeof(char));
		sprintf(path, "%s", argv[1]);
		printf("%s\n", path);

		f = fopen(path, "r");
		
		if (f == NULL)
		{
			printf("File not found\n");
			return 1;
		}

		problem1(f);
		rewind(f);
		problem2(f);
		
		fclose(f);
	}

	return 0;
}

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		char p1 = line[0];
		char p2 = line[2];

		if (p1 == (p2 - 23)){	// X - A = 23
			result += (TIE + (p2 - 'W'));   // W to convert to 1, 2 or 3
		}
		else if ((p1 == 'A' && p2 == 'Y') || (p1 == 'B' && p2 == 'Z') || (p1 == 'C' && p2 == 'X')){
			result += (WIN + (p2 - 'W'));
		} 
		else{
			result += (LOSE + (p2 - 'W'));
		}
	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	int result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		char p1 = line[0];
		char p2 = line[2];

		if (p2 == 'X'){
			result += LOSE;
			if (p1 == 'A') result += SCISSORS;
			else if (p1 == 'B') result += ROCK;
			else result += PAPER;
		}
		else if (p2 == 'Y'){
			result += TIE;
			if (p1 == 'A') result += ROCK;
			else if (p1 == 'B') result += PAPER;
			else result += SCISSORS;
		}
		else{
			result += WIN;
			if (p1 == 'A') result += PAPER;
			else if (p1 == 'B') result += SCISSORS;
			else result += ROCK;
		}
	}
	printf("%d\n", result);
}