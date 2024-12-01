#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef enum {
    HLF, TPL, INC, JMP, JIE, JIO
} opcode;

typedef struct {
    opcode code;
    int reg;
    int offset;
} instruction_t;

void instruction_init(instruction_t *, opcode, char*, int);

#endif