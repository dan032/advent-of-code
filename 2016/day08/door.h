#ifndef DOOR_H
#define DOOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

#define LINE_NUM 145
#define SCREEN_HEIGHT 6
#define SCREEN_WIDTH 50

typedef struct {
    instruction_t instructions[LINE_NUM];
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
} door_t;
door_t door_create();
void door_load_data(door_t*, FILE*);
void door_voltage_check(door_t*);
void door_count_on_pixels(door_t);
void door_print_screen(door_t);
#endif