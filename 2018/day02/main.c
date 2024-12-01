#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 250

void problem1(FILE *f){
    int freq[LINE_NUM][26];

    for(int i = 0; i < LINE_NUM; i++)
        memset(freq[i], 0, 26 *sizeof(int));

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    int twos = 0;
    int threes = 0;
    int idx = 0;
    while((read = getline(&line, &len, f)) != EOF){
        int two_set = 0;
        int three_set = 0;

        line[strcspn(line, "\n")] = '\0';

        for(int i = 0; i < strlen(line); i++){
            freq[idx][line[i] - 'a']++;
        }

        for(int i = 0; i < 26; i++){
            if (freq[idx][i] == 2 && !two_set){
                twos++;
                two_set = 1;
            }
            if (freq[idx][i] == 3 && !three_set){
                threes++;
                three_set = 1;
            }
        }
        idx++;
    }
    printf("%d\n", twos * threes);
}

void problem2(FILE *f){
    char **id_array = (char**) calloc(LINE_NUM, sizeof(char*));

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    int idx = 0;
    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';
        id_array[idx] = (char*) calloc(strlen(line) + 1, sizeof(char));
        strncpy(id_array[idx++], line, strlen(line));
    }

    for(int i = 0; i < LINE_NUM; i++){
        for(int j = i + 1; j < LINE_NUM; j++){
            int differences = 0;
            for(int k = 0; k < strlen(id_array[i]); k++){
                if (id_array[i][k] != id_array[j][k]) differences++;
                if (differences > 1) break;
            }
            if (differences == 1){
                printf("%s -> %s\n", id_array[i], id_array[j]);
                return;
            }
        }
    }
}

int main(){
    char *path = "/Users/dan2/advent-of-code/2018/day02/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("404!\n");
        return 1;
    }


    problem1(f);
    rewind(f);
    problem2(f);

    return 0;
}