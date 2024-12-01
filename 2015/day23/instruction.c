#include "instruction.h"

void instruction_init(instruction_t *ins, opcode code, char *reg, int offset){
    ins->code = code;
    ins->reg = reg[0] - 'a';
    ins->offset = offset;
}
