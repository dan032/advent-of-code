#include "computer.h"

computer_t computer_create(){
    computer_t computer = {.idx = 0};
    memset(computer.registers, 0, N_REGISTERS * sizeof(int));
    computer.registers[2] = 1;
    return computer;
}

int get_field_value(char *str, bool *is_reg){
    int val = 0;
    if (!isdigit(str[0])){
        *is_reg = true;
        val = str[0] - 'a';
    }
    else val = atoi(str);
    return val;
}


void computer_load_data(computer_t *computer, FILE *f){
    char *line = NULL, *code = NULL, *x_char = NULL, *y_char = NULL;
    ssize_t read;
    size_t len;
    ins_code i_code;
    int x = 0, y = 0;

    while((read = getline(&line, &len, f)) != EOF){
        bool x_reg = false, y_reg = false;
        line[strcspn(line, "\n")] = '\0';
        code = strtok(line, " ");

        if (strcmp(code, "cpy") == 0){
            x = get_field_value(strtok(NULL, " "), &x_reg);
            y = get_field_value(strtok(NULL, " "), &y_reg);
            i_code = CPY;
        }
        else if (strcmp(code, "inc") == 0){
            x = strtok(NULL, "")[0] - 'a';
            x_reg = true;
            i_code = INC;
        }
        else if (strcmp(code, "dec") == 0){
            x = strtok(NULL, "")[0] - 'a';
            x_reg = true;
            i_code = DEC;
        }
        else if (strcmp(code, "jnz") == 0){
            x = get_field_value(strtok(NULL, " "), &x_reg);
            y = atoi(strtok(NULL, " "));
            i_code = JNZ;
        }
        else {
            printf("Unsupported Command Type\n");
        }
        computer->instructions[computer->idx++] = (ins_t) {.code = i_code, .x_reg = x_reg, .y_reg = y_reg, .x = x, .y = y};
    }
    computer->idx = 0;
}

void computer_perform(computer_t *computer){
    while(computer->idx < LINE_NUM){
        ins_t ins = computer->instructions[computer->idx];
        switch(ins.code){
            case CPY: {
                if (ins.x_reg) computer->registers[ins.y] = computer->registers[ins.x];
                else computer->registers[ins.y] = ins.x;;
                break;
            }
            case INC: {
                computer->registers[ins.x]++;
                break;
            }
            case DEC: {
                computer->registers[ins.x]--;
                break;
            }
            case JNZ: {
                if ((ins.x_reg && computer->registers[ins.x] != 0) || (!ins.x_reg && ins.x != 0)){
                    computer->idx += ins.y;
                    continue;
                }
                break;
            }
        }
        computer->idx++;
    }
}

void computer_print_registers(computer_t computer){
    for(int i = 0; i < N_REGISTERS; i++)
        printf("Register %c is set to %d\n", (i + 'a'), computer.registers[i]);
}