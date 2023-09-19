#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

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

		// Need to add ability to know the top 5 frequencies so this passes

		while((read = getline(&line, &len, f)) != EOF){
			line[strcspn(line, "\n")] = 0;
			int arr[26] = {0};
			int checksumIdx = 0;
			int sectorIdx = 0;
			for(int i = 0; i < strlen(line) - 1; i++){
				if (line[i] == '['){
					checksumIdx = i + 1;
					break;
				}
				if (line[i] == '-') continue;
				if (isdigit(line[i]) && sectorIdx == 0){
					sectorIdx = i;
					continue;
				}
				if (isdigit(line[i])) continue;
				// printf("%c|%d|\n", line[i], line[i] - 'a');
				arr[line[i] - 'a']++;
			}
			

			int currVal = INT_MIN;
			for(int i = 0; i < 26; i++){
				currVal = currVal > arr[i] ? currVal : arr[i];
			}
			int is_real = 1;
			// printf("%d|%d|\n", currVal, checksumIdx);
			for(int i = checksumIdx; i < strlen(line) - 2; i++){
				if (arr[line[i] - 'a'] == 0){
					is_real = 0;
					break;
				}
				if (arr[line[i] - 'a'] >= arr[line[i + 1] - 'a']){
					if (arr[line[i] - 'a'] == arr[line[i + 1] - 'a']){
						if ((line[i] - 'a') < (line[i + 1] - 'a')) continue;
						// printf("%s\n", line);
						is_real = 0;
						break;
					}
				}
				else{
					is_real = 0;
					break;
				}
				
				// arr[line[i]] = INT_MAX;
			}

			long sectorVal = 0;
			int p = 0;
			int idx = sectorIdx;
			if (is_real == 1){
				printf("%s\n", line);
				while(line[idx] != '['){
					sectorVal *= 10;
					sectorVal += (line[idx++] - '0');
				}

			}
			// if (sectorVal != 0) printf("%ld\n", sectorVal);
			result += sectorVal;
		}
		printf("%ld\n", result);
		
		fclose(f);
	}

	return 0;
}

