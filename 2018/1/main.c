#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "set.h"

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

		ssize_t read;
		size_t len;
		char *line = NULL;

		int result = 0;
		int freq = 0;

		int *arr = (int*) malloc(1028 * sizeof(int));
		int idx = 0;
		Set_t *set = set__create();
		while((read = getline(&line, &len, f)) != EOF){
			int c = atoi(line);
			arr[idx++] = c;
		}

		idx = 0;
		while(1){
			freq += arr[idx++ % 1028];
			if (set__add(set, freq) == 0){
				printf("%d\n", freq);
				break;
			}
		}

		set__free(set);
		fclose(f);
	}

	return 0;
}

