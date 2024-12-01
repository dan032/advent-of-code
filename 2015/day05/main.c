#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>

#include "hashmap.h"

int p1_is_nice_string(char *);
int p2_is_nice_string(char *);
int has_forbidden_string(char *);
int is_vowel(char);

int main(int argc, char *argv[]){
	char *path = (char*) malloc(100 * sizeof(char));

	sprintf(path, "/home/dan/Desktop/advent-of-code/%s", argv[1]);

	FILE *f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}
	
	ssize_t read;
	size_t len;
	char *line = NULL;
	int result1 = 0;
	int result2 = 0;

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		if (p1_is_nice_string(line)) result1++;
	}

	rewind(f);

	while((read = getline(&line, &len, f)) != EOF){
		line[strcspn(line, "\n")] = 0;
		if (p2_is_nice_string(line)) result2++;
	}

	printf("%d\n", result1);
	printf("%d\n", result2);
	fclose(f);
	return 0;
}

int is_vowel(char c){
	char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
	for(int i = 0; i < 5; i++){
		if (vowels[i] == c) return TRUE;
	}
	return FALSE;
}

int has_forbidden_string(char *line){
	for(int i = 0; i < strlen(line) - 1; i++){
		if (line[i] == 'a' && line[i + 1] == 'b') return TRUE;
		if (line[i] == 'c' && line[i + 1] == 'd') return TRUE;
		if (line[i] == 'p' && line[i + 1] == 'q') return TRUE;
		if (line[i] == 'x' && line[i + 1] == 'y') return TRUE;
	}
	return FALSE;
}

int p1_is_nice_string(char *line){
	int vowel_count = 0;
	int duplicate_in_row = 0;

	if (has_forbidden_string(line)) return FALSE;

	for(int i = 0; i < strlen(line) - 1; i++){
		if (is_vowel(line[i])) vowel_count++;
		if (line[i] == line[i + 1]) duplicate_in_row++;
		if (vowel_count > 2 && duplicate_in_row > 0) return TRUE;
	}

	if (is_vowel(line[strlen(line) - 1])) vowel_count++;
	return vowel_count > 2 && duplicate_in_row > 0 ? TRUE : FALSE;
}

int p2_is_nice_string(char *line){
	int condition_1 = 0;
	int condition_2 = 0;
	Hashmap_t *hm = hashmap__create();
	char **sub = malloc(16 * sizeof(char*));
	
	for(int i = 0; i < strlen(line) - 1; i++){
		sub[i] = malloc(3 * sizeof(char));
		sub[i][0] = line[i];
		sub[i][1] = line[i + 1];
		sub[i][2] = '\0';

		if (hashmap__add(hm, sub[i], i, i + 1) == 0) condition_1++;
		if (i < strlen(line) - 2 && line[i] == line[i + 2]) condition_2++;
		if (condition_1 > 0 && condition_2 > 0) return TRUE;
	}
	hashmap__free(hm);
	for(int i = 0; i < 16; i++) free(sub[i]);
	free(sub);
	return FALSE;
}