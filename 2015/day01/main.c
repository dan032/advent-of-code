#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	char *path = (char*) malloc(50 * sizeof(char));

	sprintf(path, "/home/dan/Desktop/advent-of-code/%s", argv[1]);
	printf("%s\n", path);

	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	char c;
	long floors = 0;
	long position = 1;
	while((c = fgetc(f)) != EOF){
		if (c == '(') floors++;
		else if (c == ')') floors--;

		if (floors == -1){
			break;
		}
		position++;
	}

	printf("%ld\n", floors);
	printf("%ld\n", position);
	fclose(f);
	return 0;
}

