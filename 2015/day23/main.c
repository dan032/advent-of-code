#include <stdio.h>
#include "computer.h"

int main(int argc, char *argv[]){
    char *path = "/Users/dan2/advent-of-code/2015/day23/input.txt";
	FILE *f = fopen(path, "r");

	unsigned int initial_reg_vals[2] = {0, 0};
    computer_t computer = computer_create(initial_reg_vals, sizeof(initial_reg_vals)/sizeof(unsigned int), 0);

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    computer_load_data(&computer, f);
    computer_perform(&computer);
    computer_print_registers(computer);
	computer_free(computer);
}