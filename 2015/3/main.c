#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>

#include "hashmap.h"

void problem_1(FILE *f);
void problem_2(FILE *f);
void increment_coordinates(int *, int *, char);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(50 * sizeof(char));
	sprintf(path, "/home/dan/Desktop/advent-of-code/%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}
	
	problem_1(f);
	rewind(f);
	problem_2(f);
	fclose(f);
	free(path);
	return 0;
}

void problem_1(FILE *f){
	char c;
	int x = 0, y = 0;

	Hashmap_t *hm = hashmap__create();

	while((c = fgetc(f)) != EOF){
		increment_coordinates(&x, &y, c);
		hashmap__add(hm, x, y);
	}

	printf("%d\n", hm->unique_elements);
	hashmap__free(hm);
}

void problem_2(FILE *f){
	char c;
	int santa_x = 0, santa_y = 0;
	int robot_x = 0, robot_y = 0;
	int turn = 0;
	Hashmap_t *hm = hashmap__create();

	while((c = fgetc(f)) != EOF){
		if (turn % 2 == 0){
			increment_coordinates(&santa_x, &santa_y, c);
			hashmap__add(hm, santa_x, santa_y);
		}
		else{
			increment_coordinates(&robot_x, &robot_y, c);
			hashmap__add(hm, robot_x, robot_y);
		}
		turn++;
	}

	printf("%d\n", hm->unique_elements);
	hashmap__free(hm);
}

void increment_coordinates(int *x, int *y, char c){
	if (c == '>') (*x)++;
	if (c == '<') (*x)--;
	if (c == '^') (*y)++;
	if (c == 'v') (*y)--;
}