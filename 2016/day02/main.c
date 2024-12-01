#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

int within_edge(int x, int y){
	if (x < 0 || x > 4 || y < 0 || y > 4) return FALSE;
	if (y == 2 || x == 2) return TRUE;
	
	int diff = y % 2;
	if (x >= (2 - diff) && x <= (2 + diff)) return TRUE;
	return FALSE;
}

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

		char keypad2[5][5] = {{' ', ' ', '1', ' ', ' '},
							 {' ', '2', '3', '4', ' '},
							 {'5', '6', '7', '8', '9'},
							 {' ', 'A', 'B', 'C', ' '},
							 {' ', ' ', 'D', ' ', ' '}
							 };

		char keypad1[3][3] = {{'1', '2', '3'},
							 {'4', '5', '6'},
							 {'7', '8', '9',}};

		ssize_t read;
		size_t len;
		char *line = NULL;

		int x = 0;
		int y = 2;

		while((read = getline(&line, &len, f)) != EOF){
			line[strcspn(line, "\n")] = 0;

			for(int i = 0; i < strlen(line); i++){
				int oldX = x;
				int oldY = y;
				if (line[i] == 'U') y--;
				if (line[i] == 'D') y++;
				if (line[i] == 'L') x--;
				if (line[i] == 'R') x++;

				if (within_edge(x, y) == FALSE){
					x = oldX;
					y = oldY;
				}
			}
			printf("%c\n", keypad2[y][x]);
		}
		
		fclose(f);
	}

	return 0;
}



