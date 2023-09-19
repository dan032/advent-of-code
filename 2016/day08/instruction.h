#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
    GENERATE, ROTATE_X, ROTATE_Y
} ins_type;

typedef struct {
    ins_type type;
    int x;
    int y;
    int amount;
} instruction_t;

#endif