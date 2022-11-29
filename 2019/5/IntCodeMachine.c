#include "IntCodeMachine.h"

#define ADD_OP 1
#define MULT_OP 2
#define INPUT_OP 3
#define OUTPUT_OP 4
#define JIT_OP 5
#define JIF_OP 6
#define LT_OP 7
#define EQ_OP 8
#define HALT_OP 99

#define POSITION_MODE 0
#define IMMEDIATE_MODE 1

#define TRUE 1
#define FALSE 0

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
            if (token == NULL) break;
            count++;
        }
    }
    rewind(f);
    icm->opcodes = (long*) calloc(count, sizeof(long));
    icm->loaded_memory = (long*) calloc(count, sizeof(long));
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
    icm->ip_modified = FALSE;
    icm->parameter_modes = (int*) calloc(3, sizeof(int));
    return icm;
}

void icm_set_current_opcode(IntCodeMachine_t *icm){
    int opcode = icm->opcodes[icm->instruction_pointer];
    int extracted_opcode = 0;
    int last_digit = opcode % 10;
    opcode /= 10;
    extracted_opcode += (opcode % 10);
    extracted_opcode *= 10;
    extracted_opcode += last_digit;

    icm->current_instruction = extracted_opcode;
    // printf("CI Set: %d\n", extracted_opcode);
}

void icm__increment_ip(IntCodeMachine_t *icm){
    if (icm->current_instruction == ADD_OP) icm->instruction_pointer += 4;
    else if (icm->current_instruction == MULT_OP) icm->instruction_pointer += 4;
    else if (icm->current_instruction == INPUT_OP) icm->instruction_pointer += 2;
    else if (icm->current_instruction == OUTPUT_OP) icm->instruction_pointer += 2;
    else if (icm->current_instruction == JIT_OP && !icm->ip_modified) icm->instruction_pointer += 3;
    else if (icm->current_instruction == JIF_OP && !icm->ip_modified) icm->instruction_pointer += 3;
    else if (icm->current_instruction == LT_OP) icm->instruction_pointer += 4;
    else if (icm->current_instruction == EQ_OP) icm->instruction_pointer += 4;
    icm->ip_modified = FALSE;
    // printf("IP: %d\n", icm->instruction_pointer);
}

void icm__set_parameter_modes(IntCodeMachine_t *icm){
    int instruction = icm->opcodes[icm->instruction_pointer];
    if (instruction == HALT_OP) return;

    instruction /= 10;
    instruction /= 10;
    
    icm->parameter_modes[0] = instruction & 1;
    instruction /= 10;
    icm->parameter_modes[1] = instruction & 1;
    instruction /= 10;
    icm->parameter_modes[2] = instruction & 1;
    // printf("PM Set: %d %d %d\n", icm->parameter_modes[0], icm->parameter_modes[1], icm->parameter_modes[2]);
}

long get_operand(IntCodeMachine_t *icm, int pm_idx, int offset){
    long operand = 0;
    if (icm->parameter_modes[pm_idx] == POSITION_MODE){
        operand = icm->opcodes[icm->opcodes[icm->instruction_pointer + offset]];
    }
    else if (icm->parameter_modes[pm_idx] == IMMEDIATE_MODE){
        operand = icm->opcodes[icm->instruction_pointer + offset];
    }
    return operand;
}

void icm__perform_operation(IntCodeMachine_t *icm){
    long operand1 = 0, operand2 = 0, location = 0;

    if (icm->current_instruction == ADD_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2);
        location = icm->opcodes[icm->instruction_pointer + 3];
        
        icm->opcodes[location] = operand1 + operand2;
    }
    else if (icm->current_instruction == MULT_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2);
        location = icm->opcodes[icm->instruction_pointer + 3];

        icm->opcodes[location] = operand1 * operand2;
    }
    else if (icm->current_instruction == INPUT_OP){
        operand1 = 5;
        location = icm->opcodes[icm->instruction_pointer + 1];

        icm->opcodes[location] = operand1;
    }
    else if (icm->current_instruction == OUTPUT_OP){
        operand1 = get_operand(icm, 0, 1);
        printf("Output: %ld\n", operand1);
    }
    else if (icm->current_instruction == JIT_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2);
        
        if (operand1){
            icm->instruction_pointer = operand2;
            icm->ip_modified = TRUE;
        }
    }
    else if (icm->current_instruction == JIF_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2);
        
        if (operand1 == 0){
            icm->instruction_pointer = operand2;
            icm->ip_modified = TRUE;
        }
    }
    else if (icm->current_instruction == LT_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2); 
        location = icm->opcodes[icm->instruction_pointer + 3];

        if (operand1 < operand2){
            icm->opcodes[location] = 1;
        }
        else{
            icm->opcodes[location] = 0;
        }
    }
    else if (icm->current_instruction == EQ_OP){
        operand1 = get_operand(icm, 0, 1);
        operand2 = get_operand(icm, 1, 2); 
        location = icm->opcodes[icm->instruction_pointer + 3];

        if (operand1 == operand2){
            icm->opcodes[location] = 1;
        }
        else{
            icm->opcodes[location] = 0;
        }
    }
    else{
        printf("Invalid Opcode\n");
    }
}

void icm__perform(IntCodeMachine_t *icm){
    while (icm->opcodes[icm->instruction_pointer] != HALT_OP){
        // printf("RI: %ld\n", icm->opcodes[icm->instruction_pointer]);
        icm_set_current_opcode(icm);
        icm__set_parameter_modes(icm);
        icm__perform_operation(icm);
        icm__increment_ip(icm);
        // printf("--------------\n");

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
    free(icm->parameter_modes);
    free(icm);
}