#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define LINE_LEN 8

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

		int arr[LINE_LEN][26] = {0};

		ssize_t read;
		size_t len;
		char *line = NULL;

		while((read = getline(&line, &len, f)) != EOF){
			line[strcspn(line, "\n")] = 0;
			for(int i = 0; i < LINE_LEN; i++){
				arr[i][line[i] - 'a']++;
			}
		}

		for(int i = 0; i < LINE_LEN; i++){
			int currVal = INT_MAX;
			char currLetter = '\0';
			for(int j = 0; j < 26; j++){
				if (currVal > arr[i][j]){
					currVal = arr[i][j];
					currLetter = j + 'a';
				}
			}
			printf("%c", currLetter);
		}
		
		fclose(f);
	}

	return 0;
}

