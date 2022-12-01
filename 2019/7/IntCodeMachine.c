#include "IntCodeMachine.h"

#define ENABLE_DEBUGGING 0

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
    size_t len = 0;
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
    icm->wait_for_input = TRUE;
    icm->output_ready = FALSE;
    free(line);
    return icm;
}

void icm_set_current_opcode(IntCodeMachine_t *icm){
    long opcode = icm->opcodes[icm->instruction_pointer];
    long extracted_opcode = 0;
    long last_digit = opcode % 10;
    opcode /= 10;
    extracted_opcode += (opcode % 10);
    extracted_opcode *= 10;
    extracted_opcode += last_digit;

    icm->current_instruction = extracted_opcode;
    if (ENABLE_DEBUGGING)
        printf("COP: %ld\n", extracted_opcode);
}

void icm__increment_ip(IntCodeMachine_t *icm){
    switch(icm->current_instruction){
        case ADD_OP:
        case MULT_OP:
        case LT_OP:
        case EQ_OP:
            icm->instruction_pointer += 4;
            break;
        case INPUT_OP:
            if (!icm->wait_for_input)
                icm->instruction_pointer += 2;
            break;
        case OUTPUT_OP:
            icm->instruction_pointer += 2;
            break;
        case JIT_OP:
        case JIF_OP:
            if (!icm->ip_modified) icm->instruction_pointer += 3;
            break;
        case HALT_OP:           // MAYBE
            icm->instruction_pointer += 1;
            break;
        default:
            printf("Unknown opcode - increment\n");
            icm->exit = TRUE;
    }
    icm->ip_modified = FALSE;
    if (ENABLE_DEBUGGING)
        printf("IP: %ld\n", icm->instruction_pointer);
}

void icm__set_parameter_modes(IntCodeMachine_t *icm){
    long instruction = icm->opcodes[icm->instruction_pointer];
    if (instruction == HALT_OP) return;

    instruction /= 10;
    instruction /= 10;
    
    icm->parameter_modes[0] = instruction & 1;
    instruction /= 10;
    icm->parameter_modes[1] = instruction & 1;
    instruction /= 10;
    icm->parameter_modes[2] = instruction & 1;
    if (ENABLE_DEBUGGING)
        printf("PMs: %d %d %d\n", icm->parameter_modes[0], icm->parameter_modes[1], icm->parameter_modes[2]);
}

long get_operand(IntCodeMachine_t *icm, int pm_idx, int offset){
    long operand = 0;
    if (icm->parameter_modes[pm_idx] == POSITION_MODE){
        operand = icm->opcodes[icm->opcodes[icm->instruction_pointer + offset]];
    }
    else if (icm->parameter_modes[pm_idx] == IMMEDIATE_MODE){
        operand = icm->opcodes[icm->instruction_pointer + offset];
    }
    if (ENABLE_DEBUGGING)
        printf("OP: %ld| IP: %ld\n", operand, icm->instruction_pointer + offset);
    return operand;
}

void icm__perform_operation(IntCodeMachine_t *icm){
    long operand1 = 0, operand2 = 0, location = 0;
    switch(icm->current_instruction){
        case ADD_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2);
            location = icm->opcodes[icm->instruction_pointer + 3];
            icm->opcodes[location] = operand1 + operand2;

            if (ENABLE_DEBUGGING) 
                printf("ADD: L(%ld) R(%ld)\n", location, (operand1 + operand2));
            break;

        case MULT_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2);
            location = icm->opcodes[icm->instruction_pointer + 3];
            icm->opcodes[location] = operand1 * operand2;

            if (ENABLE_DEBUGGING)
                printf("MUL: L(%ld) R(%ld)\n", location, (operand1 * operand2));
            break;

        case INPUT_OP:
            if (icm->curr_input_idx < icm->input_len){
                operand1 = icm->inputs[icm->curr_input_idx];
                location = icm->opcodes[icm->instruction_pointer + 1];
                icm->opcodes[location] = operand1;
                // printf("IN: %ld\n", operand1);
                icm->curr_input_idx++;
            }
            else{
                icm->wait_for_input = TRUE;
            }

            break;

        case OUTPUT_OP:
            operand1 = get_operand(icm, 0, 1);
            icm->last_output = operand1;
            icm->output_ready = TRUE;
            break;

        case JIT_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2);
            
            if (operand1 == FALSE) break;
            icm->instruction_pointer = operand2;
            icm->ip_modified = TRUE;    
            break;

        case JIF_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2);
            
            if (operand1 != FALSE) break;
            icm->instruction_pointer = operand2;
            icm->ip_modified = TRUE;
            break;

        case LT_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2); 
            location = icm->opcodes[icm->instruction_pointer + 3];
            icm->opcodes[location] = operand1 < operand2 ? 1 : 0;
            break;
        
        case EQ_OP:
            operand1 = get_operand(icm, 0, 1);
            operand2 = get_operand(icm, 1, 2); 
            location = icm->opcodes[icm->instruction_pointer + 3];
            icm->opcodes[location] = operand1 == operand2 ? 1 : 0;
            break;

        case HALT_OP:
            icm->exit = TRUE;
            break;
        default:
            printf("Invalid Opcode\n");
            icm->exit = TRUE;
    }
}

void icm__perform(IntCodeMachine_t *icm){
    // icm->exit = FALSE;
    while (icm->exit == FALSE && icm->wait_for_input == FALSE){     // MAYBE
        icm_set_current_opcode(icm);
        if (icm->exit) break;
        icm__set_parameter_modes(icm);
        if (icm->exit) break;
        icm__perform_operation(icm);
        if (icm->exit) break;
        icm__increment_ip(icm);

        if (ENABLE_DEBUGGING)
            printf("----------\n");
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
    icm->curr_input_idx = 0;
    icm->last_output = 0;
    icm->current_instruction = 0;
    icm->ip_modified = FALSE;
    icm->exit = FALSE;
}

void icm__free(IntCodeMachine_t *icm){
    free(icm->opcodes);
    free(icm->inputs);
    free(icm->loaded_memory);
    free(icm->parameter_modes);
    free(icm);
}

void icm__set_input(IntCodeMachine_t *icm, long *inputs, int input_len){
    if (icm->inputs != NULL){
        free(icm->inputs);
    }
    long *p = (long*) calloc(input_len, sizeof(long));
    memcpy(p, inputs, input_len * sizeof(long));
    icm->inputs = p;
    icm->input_len = input_len;
    icm->curr_input_idx = 0;
    icm->wait_for_input = FALSE;
    if (ENABLE_DEBUGGING)
        printf("INPUTS: %ld %ld\n", icm->inputs[0], icm->inputs[1]);
}