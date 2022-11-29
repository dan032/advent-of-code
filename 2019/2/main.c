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
		for(int i = 0; i <= 99; i++){
			for(int j = 0; j <= 99; j++){
				icm__1202_program_alarm(icm, i, j);
				icm__perform(icm);
				if (icm->opcodes[0] == 19690720){
					icm__free(icm);
					printf("%d\n", 100 * i + j);
					fclose(f);
					return 0;
				}
				icm__reset(icm);
			}
		}
		
		icm__free(icm);
		fclose(f);
	}

	return 0;
}

