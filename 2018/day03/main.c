#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X_DIMS 2000
#define Y_DIMS 2000
#define LINE_NUMS 1341

int main(){
    char *path = "/Users/dan2/advent-of-code/2018/day03/input.txt";
    FILE *f = fopen(path, "r");

    if (f == NULL){
        printf("404\n");
        return 1;
    }

    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    static int matrix[Y_DIMS][X_DIMS];
    static int size_matrix[LINE_NUMS + 1];

    int id = 0, offset_y = 0, offset_x = 0, width = 0, height = 0;

    for(int i = 0; i < Y_DIMS; i++) memset(matrix[i], 0, X_DIMS * sizeof(int));
    memset(size_matrix, -1, (LINE_NUMS + 1) * sizeof(int));

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';
        line++;
        id = atoi(strtok(line, " "));
        strtok(NULL, " ");

        offset_x = atoi(strtok(NULL, ","));
        offset_y = atoi(strtok(NULL, ":"));
        width = atoi(strtok(NULL, "x"));
        height = atoi(strtok(NULL, ""));

        size_matrix[id] = (width * height);

        for(int i = offset_y; i < offset_y + height; i++){
            for(int j = offset_x; j < offset_x + width; j++){
                if (matrix[i][j] == 0) matrix[i][j] = id;
                else matrix[i][j] = -1;
            }
        }
    }

    int result = 0;
    int idx = 0;
    for(int i = 0; i < Y_DIMS; i++){
        for(int j = 0; j < X_DIMS; j++){
            if(matrix[i][j] != -1) size_matrix[matrix[i][j]]--;
        }
    }

    for(int i = 0; i < LINE_NUMS; i++){
        if (size_matrix[i] == 0){
            printf("%d\n", i);
            return 0;
        }
    }
}