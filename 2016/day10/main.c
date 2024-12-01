#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define C1 61
#define C2 17

typedef enum {
    BOT, OUTPUT
} destination_type;

typedef struct {
    int bot;
    int value;
} input_ins_t;

typedef struct {
    int bot_src;
    int low_id;
    int high_id;
    destination_type low_type;
    destination_type high_type;
} bot_ins_t;


int main(){
    char *path = "/Users/dan2/advent-of-code/2016/day10/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("File not found\n");
        return 1;
    }

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;


    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';

    }
}