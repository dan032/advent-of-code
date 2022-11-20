#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>

int calculate_perimeter(int*, int);
int convert_string_to_int(char *);
void *get_sides(char *, int *);
int max(int, int);
int min(int, int);
void problem_1(FILE*);
void problem_2(FILE*);

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

int calculate_perimeter(int* sides, int s_size){
	int sum = 0;
	for(int i = 0; i < s_size; i++){
		
		sum += (2 * sides[i]);
	}
	return sum;
}

int convert_string_to_int(char *str){
	int p = 0;
	int val = 0;

	for(int i = 0; i < strlen(str); i++){
		if (str[i] == 'x') break;
		val *= pow(10, p++); 
		val += str[i] - '0';
	}
	return val;
}

void *get_sides(char *line, int *sides){
	int ch = 'x';
	int l = convert_string_to_int(line);
	char *ptr = strchr(line, ch);
	
	int w = convert_string_to_int(++ptr);
	ptr = strchr(ptr, ch);
	
	int h = convert_string_to_int(++ptr);

	sides[0] = l;
	sides[1] = w;
	sides[2] = h;
}

int max(int a, int b){
	if (a > b) return a;
	return b;
}

int min(int a, int b){
	if (a < b) return a;
	return b;
}

void problem_1(FILE *f){
	ssize_t read;
	size_t len;
	char *line;
	int result = 0;
	int *faces = (int*) malloc(3 * sizeof(int));
	int *sides = (int*) malloc(3 * sizeof(int));

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		get_sides(line, sides);
		
		int f1 = (sides[0] * sides[1]);
		int f2 = (sides[1] * sides[2]);
		int f3 = (sides[2] * sides[0]);
		int min_side = min(f1, min(f2, f3));

		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;

		result +=  calculate_perimeter(faces, 3) + min_side;
	}
	free(faces);
	free(sides);

	printf("%d\n", result);
}

void problem_2(FILE *f){
	ssize_t read;
	size_t len;
	char *line;
	int result = 0;
	int *sides = (int*) malloc(3 * sizeof(int));
	
	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		get_sides(line, sides);
		
		int max_val = max(sides[0], max(sides[1], sides[2]));
		int volume = sides[0] * sides[1] * sides[2];

		if (sides[0] == max_val){
			sides[0] = 0;
		}
		else if (sides[1] == max_val){
			sides[1] = 0;
		}
		else{
			sides[2] = 0;
		}

		result +=  calculate_perimeter(sides, 3) + volume;
	}
	free(sides);

	printf("%d\n", result);
}