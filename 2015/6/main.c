#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define DIMENSION 1000

void problem_1(int *, char*, int**);
void problem_2(int *, char*, int**);

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

	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	int coords[4] = { 0 };

	long result1 = 0, result2 = 0;

	char *command = (char*) malloc(6 * sizeof(char));
	int **grid1 = (int**) malloc(DIMENSION * sizeof(int*));
	int **grid2 = (int**) malloc(DIMENSION * sizeof(int*));

	for(int i = 0; i < DIMENSION; i++){
		grid1[i] = (int*) malloc(DIMENSION * sizeof(int));
		grid2[i] = (int*) malloc(DIMENSION * sizeof(int));
	}
	
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		token = strtok(line, " ");
		
		if (strcmp(token, "turn") == 0){
			token = strtok(NULL, " ");
		}

		command = token;

		coords[0] = atoi(strtok(NULL, ","));
		coords[1] = atoi(strtok(NULL, " "));
		strtok(NULL, " ");
		coords[2] = atoi(strtok(NULL, ","));
		coords[3] = atoi(strtok(NULL, ""));
	
		problem_1(coords, command, grid1);
		problem_2(coords, command, grid2);
	}

	for(int i = 0; i < DIMENSION; i++){
		for(int j = 0; j < DIMENSION; j++){
			if (grid1[i][j] == 1) result1++;
			result2 += grid2[i][j];
		}
	}
	printf("%ld\n", result1);
	printf("%ld\n", result2);

	fclose(f);
	return 0;
}

void problem_1(int *coords, char *command, int** grid){
	for(int i = coords[0]; i <= coords[2]; i++){
		for(int j = coords[1]; j <= coords[3]; j++){
			if (strcmp(command, "toggle") == 0){
				grid[i][j] = !grid[i][j];
			}
			else if(strcmp(command, "on") == 0){
				grid[i][j] = 1;
			}
			else if(strcmp(command, "off") == 0){
				grid[i][j] = 0;
			}
		}
	}
}

void problem_2(int *coords, char *command, int** grid){
	for(int i = coords[0]; i <= coords[2]; i++){
		for(int j = coords[1]; j <= coords[3]; j++){
			if (strcmp(command, "toggle") == 0){
				grid[i][j] += 2;
			}
			else if(strcmp(command, "on") == 0){
				grid[i][j]++;
			}
			else if(strcmp(command, "off") == 0){
				if (grid[i][j] == 0) continue;
				grid[i][j]--;
			}
		}
	}
}