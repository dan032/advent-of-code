#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define GRID_DIM 100

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/day18/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    problem1(f);
}

// x will mean coming on, y will mean coming off.

void problem1(FILE *f){
    ssize_t read;
    size_t len;

    char *line = NULL, *token = NULL;
    char grid[GRID_DIM][GRID_DIM];

    int i = 0, j = 0;
    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';

        for(int x = 0; x < strlen(line); x++){
            grid[i][j++] = line[x];
        }
        j = 0;
        i++;
    }


    int step = 0;
    while(step++ < 100){
        for(i = 0; i < GRID_DIM; i++){
            for(j = 0; j < GRID_DIM; j++){
                int count = 0;
                if ((i == 0 && j == 0) || (i == 0 && j == (GRID_DIM - 1) || (i == (GRID_DIM - 1) && j == 0) || (i == (GRID_DIM - 1) && j == (GRID_DIM - 1)))) continue;

                for(int r = (i - 1); r <= (i + 1); r++){
                    for(int c = (j - 1); c <= (j + 1); c++){
                        if (r < 0 || r >= GRID_DIM || c < 0 || c >= GRID_DIM || (r == i && c == j)) continue;
                        if ((grid[r][c] == '#' ) || (grid[r][c] == 'y')) count++;
                    }
                }

                if (grid[i][j] == '#' && (count != 2 && count != 3)) grid[i][j] = 'y';
                else if (grid[i][j] == '.' && (count == 3)) grid[i][j] = 'x';
            }
        }

        for(i = 0; i < GRID_DIM; i++){
            for(j = 0; j < GRID_DIM; j++){
                if (grid[i][j] == 'y') grid[i][j] = '.';
                if (grid[i][j] == 'x') grid[i][j] = '#';
            }
        }
    }

    int result = 0;
    for(int i = 0; i < GRID_DIM; i++){
        for(int j = 0; j < GRID_DIM; j++){
            if (grid[i][j] == '#') result++;
        }
    }
    printf("%d\n", result);
}