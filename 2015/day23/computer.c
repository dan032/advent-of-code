#include "computer.h"

computer_t computer_create(unsigned int *r_vals, size_t r_size, int idx_val){
    computer_t computer = {
        .registers = (unsigned int*) calloc(r_size, sizeof(unsigned int)),
        .n_registers = r_size,
        .idx = idx_val
    };

    for(int i = 0; i < r_size; i++) computer.registers[i] = r_vals[i];

    return computer;
}

void computer_load_data(computer_t *computer, FILE *f){
    ssize_t read;
    size_t len;
    char *line = NULL, *instruction_code = NULL;

    while((read = getline(&line, &len, f)) != EOF){
        instruction_t instruction;
        line[strcspn(line, "\n")] = '\0';
        instruction_code = strtok(line, " ");

        if(strcmp(instruction_code, "hlf") == 0){
            instruction_init(&instruction, HLF, strtok(NULL, ""), 0);
        }
        else if(strcmp(instruction_code, "tpl") == 0){
            instruction_init(&instruction, TPL, strtok(NULL, ""), 0);
        }
        else if(strcmp(instruction_code, "inc") == 0){
            instruction_init(&instruction, INC, strtok(NULL, ""), 0);
        }
        else if (strcmp(instruction_code, "jmp") == 0){
            instruction_init(&instruction, JMP, "\0", atoi(strtok(NULL, "")));
        }
        else if(strcmp(instruction_code, "jie") == 0){
            instruction_init(&instruction, JIE, strtok(NULL, ", "), atoi(strtok(NULL, "")));
        }
        else if(strcmp(instruction_code, "jio") == 0){
            instruction_init(&instruction, JIO, strtok(NULL, ", "), atoi(strtok(NULL, "")));
        }
        else{
            printf("UNSUPPORTED INSTRUCTION CODE IN INPUT: %s\n", instruction_code);
        }

        computer->instructions[computer->idx++] = instruction;
    }
    computer->idx = 0;
}

void computer_perform(computer_t *computer){
    while(computer->idx < LINE_COUNT){
        int increment_idx = TRUE;
        instruction_t ins = computer->instructions[computer->idx];
        switch(ins.code){
            case HLF:
                computer->registers[ins.reg] *= 0.5;
                break;
            case TPL:
                computer->registers[ins.reg] *= 3;
                break;
            case INC:
                computer->registers[ins.reg] += 1;
                break;
            case JMP:
                computer->idx += ins.offset;
                increment_idx = FALSE;
                break;
            case JIE:
                if(computer->registers[ins.reg] % 2 == 0){
                    computer->idx += ins.offset;
                    increment_idx = FALSE;
                }
                break;
            case JIO:
                if(computer->registers[ins.reg] == 1){
                    computer->idx += ins.offset;
                    increment_idx = FALSE;
                }
                break;
            default:
                printf("UNSUPPORTED CODE: %d\n", ins.code);
        }

        if (increment_idx) computer->idx++;
    }
}

void computer_print_registers(computer_t computer){
    for(int i = 0; i < computer.n_registers; i++)
        printf("Register '%c' has a value of %d\n", (i + 'a'), computer.registers[i]);
}

void computer_free(computer_t computer){
    free(computer.registers);
}