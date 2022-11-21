#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

int move(char *token, long *x, long *y, int *angle);

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
	long x = 0;
	long y = 0;
	int angle = 0; // 0 N, 90 E, 180 S, 270 W

	read = getline(&line, &len, f);
	token = strtok(line, ", ");

	char dir = token[0];
	int distance = token[1] - '0';

	move(token, &x, &y, &angle);

	while(token = strtok(NULL, ", ")){
		move(token, &x, &y, &angle);
	}
	
	printf("\n%ld\n", labs(x + y));
	fclose(f);
	return 0;
}

int move(char *token, long *x, long *y, int *angle){
	char dir = token[0];
	int distance = atoi(++token);

	if (dir == 'L')      *angle -= 90;
	else if (dir == 'R') *angle += 90;

	if (*angle < 0)        *angle += 360;
	else if (*angle > 270) *angle -= 360;

	if (*angle == 0)        *y += distance;
	else if (*angle == 180) *y -= distance;
	else if (*angle == 90)  *x += distance;
	else if (*angle == 270) *x -= distance;
}
