#include <stdio.h>
#include "computer.h"
#include "instruction.h"


int main(int argc, char *argv[]){
    char *path = "/Users/dan2/advent-of-code/2015/day23/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    computer_t computer = computer_create(0, 0, 0);
    computer_load_data(&computer, f);
    computer_perform(&computer);
    printf("%d\n", computer.register_b);
}