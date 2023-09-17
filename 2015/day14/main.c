#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 9

typedef struct {
    char *name;
    int speed;
    int moving_time;
    int rest_time;
    int distance_moved;
    int current_moving_time;
    int current_rest_time;
    int points;
} reindeer_t;

void problem1(FILE *f);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/14/input.txt";
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
    reindeer_t reindeer_array[LINE_COUNT];
    int reindeer_array_idx = 0;

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';

        reindeer_t reindeer;
        token = strtok(line, " ");
        reindeer.name = (char*) calloc(strlen(token) + 1, sizeof(char));
        strncpy(reindeer.name, token, strlen(token));

        strtok(NULL, " ");
        strtok(NULL, " ");

        token = strtok(NULL, " ");
        reindeer.speed = atoi(token);

        strtok(NULL, " ");
        strtok(NULL, " ");

        token = strtok(NULL, " ");
        reindeer.moving_time = atoi(token);

        strtok(NULL, " ");
        strtok(NULL, " ");
        strtok(NULL, " ");
        strtok(NULL, " ");
        strtok(NULL, " ");
        strtok(NULL, " ");

        token = strtok(NULL, " ");
        reindeer.rest_time = atoi(token);
        reindeer.current_moving_time = 0;
        reindeer.current_rest_time = 0;
        reindeer.distance_moved = 0;
        reindeer.points = 0;
        reindeer_array[reindeer_array_idx++] = reindeer;
    }

    int second = 0;

    while(second != 2503){
        for(int i = 0; i < LINE_COUNT; i++){
            if (reindeer_array[i].current_moving_time < reindeer_array[i].moving_time){
                reindeer_array[i].distance_moved += reindeer_array[i].speed;
                reindeer_array[i].current_moving_time++;
            }
            else if (reindeer_array[i].current_rest_time < reindeer_array[i].rest_time){
                reindeer_array[i].current_rest_time++;
                if (reindeer_array[i].current_rest_time == reindeer_array[i].rest_time){
                    reindeer_array[i].current_rest_time = 0;
                    reindeer_array[i].current_moving_time = 0;
                }
            }
        }
        int max_distance = 0;
        for(int i = 0; i < LINE_COUNT; i++) max_distance = reindeer_array[i].distance_moved > max_distance ? reindeer_array[i].distance_moved : max_distance;
        for(int i = 0; i < LINE_COUNT; i++) if (reindeer_array[i].distance_moved == max_distance) reindeer_array[i].points++;
        second++;
    }

    for(int i = 0; i < LINE_COUNT; i++) printf("%d\n", reindeer_array[i].points);

}