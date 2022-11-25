#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "set.h"


int move(Set_t *set, char *token, long *x, long *y, int *angle);
int insert_trace(Set_t *set, long oldX, long *x, long oldY, long *y);
int main(int argc, char *argv[]){
	char *path = (char*) malloc(50 * sizeof(char));

	sprintf(path, "%s", argv[1]);

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

	Set_t *set = set__create();

	read = getline(&line, &len, f);
	token = strtok(line, ", ");

	char dir = token[0];
	int distance = token[1] - '0';

	move(set, token, &x, &y, &angle);

	while(token = strtok(NULL, ", ")){
		if (move(set, token, &x, &y, &angle)) break;
	}
	
	printf("\n%ld\n", labs(x) + labs(y));
	set__free(set);
	fclose(f);
	return 0;
}

long lmin(long a, long b){
	return a < b ? a : b;
}

long lmax(long a, long b){
	return a > b ? a : b;
}

int move(Set_t *set, char *token, long *x, long *y, int *angle){
	char dir = token[0];
	int distance = atoi(++token);

	long oldX = *x;
	long oldY = *y;

	if (dir == 'L')      *angle -= 90;
	else if (dir == 'R') *angle += 90;

	if (*angle < 0)        *angle += 360;
	else if (*angle > 270) *angle -= 360;

	if (*angle == 0)        *y += distance;
	else if (*angle == 180) *y -= distance;
	else if (*angle == 90)  *x += distance;
	else if (*angle == 270) *x -= distance;

	return insert_trace(set, oldX, x, oldY, y);
}

int insert_trace(Set_t *set, long oldX, long *x, long oldY, long *y){
	if (oldX < *x){
		for(long i = oldX + 1; i <= *x; i++){
			if (set__insert(set, i, *y) == 0){
				*x = i;
				return TRUE;
			}
		}
	}
	else{
		for(long i = oldX - 1; i >= *x; i--){
			if (set__insert(set, i, *y) == 0){
				*x = i;
				return TRUE;
			}
		}
	}

	if (oldY < *y){
		for(long i = oldY + 1; i <= *y; i++){
			if (set__insert(set, *x, i) == 0){
				*y = i;
				return TRUE;
			}
		}
	}
	else{
		for(long i = oldY - 1; i >= *y; i--){
			if (set__insert(set, *x, i) == 0){
				*y = i;
				return TRUE;
			}
		}
	}
	return FALSE;
}