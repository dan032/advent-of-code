#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "instruction.h"

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 48

typedef struct {
    unsigned int *registers;
    size_t n_registers;
    int idx;
    instruction_t instructions[LINE_COUNT];
} computer_t;

computer_t computer_create(unsigned int *, size_t, int);
void computer_load_data(computer_t*, FILE*);
void computer_perform(computer_t*);
void computer_print_registers(computer_t);
void computer_free(computer_t);

#endif