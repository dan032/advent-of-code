#include "instruction.h"

void instruction_set(instruction_t *ins, opcode code, char reg, int offset){
    ins->code = code;
    ins->reg = reg;
    ins->offset = offset;
}
