#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "instruction.h"

#define LINE_NUM 23
#define N_REGISTERS 4

typedef struct {
    ins_t instructions[LINE_NUM];
    int registers[N_REGISTERS];
    size_t idx;
} computer_t;

computer_t computer_create();
void computer_load_data(computer_t*, FILE*);
void computer_perform(computer_t*);
void computer_print_registers(computer_t);

#endif