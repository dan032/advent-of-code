#include <stdlib.h>
#include <stdio.h>

#include "door.h"

int main(){
    char *path = "/Users/dan2/advent-of-code/2016/day08/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("File not found\n");
        return 1;
    }

    door_t door = door_create();
    door_load_data(&door, f);
    door_voltage_check(&door);
    door_count_on_pixels(door);
    door_print_screen(door);
}