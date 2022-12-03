#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>

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

	int result = 0, found = FALSE;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		for(int i = 0; i < strlen(line) / 2; i++){
			if (found) break;
			for(int j = strlen(line) / 2; j < strlen(line); j++){
				if (line[i] == line[j]){
					if (isupper(line[i])){
						result += line[i] - 38;
					}
					else{
						result += line[i] - 96;
					}
					found = TRUE;
					break;
				}
			}
		}
	}
	printf("%d\n", result);
}

void problem2(FILE *f){
	ssize_t read;
	size_t len;
	char *line = NULL;

	int idx = 0, result = 0;
	int arr[52] = {0};

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		for(int i = 0; i < strlen(line); i++){
			if (islower(line[i]) && (arr[line[i] - 'a'] == idx)){
				arr[line[i] - 'a'] = idx + 1;
			}
			else if (arr[line[i] - 'A' + 26] == idx){
				arr[line[i] - 'A' + 26] = idx + 1;
			}
		}

		if (idx == 2){
			for(int i = 0; i < 52; i++){
				if (arr[i] == 3){
					result += (i + 1);
				}
			}	
			idx = 0;
			for(int i = 0; i < 52; i++) arr[i] = 0;
			continue;
		}

		idx++;
	}
	
	printf("%d\n", result);
}
