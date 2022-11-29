#ifndef INT_CODE_MACHINE_H
#define INT_CODE_MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int *opcodes;
    int *loaded_memory;
    size_t opcodes_len;
    int instruction_pointer;
} IntCodeMachine_t;

IntCodeMachine_t *icm__load(FILE *);
void icm__perform(IntCodeMachine_t*);
void icm__1202_program_alarm(IntCodeMachine_t*, int, int);
void icm__reset(IntCodeMachine_t*);
void icm__free(IntCodeMachine_t*);

#endif