#include "door.h"

door_t door_create(){
    door_t door;
    for(int i = 0; i < SCREEN_HEIGHT; i++)
        memset(door.screen[i], '.', SCREEN_WIDTH);

    return door;
}

void door_print_screen(door_t door){
    for(int i = 0; i < SCREEN_HEIGHT; i++){
        for(int j = 0; j < SCREEN_WIDTH; j++) printf("%c", door.screen[i][j]);
        printf("\n");
    }
    printf("\n\n\n");
}

void door_count_on_pixels(door_t door){
    int res = 0;
    for(int i = 0; i < SCREEN_HEIGHT; i++){
        for(int j = 0; j < SCREEN_WIDTH; j++) if (door.screen[i][j] == '#') res++;
    }
    printf("%d\n", res);
}

void door_load_data(door_t *door, FILE *f){
    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    int idx = 0;
    while((read = getline(&line, &len, f)) != EOF){
        instruction_t ins;
        line[strcspn(line, "\n")] = '\0';
        token = strtok(line, " ");

        if (strcmp(token, "rect") == 0){
            ins = (instruction_t) {.type = GENERATE, .x = atoi(strtok(NULL, "x")), .y = atoi(strtok(NULL, "")), .amount = 0};
        }
        else if (strcmp(token, "rotate") == 0){
            token = strtok(NULL, " ");
            if (strcmp(token, "row") == 0){
                ins = (instruction_t) {.type = ROTATE_Y, .x = 0, .y = atoi(strtok(NULL, " y="))};
                ins.amount = atoi(strtok(NULL, "by "));
            }
            else if (strcmp(token, "column") == 0){
                ins = (instruction_t) {.type = ROTATE_X, .x = atoi(strtok(NULL, " x=")), .y = 0};
                ins.amount = atoi(strtok(NULL, "by "));
            }
        }
        door->instructions[idx++] = ins;
    }
}

void door_voltage_check(door_t *door){
    for(int i = 0; i < LINE_NUM; i++){
        instruction_t ins = door->instructions[i];

        switch(ins.type){
            case GENERATE:
                for(int y = 0; y < ins.y; y++){
                    for(int x = 0; x < ins.x; x++){
                        door->screen[y][x] = '#';
                    }
                }
                break;
            case ROTATE_X:{
                char copy[SCREEN_HEIGHT];
                for(int i = 0; i < SCREEN_HEIGHT; i++) copy[i] = door->screen[i][ins.x];
                for(int i = 0; i < SCREEN_HEIGHT; i++){
                    int shift_idx = (i - ins.amount) < 0 ? SCREEN_HEIGHT + i - ins.amount : i - ins.amount;
                    door->screen[i][ins.x] = copy[shift_idx];
                }
                break;
            }
            case ROTATE_Y: {
                char copy[SCREEN_WIDTH];
                for(int i = 0; i < SCREEN_WIDTH; i++) copy[i] = door->screen[ins.y][i];
                for(int i = 0; i < SCREEN_WIDTH; i++){
                    int shift_idx = ((i - ins.amount) < 0) ? SCREEN_WIDTH + i - ins.amount : i - ins.amount;
                    door->screen[ins.y][i] = copy[shift_idx];
                }
                break;
            }
        }
    }
}