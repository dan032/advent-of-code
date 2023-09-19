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

		ssize_t read;
		size_t len;
		char *line = NULL;

		long result = 0;

		int arr[5706][3] = {0};

		int idx = 0;
		int column = 0;

		int count = 0;

		while((read = getline(&line, &len, f)) != EOF){
			int s1 = atoi(strtok(line, " "));
			int s2 = atoi(strtok(NULL, " "));
			int s3 = atoi(strtok(NULL, " "));

			arr[idx][column] = s1;
			arr[idx + 1][column] = s2;
			arr[idx + 2][column] = s3;
	
			count++;
			column++;
			
			if (count % 3 == 0){
				column = 0;
				idx += 3;
			}
		}
		for(int i = 0; i < 5706; i++){
			int s1 = arr[i][0];
			int s2 = arr[i][1];
			int s3 = arr[i][2];
			if (((s1 + s2) > s3) && ((s1 + s3) > s2) && ((s2 + s3) > s1)) result++;
		}
		printf("%ld\n", result);
		
		fclose(f);
	}

	return 0;
}

