#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void problem1(FILE *f);
void problem2(FILE *f);
int cmp(const void*, const void*);

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
	int curr = 0, maxVal = 0;

	while((read = getline(&line, &len, f)) != EOF){
		if (strcmp(line, "\n") == 0){
			maxVal = curr > maxVal ? curr : maxVal;
			curr = 0;
		}
		else{
			curr += atoi(line);
		}
	}
	printf("%d\n", maxVal);
}

int cmp(const void *a, const void *b){
	return (*(int*) b - *(int*) a); 
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;
	int curr = 0, idx = 0;
	int arr[2255] = {0};

	while((read = getline(&line, &len, f)) != EOF){
		if (strcmp(line, "\n") == 0){
			arr[idx++] = curr;
			curr = 0;
		}
		else{
			curr += atoi(line);
		}
	}
	arr[idx++] = curr;

	qsort(arr, idx, sizeof(int), cmp);
	printf("%d\n", arr[0] + arr[1] + arr[2]);
}