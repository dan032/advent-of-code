#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

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

		long result = 0;

		ssize_t read;
		size_t len;
		char *line = NULL;
		int mass = 0;
		int oldMass = 0;
		while((read = getline(&line, &len, f)) != EOF){
			mass = atoi(line);

			while(mass > 0){
				mass = (mass/3) - 2;
				if (mass > 0) 
					result += mass;
			}
		}
		printf("%ld\n", result);
		
		fclose(f);
	}

	return 0;
}

