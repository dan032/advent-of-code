#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "stack.h"

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
		long result = 0;


		
		fclose(f);
	}

	return 0;
}

