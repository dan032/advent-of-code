#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 4000000
#define ITERATIONS 50

int main(){
    static char buffers[2][BUFFER_SIZE];
    char *buffer1 = NULL, *buffer2 = NULL;
    int ai = 0, bi = 0, digit = 0, count = 0;

    strncpy(buffers[0], "1113122113", BUFFER_SIZE);
    for(int i = 0; i < ITERATIONS; i++){
        buffer1 = buffers[(i & 1)];
        buffer2 = buffers[!(i & 1)];
        ai = 1, bi = 0, digit = buffer1[0], count = 1;

        while(buffer1[ai - 1]){
            if (buffer1[ai] == digit) count++;
            else {
                buffer2[bi++] = count + '0';
                buffer2[bi++] = digit;
                count = 1;
                digit = buffer1[ai];
            }
            ai++;
        }
        buffer2[bi] = '\0';
    }
    printf("%zu\n", strlen(buffer2));
    return 0;
}