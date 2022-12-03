#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

void problem1(FILE *f);
void problem2(FILE *f);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));
	sprintf(path, "%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	problem1(f);
	rewind(f);
	problem2(f);	
	fclose(f);
	

	return 0;
}

void problem1(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	long result = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		int r_min = 0, r_max = 127;
		int c_min = 0, c_max = 7;
		int c = INT_MIN, r = INT_MIN;
		char last_c, last_r;
		
		for(int i = 0; i < strlen(line); i++){
			if(line[i] == 'F'){
				r_max -= ((r_max - r_min + 1) / 2);
				last_r = line[i];
			}
			else if (line[i] == 'B'){
				r_min += ((r_max - r_min + 1) / 2);
				last_r = line[i];
			}
			else if (line[i] == 'L'){
				c_max -= ((c_max - c_min + 1) / 2);
				last_c = line[i];
			}
			else{
				c_min += ((c_max - c_min + 1) / 2);
				last_c = line[i];
			}
		}
		
		c = last_c == 'R' ? c_max : c_min;
		r = last_r == 'B' ? r_max : r_min;
		result = result > (c + r * 8) ? result : (c + r * 8);
	}
	printf("%ld\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int arr[1023] = {0};

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		int r_min = 0, r_max = 127;
		int c_min = 0, c_max = 7;
		int c = INT_MIN, r = INT_MIN;
		int id;
		char last_c, last_r;
		
		for(int i = 0; i < strlen(line); i++){
			if(line[i] == 'F'){
				r_max -= ((r_max - r_min + 1) / 2);
				last_r = line[i];
			}
			else if (line[i] == 'B'){
				r_min += ((r_max - r_min + 1) / 2);
				last_r = line[i];
			}
			else if (line[i] == 'L'){
				c_max -= ((c_max - c_min + 1) / 2);
				last_c = line[i];
			}
			else{
				c_min += ((c_max - c_min + 1) / 2);
				last_c = line[i];
			}
		}
		
		c = last_c == 'R' ? c_max : c_min;
		r = last_r == 'B' ? r_max : r_min;
		id = (c + r * 8);
		arr[id] = 1;
	}

	for(int i = 1; i < 1022; i++){
		if (arr[i - 1] == 1 && arr[i + 1] == 1 && arr[i] == 0){
			printf("%d\n", i);
			break;
		}
	}
}
