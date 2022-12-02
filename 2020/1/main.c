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

		int arr[200] = {0};
		ssize_t read;
		size_t len;
		char *line = NULL;
		int idx = 0;
		while((read = getline(&line, &len, f)) != EOF){
			arr[idx++] = atoi(line);
		}

		for(int i = 0; i < 200; i++){
			for(int j = i; j < 200; j++){
				for(int k = j; k < 200; k++){
					if ((arr[i] + arr[j] + arr[k]) == 2020){
						printf("%d\n", arr[i] * arr[j] * arr[k]);
		
					}
				}
			}
		}

		
		fclose(f);
	}

	return 0;
}

