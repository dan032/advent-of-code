#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N_DIGITS 4
#define MAX_LINE_LEN 8000

long long get_length(char *str, int last_repeat){
    char sub_chars[MAX_N_DIGITS], repeat[MAX_N_DIGITS];
    char *nextStr;
    long long count = 0;

    for(int i = 0; i < strlen(str); i++){
        if (str[i] == '('){
            int n_chars = 0, n_repeat = 0, idx = 0;
            memset(sub_chars, '\0', MAX_N_DIGITS);
            memset(repeat, '\0', MAX_N_DIGITS);

            while(str[++i] != 'x'){
                sub_chars[idx++] = str[i];
            }

            idx = 0;
            while(str[++i] != ')'){
                repeat[idx++] = str[i];
            }

            n_chars = atoi(sub_chars), n_repeat = atoi(repeat);
            nextStr = (char*) calloc(n_chars + 1, sizeof(char));
            strncpy(nextStr, &(str[++i]), n_chars);

            count += get_length(nextStr, n_repeat);
            i += n_chars - 1;
            free(nextStr);
        }
        else count++;
    }
    return count * last_repeat;
}

int main(){
    char *path = "/Users/dan2/advent-of-code/2016/day09/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("File not found\n");
        return 1;
    }

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;

    getline(&line, &len, f);
    line[strcspn(line, "\n")] = '\0';

    printf("%lld\n", get_length(line, 1));
}