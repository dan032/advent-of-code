#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include "hashmap.h"

void parse_line(Hashmap_t *, char* , long *);
long perform_operation(Hashmap_t*, char *, long, char *);

int main(int argc, char *argv[]){
	FILE *f;
	if (argc > 1){
		char *path = (char*) malloc(100 * sizeof(char));
		sprintf(path, "%s", argv[1]);

		f = fopen(path, "r");
		
		if (f == NULL)
		{
			printf("File not found\n");
			return 1;
		}

		ssize_t read;
		size_t len = 0;
		char *line = NULL;

		long problem2 = 0;

		Hashmap_t *hm = hashmap__create();

		while((read = getline(&line, &len, f)) != EOF){
			line[strcspn(line, "\n")] = 0;
			parse_line(hm, line, &problem2);
		}

		long problem1 = hashmap__get_max_val(hm);
		
		hashmap__free(hm);
		free(path);
		fclose(f);
		printf("%ld\n", problem1);
		printf("%ld\n", problem2);
	}

	return 0;
}

void parse_line(Hashmap_t *hm, char* line, long *result){
	char *id = strtok(line, " ");
	char *ins = strtok(NULL, " ");
	long value = atol(strtok(NULL, " "));
	
	strtok(NULL, " ");

	char *cond_id = strtok(NULL, " ");
	char *cond = strtok(NULL, " ");
	long cond_val = atol(strtok(NULL, " "));

	long tmp_result = LONG_MIN;

	if ((strcmp(cond, "<") == 0) && (hashmap__upsert(hm, cond_id, 0) < cond_val)){
		tmp_result = perform_operation(hm, ins, value, id);
	}
	if ((strcmp(cond, "<=") == 0) && (hashmap__upsert(hm, cond_id, 0) <= cond_val)){
		tmp_result = perform_operation(hm, ins, value, id);
	}
	if ((strcmp(cond, ">") == 0) && (hashmap__upsert(hm, cond_id, 0) > cond_val)){
		tmp_result = perform_operation(hm, ins, value, id);
	}
	if ((strcmp(cond, ">=") == 0) && hashmap__upsert(hm, cond_id, 0) >= cond_val){
		tmp_result = perform_operation(hm, ins, value, id);
	}
	if ((strcmp(cond, "==") == 0) && hashmap__upsert(hm, cond_id, 0) == cond_val){
		tmp_result = perform_operation(hm, ins, value, id);
	}
	if ((strcmp(cond, "!=") == 0) && hashmap__upsert(hm, cond_id, 0) != cond_val){
		tmp_result = perform_operation(hm, ins, value, id);
	}

	*result = *result > tmp_result ? *result : tmp_result;
}

long perform_operation(Hashmap_t *hm, char *op, long value, char *id){
	if(strcmp(op, "inc") == 0){
		return hashmap__upsert(hm, id, value);
	}
	return hashmap__upsert(hm, id, -value);
}