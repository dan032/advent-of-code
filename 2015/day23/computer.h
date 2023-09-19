#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instruction.h"

#define LINE_COUNT 48

typedef struct {
    unsigned int register_a;
    unsigned int register_b;
    int idx;
    instruction_t instructions[LINE_COUNT];
} computer_t;

computer_t computer_create(int, int, int);
void computer_load_data(computer_t*, FILE*);
void computer_perform(computer_t*);

#endif