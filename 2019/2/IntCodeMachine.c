#include "IntCodeMachine.h"

IntCodeMachine_t *icm__load(FILE *f){
    IntCodeMachine_t *icm = (IntCodeMachine_t*) calloc(1, sizeof(IntCodeMachine_t));
    
    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    long count = 0;
    int curr = 0;
    int idx = 0;
    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        token = strtok(line, ",");
        count++;

        while(token = strtok(NULL, ",")){
            if (token = NULL) break;
            count++;
        }
    }
    rewind(f);
    icm->opcodes = (int*) calloc(count, sizeof(int));
    icm->loaded_memory = (int*) calloc(count, sizeof(int));
    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = 0;
        curr = atoi(strtok(line, ","));

        icm->opcodes[idx] = curr;
        icm->loaded_memory[idx++] = curr;

        while(token = strtok(NULL, ",")){
            if (token == NULL) break;
            icm->opcodes[idx] = atoi(token);
            icm->loaded_memory[idx++] = atoi(token);
        }
    }
    icm->opcodes_len = count;
    icm->instruction_pointer = 0;
    return icm;
}
void icm__perform(IntCodeMachine_t *icm){
    int operand1 = 0;
    int operand2 = 0;
    int location = 0;

    while (icm->opcodes[icm->instruction_pointer] != 99){
        if (icm->opcodes[icm->instruction_pointer] == 1){
            operand1 = icm->opcodes[icm->instruction_pointer + 1];
            operand2 = icm->opcodes[icm->instruction_pointer + 2];
            location = icm->opcodes[icm->instruction_pointer + 3];

            icm->opcodes[location] = icm->opcodes[operand1] + icm->opcodes[operand2];
        }
        else if (icm->opcodes[icm->instruction_pointer] == 2){
            operand1 = icm->opcodes[icm->instruction_pointer + 1];
            operand2 = icm->opcodes[icm->instruction_pointer + 2];
            location = icm->opcodes[icm->instruction_pointer + 3];

            icm->opcodes[location] = icm->opcodes[operand1] * icm->opcodes[operand2];
        }
        icm->instruction_pointer += 4;
    }
}

void icm__1202_program_alarm(IntCodeMachine_t *icm, int noun, int verb){
    icm->opcodes[1] = noun;
    icm->opcodes[2] = verb;
}

void icm__reset(IntCodeMachine_t *icm){
    for(int i = 0; i < icm->opcodes_len; i++){
        icm->opcodes[i] = icm->loaded_memory[i];
    }
    icm->instruction_pointer = 0;
}

void icm__free(IntCodeMachine_t *icm){
    free(icm->opcodes);
    free(icm);
}