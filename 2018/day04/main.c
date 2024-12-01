#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_NUM 1041
#define MAX_GUARD_ID 4000
#define MIN_IN_HOUR 60
#define DAYS_IN_MONTH 30
#define MONTHS_IN_YEAR 12

typedef struct {
    int id;
    int overall_time_slept;
    int time[MONTHS_IN_YEAR][DAYS_IN_MONTH][MIN_IN_HOUR]; // Dont care about year, and only care about a single hour
} guard_t;

int sortStr(const void *str1, const void *str2){
    return strcmp(*(char**) str1, *(char**) str2);
}


int main(){
    char *path = "/Users/dan2/advent-of-code/2018/day04/input.txt";
    FILE *f = fopen(path, "r");

    char **events = (char**) calloc(LINE_NUM, sizeof(char*));
    char *line = NULL, *token = NULL;
    ssize_t read;
    size_t len;
    int idx = 0;
    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';
        events[idx] = (char*) calloc(strlen(line) + 1, sizeof(char));
        strncpy(events[idx++], line, strlen(line));
    }

    qsort(events, LINE_NUM, sizeof(char*), sortStr);
    int month = 0, day = 0, hour = 0, min = 0, id = 0, curr_id = -1;

    for(int i = 0; i < LINE_NUM; i++){
        strtok(events[i], "-");
        month = atoi(strtok(NULL, "-"));
        day   = atoi(strtok(NULL, " "));
        hour  = atoi(strtok(NULL, ":"));
        min   = atoi(strtok(NULL, "]"));
        token = strtok(NULL, " ");


    }

    return 0;
}