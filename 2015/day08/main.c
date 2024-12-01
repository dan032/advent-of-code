#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 300

void problem1(char*[], unsigned long[], unsigned long[]);
void problem2(char*[], unsigned long[], unsigned long[]);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/8/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    char *input_array[LINE_COUNT];
    unsigned long literal_size_array[LINE_COUNT];
    unsigned long memory_size_array[LINE_COUNT];

    int input_array_idx = 0;

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        input_array[input_array_idx] = (char*) calloc(strlen(line) + 1, sizeof(char));
        strncpy(input_array[input_array_idx++], line, strlen(line));
    }

    for(int i = 0; i < LINE_COUNT; i++){
        literal_size_array[i] = strlen(input_array[i]);
    }

    problem1(input_array, literal_size_array, memory_size_array);
    problem2(input_array, literal_size_array, memory_size_array);
}

void problem1(char *input_array[], unsigned long literal_size_array[], unsigned long memory_size_array[]){
    for(int i = 0; i < LINE_COUNT; i++){
        unsigned long len = 0;
        int isEscaped = FALSE;
        int isHex = FALSE;
        int hexCharNum = 0;

        for(int j = 0; j < strlen(input_array[i]); j++){
            if (input_array[i][j] == '\\'){
                if (isEscaped){
                    len++;
                    isEscaped = FALSE;
                }
                else{
                    isEscaped = TRUE;
                }
            }
            else{
                // Single Quote
                if (isEscaped && input_array[i][j] == '\"'){
                    len++;
                    isEscaped = FALSE;
                }

                // Hex Pre
                else if (isEscaped && input_array[i][j] == 'x'){
                    isHex = TRUE;
                }

                // Hex Post
                else if (isEscaped && isHex){
                    if (hexCharNum == 0) hexCharNum++;
                    else{
                        len++;
                        isEscaped =  FALSE;
                        isHex = FALSE;
                        hexCharNum = 0;
                    }
                }
                else{
                    len++;
                }
            }
        }

        len -= 2;
        memory_size_array[i] = len;
    }

    long result = 0;
    for(int i = 0; i < LINE_COUNT; i++) result += (literal_size_array[i] - memory_size_array[i]);
    printf("%ld\n", result);
}

void problem2(char *input_array[], unsigned long literal_size_array[], unsigned long encoded_size_array[]){
    for(int i = 0; i < LINE_COUNT; i++){
        unsigned long len = 0;

        for(int j = 0; j < strlen(input_array[i]); j++){
            if (input_array[i][j] == '\\') len += 2;
            else if (input_array[i][j] == '\"'){
                if (j == 0 || j == strlen(input_array[i]) - 1) len += 3;
                else len += 2;
            }
            else len++;
        }
        encoded_size_array[i] = len;
    }

    long result = 0;
    for(int i = 0; i < LINE_COUNT; i++) result += (encoded_size_array[i] - literal_size_array[i]);
    printf("%ld\n", result);
}