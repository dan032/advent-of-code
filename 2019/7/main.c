#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#include "IntCodeMachine.h"

int g_idx = 0;

void generate_permutations(long **result, long *input, int size);
long lmax(long a, long b);
void free_int_code_machines(IntCodeMachine_t** amps);

int main(int argc, char *argv[]){
	FILE *f;
	char *path = (char*) malloc(100 * sizeof(char));
	sprintf(path, "%s", argv[1]);

	f = fopen(path, "r");
	
	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

	long maxOutput = LONG_MIN;
	long icm_inputs1[2] = {0};
	long icm_inputs2[1] = {0};
	long inputs[5] = {0};
	long original_phase_setting[5] = {5, 6, 7, 8, 9};
	long **phase_settings = (long**) calloc(120, sizeof(long*));




	generate_permutations(phase_settings, original_phase_setting, 5);

	for(int i = 0; i < 120; i++){
		IntCodeMachine_t *amps[5];
		for(int k = 0; k < 5; k++){
			amps[k] = icm__load(f);
			rewind(f);
		}
		int j = 0;
		int first = 1;
		while(amps[4]->exit == 0){
			if (first){
				icm_inputs1[0] = phase_settings[i][j % 5];
				icm_inputs1[1] = inputs[j % 5];
				// printf("%ld %ld\n", icm_inputs1[0], icm_inputs1[1]);
				icm__set_input(amps[j % 5], icm_inputs1, 2);
				first = 0;
			}
			else{
				icm_inputs2[0] = inputs[j % 5];
				printf("%ld\n", icm_inputs1[0]);
				icm__set_input(amps[j % 5], icm_inputs2, 1);
			}

			icm__perform(amps[j % 5]);

			if (amps[j % 5]->output_ready)
				inputs[(j + 1) % 5] = amps[j % 5]->last_output;
				amps[j % 5]->output_ready = 0;
			j++;
		}
		maxOutput = lmax(maxOutput, amps[4]->last_output);
		free_int_code_machines(amps);
		memset(inputs, 0, sizeof(inputs));
		
	}
	
	printf("%ld\n", maxOutput);
	for(int i = 0; i < 120; i++){
		free(phase_settings[i]);
	}
	free(phase_settings);
	fclose(f);
	free(path);

	return 0;
}

void free_int_code_machines(IntCodeMachine_t** amps){
	for(int j = 0; j < 5; j++){
		icm__free(amps[j]);
	}
}

long lmax(long a, long b){
	return a > b ? a : b;
}

void generate_permutations(long **result, long *input, int size){
	if (size == 1){
		long *p = (long*) calloc(5, sizeof(long));
		memcpy(p, input, 5 * sizeof(long));
		result[g_idx++] = p;
		return;
	}

	for (int i = 0; i < size; i++){
		generate_permutations(result, input, size - 1);

		if (size % 2 == 1){
			int tmp = input[0];
			input[0] = input[size - 1];
			input[size - 1] = tmp;
		}
		else{
			int tmp = input[i];
			input[i] = input[size - 1];
			input[size - 1] = tmp;
		}
	}
}