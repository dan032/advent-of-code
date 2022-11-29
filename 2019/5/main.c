#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "IntCodeMachine.h"

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

		IntCodeMachine_t *icm = icm__load(f);
		icm__perform(icm);
		icm__free(icm);		
		fclose(f);
	}

	return 0;
}

