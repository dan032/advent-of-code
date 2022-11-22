#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define LEN 1043

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));

	sprintf(path, "%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}
	
	int *arr = (int*) calloc(LEN, sizeof(int));
	int idx = 0;

	ssize_t read;
	size_t len;
	char *line = NULL, *token = NULL;
	int steps = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		arr[idx++] = atoi(line); 
	}

	idx = 0;
	int curr_step = 0;
	int first_step = 1;
	while (idx >= 0 && idx < LEN){
		curr_step = arr[idx];
		arr[idx] += curr_step >= 3 ? -1 : 1;
		if (first_step){
			curr_step = 1;
			first_step = 0;
		}
		idx += curr_step;
		steps++;
	}
	printf("%d\n", steps + 1);
	free(arr);
	fclose(f);
	return 0;
}

