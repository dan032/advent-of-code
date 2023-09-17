#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

void problem1(FILE *f);
void problem2(char*[], unsigned long[], unsigned long[]);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/12/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    problem1(f);
}

void problem1(FILE *f){
    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    long result = 0, idx = 0, started = FALSE, isNegative = FALSE;

    char* num = (char*) calloc(4, sizeof(char));

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;

        for(int i = 0; i < strlen(line); i++){
            if (line[i] == '-') isNegative = TRUE;
            else if (isdigit(line[i])){
                num[idx++] = line[i];
                started = TRUE;
            }
            else if (started){
                long val = isNegative ? (atoi(num) * -1) : atoi(num);
                result += val;
                free(num);
                num = (char*) calloc(4, sizeof(char));
                idx = 0;
                isNegative = FALSE;
                started = FALSE;
            }
        }
    }
    printf("%ld\n", result);
}