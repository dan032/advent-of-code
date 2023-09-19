#include "computer.h"

computer_t computer_create(int a_val, int b_val, int idx_val){
    computer_t computer = {.register_a = 0, .register_b = 0, .idx = 0};
    return computer;
}

void computer_load_data(computer_t *computer, FILE *f){
    int idx = 0;
    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    char reg = '\0';
    while((read = getline(&line, &len, f)) != EOF){
        instruction_t instruction;
        line[strcspn(line, "\n")] = '\0';
        token = strtok(line, " ");

        if(strcmp(token, "hlf") == 0){
            instruction_set(&instruction, HLF, strtok(NULL, "")[0], 0);
        }
        else if(strcmp(token, "tpl") == 0){
            instruction_set(&instruction, TPL, strtok(NULL, "")[0], 0);
        }
        else if(strcmp(token, "inc") == 0){
            instruction_set(&instruction, INC, strtok(NULL, "")[0], 0);
        }
        else if (strcmp(token, "jmp") == 0){
            instruction_set(&instruction, JMP, '\0', atoi(strtok(NULL, "")));
        }
        else if(strcmp(token, "jie") == 0){
            token = strtok(NULL, ", ");
            reg = token[0];
            token = strtok(NULL, "");
            instruction_set(&instruction, JIE, reg, atoi(token));
        }
        else if(strcmp(token, "jio") == 0){
            token = strtok(NULL, ", ");
            reg = token[0];
            token = strtok(NULL, "");
            instruction_set(&instruction, JIO, reg, atoi(token));
        }

        computer->instructions[idx++] = instruction;
    }
}

void computer_perform(computer_t *computer){
    while(computer->idx < LINE_COUNT){
        instruction_t ins = computer->instructions[computer->idx];
        switch(ins.code){
            case HLF: {
                if(ins.reg == 'a') computer->register_a *= 0.5;
                else computer->register_b *= 0.5;
                break;
            }
            case TPL: {
                if(ins.reg == 'a') computer->register_a *= 3;
                else computer->register_b *= 3;
                break;
            }
            case INC: {
                if(ins.reg == 'a') computer->register_a += 1;
                else computer->register_b += 1;
                break;
            }
            case JMP: {
                computer->idx += ins.offset;
                continue;
            }
            case JIE: {
                if(ins.reg == 'a' && computer->register_a % 2 == 0){
                    computer->idx += ins.offset;
                    continue;
                }
                else if(ins.reg == 'b' && computer->register_b % 2 == 0){
                    computer->idx += ins.offset;
                    continue;
                }
                break;
            }
            case JIO: {
                if(ins.reg == 'a' && computer->register_a == 1){
                    computer->idx += ins.offset;
                    continue;
                }
                else if(ins.reg == 'b' && computer->register_b == 1){
                    computer->idx += ins.offset;
                    continue;
                }
                break;
            }
            default: {
                printf("UNSUPPORTED CODE: %d\n", ins.code);
            }
        }

        computer->idx++;
    }
}