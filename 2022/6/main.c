#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

void solve(FILE *, int);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));
	sprintf(path, "%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	solve(f, 4);
	rewind(f);
	solve(f, 14);	
	fclose(f);
	free(path);
	return 0;
}

void arr_shift(char *chars, int sz){
	for(int i = 0; i < sz - 1; i++){
		chars[i] = chars[i + 1];
	}
	chars[sz - 1] = '\0';
}

int unique_vals(char *chars, int sz){

	for(int i = 0; i < sz; i++){
		for(int j = i; j < sz; j++){
			if (i == j) continue;
			if (chars[i] == chars[j]) return FALSE;
		}
	}
	return TRUE;
}

void solve(FILE *f, int sz){
	ssize_t read;
	size_t len;
	char *line = NULL;
	char chars[sz];
	int idx = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;

		for(int i = 0; i < strlen(line); i++){
			if (idx < sz){
				chars[idx++] = line[i];
				continue;
			}

			arr_shift(chars, sz);
			chars[sz - 1] = line[i];
			if(unique_vals(chars, sz)){
				printf("%d\n", i + 1);
				return;
			}
		}
	}
}