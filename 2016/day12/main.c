#include "computer.h"

int main(){
    computer_t computer = computer_create();
    char *path = "/Users/dan2/advent-of-code/2016/day12/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("File not found\n");
        return 1;
    }

    computer_load_data(&computer, f);
    computer_perform(&computer);
    computer_print_registers(computer);
}