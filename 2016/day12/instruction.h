#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    CPY, INC, DEC, JNZ
} ins_code;

typedef struct {
    ins_code code;
    bool x_reg;
    bool y_reg;
    int x;
    int y;
} ins_t;

#endif