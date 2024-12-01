#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 56

typedef struct {
    char *name;
    char *neighbor;
    int happiness;
} seat_t;

typedef struct {
    char *name;
    int used;
} person_t;

void problem1(FILE *f);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/13/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    problem1(f);
}

seat_t seat_create(char * line){
    seat_t seat;
    char *token = strtok(line, " ");
    int happiness = 0, lose = 0;

    seat.name = (char*) calloc(strlen(token) + 1, sizeof(char));
    strncpy(seat.name, token, strlen(token));

    strtok(NULL, " ");

    token = strtok(NULL, " ");
    if (strcmp(token, "gain") == 0) lose = FALSE;
    else lose = TRUE;
    token = strtok(NULL, " ");
    seat.happiness = lose ? (-1 * atoi(token)) : atoi(token);

    strtok(NULL, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");

    token = strtok(NULL, ".");
    seat.neighbor = (char*) calloc(strlen(token) + 1, sizeof(char));
    strncpy(seat.neighbor, token, strlen(token));

    return seat;
}

void problem1(FILE *f){
    ssize_t read;
    size_t len;
    char *line = NULL;

    seat_t seat_array[LINE_COUNT];
    int seat_array_idx = 0;

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        seat_array[seat_array_idx++] = seat_create(line);
    }

    for(int i = 0; i < LINE_COUNT; i++) printf("%s -> %s = %d\n", seat_array[i].name, seat_array[i].neighbor, seat_array[i].happiness);

}


// [
// [0, 1, 1, 0, 0, 0, 0, 0] A   2
// [1, 0, 0, 0, 0, 0, 1, 0] B   1
// [1, 0, 0, 0, 0, 0, 0, 1] C   0
// [0, 0, 0, 0, 1, 1, 0, 0] D   2
// [0, 0, 0, 1, 0, 0, 0, 0] E   1
// [0, 0, 0, 1, 0, 0, 0, 0] F   0
// [0, 1, 0, 0, 0, 0, 0, 1] G
// [0, 0, 1, 0, 0, 0, 1, 0] H
// ]

// If two nodes belong to the same component, they cannot be connected