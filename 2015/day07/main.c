#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 339

typedef struct {
    char *line;
    int complete;
} input_t;

typedef struct {
    char *name;
    unsigned short value;
} wire_t;

void problem_1(int *, char*, int**);
void problem_2(int *, char*, int**);
int is_operator(char*);
int is_signal(char*, unsigned long);
int find_wire_index(wire_t array[], int arr_n, char *name);
void add_to_wire_array(wire_t array[], int *idx, char *name, unsigned short val, int *completed);


char *OPERATIONS[5] = {"AND", "LSHIFT", "NOT", "OR", "RSHIFT"};

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/7/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL, *output_wire = NULL, *input_wire = NULL, *operation = NULL, *operand_wire = NULL;

    input_t *input_array[LINE_COUNT];
    wire_t wire_array[500];
    int completed = 0;
    int i = 0;

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        input_t *ip = (input_t*) calloc(1, sizeof(input_t));
        ip->line = (char*) calloc(len, sizeof(char));
        ip->complete = FALSE;
        strncpy(ip->line, line, len);
        input_array[i++] = ip;
    }

    i = 0;
    int wire_array_idx = 0;
    while(completed < LINE_COUNT){
        int success = FALSE;
        if (input_array[i % LINE_COUNT]->complete) {
            i++;
            continue;
        }
        char *cpy = (char*) calloc(strlen(input_array[i % LINE_COUNT]->line) + 1, sizeof(char));
        strncpy(cpy, input_array[i % LINE_COUNT]->line, strlen(input_array[i % LINE_COUNT]->line));
        token = strtok(cpy, " ");

        if (is_operator(token)){
            output_wire = strtok(NULL, " ");
            strtok(NULL, " ");
            input_wire = strtok(NULL, " ");
            int wire_idx = find_wire_index(wire_array, completed, output_wire);
            if (wire_idx == -1){
                i++;
                continue;
            }
            unsigned short val = ~(wire_array[wire_idx].value);
            add_to_wire_array(wire_array, &wire_array_idx, input_wire, val, &completed);
            success = TRUE;
        }
        else if (is_signal(token, strlen(token))){
            if (strlen(input_array[i % LINE_COUNT]->line) > 11){
                strtok(NULL, " ");
                output_wire = strtok(NULL, " ");
                strtok(NULL, " ");
                input_wire = strtok(NULL, " ");

                int wire_idx = find_wire_index(wire_array, completed, output_wire);
                if (wire_idx == -1){
                    i++;
                    continue;
                }

                unsigned short val = 1 & (wire_array[wire_idx].value);
                add_to_wire_array(wire_array, &wire_array_idx, input_wire, val, &completed);
                success = TRUE;
            }
            else{
                unsigned short val = atoi(token);
                strtok(NULL, " ");
                input_wire = strtok(NULL, " ");
                add_to_wire_array(wire_array, &wire_array_idx, input_wire, val, &completed);
                success = TRUE;

            }
        }
        else{
            if (strlen(input_array[i % LINE_COUNT]->line) < 10){
                output_wire = (char*) calloc(strlen(token) + 1, sizeof(char));
                strncpy(output_wire, token, strlen(token));
                strtok(NULL, " ");
                input_wire = strtok(NULL, " ");

                int wire_idx = find_wire_index(wire_array, completed, output_wire);
                if (wire_idx == -1){
                    i++;
                    continue;
                }

                unsigned short val = wire_array[wire_idx].value;
                add_to_wire_array(wire_array, &wire_array_idx, input_wire, val, &completed);
                free(output_wire);
                success = TRUE;

            }
            else{
                output_wire = (char*) calloc(strlen(token) + 1, sizeof(char));
                strncpy(output_wire, token, strlen(token));
                int wire_idx = find_wire_index(wire_array, completed, output_wire);
                if (wire_idx == -1){
                    free(output_wire);
                    free(cpy);
                    i++;
                    continue;
                }

                operation = strtok(NULL, " ");

                if (strcmp(operation, "LSHIFT") == 0){
                    int val = atoi(strtok(NULL, " "));
                    strtok(NULL, " ");
                    token = strtok(NULL, " ");
                    input_wire = (char*) calloc(strlen(token) + 1, sizeof(char));
                    strncpy(input_wire, token, strlen(token));

                    add_to_wire_array(wire_array, &wire_array_idx, input_wire, wire_array[wire_idx].value << val, &completed);
                    success = TRUE;

                }
                else if (strcmp(operation, "RSHIFT") == 0){
                    int val = atoi(strtok(NULL, " "));
                    strtok(NULL, " ");
                    input_wire = strtok(NULL, " ");
                    add_to_wire_array(wire_array, &wire_array_idx, input_wire, wire_array[wire_idx].value >> val, &completed);
                    success = TRUE;

                }
                else if (strcmp(operation, "AND") == 0) {
                    operand_wire = strtok(NULL, " ");
                    strtok(NULL, " ");
                    input_wire = strtok(NULL, " ");

                    int wire_idx2 = find_wire_index(wire_array, completed, operand_wire);
                    if (wire_idx2 == -1){
                        free(output_wire);
                        free(cpy);
                        i++;
                        continue;
                    }

                    add_to_wire_array(wire_array, &wire_array_idx, input_wire, wire_array[wire_idx].value & wire_array[wire_idx2].value, &completed);
                    success = TRUE;
                }
                else if (strcmp(operation, "OR") == 0) {
                    operand_wire = strtok(NULL, " ");
                    strtok(NULL, " ");
                    input_wire = strtok(NULL, " ");
                    int wire_idx2 = find_wire_index(wire_array, completed, operand_wire);
                    if (wire_idx2 == -1){
                        free(output_wire);
                        free(cpy);
                        i++;
                        continue;
                    }

                    add_to_wire_array(wire_array, &wire_array_idx, input_wire, wire_array[wire_idx].value | wire_array[wire_idx2].value, &completed);
                    success = TRUE;
                }
                free(output_wire);
            }
        }

        if (success){
            input_array[i % LINE_COUNT]->complete = TRUE;
        }
        i++;
        free(cpy);
    }

    for(int i = 0; i < LINE_COUNT; i++){
        printf("%s\n", wire_array[i].name);
        printf("%s ----> %hu\n", wire_array[i].name, wire_array[i].value);
    }
}

void add_to_wire_array(wire_t array[], int *idx, char *name, unsigned short val, int *completed){
    array[*idx].value = val;
    array[*idx].name = (char*) calloc(strlen(name), sizeof(char));
    strncpy(array[(*idx)++].name, name, strlen(name));
    (*completed)++;
}

int is_operator(char* input){
    for(int i = 0; i < 5; i++){
        if (strcmp(OPERATIONS[i], input) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

int is_signal(char* input, unsigned long len){
    for(unsigned long i = 0; i < len; i++){
        if (isdigit(input[i]) == FALSE) return FALSE;
    }
    return TRUE;
}

int find_wire_index(wire_t array[], int arr_n, char *name){
    for(int i = 0; i < arr_n; i++){
        if (strcmp(array[i].name, name) == 0) return i;
    }
    return -1;
}
