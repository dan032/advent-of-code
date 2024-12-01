#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 28

typedef struct {
    char *start;
    char *end;
    int distance;
    int visited;
} node_t;

void problem1(char*[], unsigned long[], unsigned long[]);
void problem2(char*[], unsigned long[], unsigned long[]);

void dfs(node_t nodes[], int visited_count, int distance, int locations);
int count_unique_locations(node_t nodes[]);

int result = INT_MAX;

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/9/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL, *start, *end;
    int distance;

    int node_array_idx = 0;
    node_t nodes[LINE_COUNT * 2];

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, " ");
        start = (char*) calloc(strlen(token) + 1, sizeof(char));
        strncpy(start, token, strlen(token));

        strtok(NULL, " ");

        token = strtok(NULL, " ");
        end = (char*) calloc(strlen(token) + 1, sizeof(char));
        strncpy(end, token, strlen(token));

        strtok(NULL, " ");

        token = strtok(NULL, " ");
        distance = atoi(token);

        nodes[node_array_idx].start = start;
        nodes[node_array_idx].end = end;
        nodes[node_array_idx].distance = distance;
        nodes[node_array_idx++].visited = FALSE;

        nodes[node_array_idx].start = end;
        nodes[node_array_idx].end = start;
        nodes[node_array_idx].distance = distance;
        nodes[node_array_idx++].visited = FALSE;
    }
    int unique_locations = count_unique_locations(nodes);
}

void dfs(node_t nodes[], int currIdx, int visited_count, int distance, int locations){
    if (visited_count == locations){
        result = min(result, distance);
        return;
    }


}


int location_in_array(char *nodes[], char *loc, int len){
    for(int i = 0; i < len; i++){
        if ((strcmp(nodes[i], loc) == 0)) return TRUE;
    }
    return FALSE;
}

int count_unique_locations(node_t nodes[]){
    char *unique_nodes[LINE_COUNT * 2];
    int currIdx = 0;

    for(int i = 0; i < LINE_COUNT * 2; i++){
        if (location_in_array(unique_nodes, nodes[i].start, currIdx)) continue;
        unique_nodes[currIdx++] = nodes[i].start;
        if (location_in_array(unique_nodes, nodes[i].end, currIdx)) continue;
        unique_nodes[currIdx++] = nodes[i].end;
    }
    return currIdx;
}