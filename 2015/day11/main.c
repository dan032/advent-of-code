#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int validate(char *);

int main(int argc, char *argv[]){
    char *c = calloc(9, sizeof(char));
    strncpy(c, "hxbxxyzz", 8);

    int idx = strlen(c) - 1;
    while(TRUE){
        c[idx]++;
        while (c[idx] > 'z'){
            c[idx] = 'a';
            idx--;
            c[idx]++;
        }
        idx = strlen(c) - 1;
        if (validate(c)){
            printf("%s\n", c);
            return 0;
        }
    }
}

int validate(char *c){
    int first_req = FALSE;
    int third_req = FALSE;
    int last_idx = -1;
    int third_count = 0;
    char first_char = '0';
    for(int i = 0; i < strlen(c); i++){
        if (i != 0 || i != (strlen(c) - 1)){
            if (c[i - 1] == (c[i] - 1) && (c[i + 1] == c[i] + 1)) first_req = TRUE;
        }

        if (c[i] == 'i' || c[i] == 'o' || c[i] == 'l') return FALSE;

        if (i != 0){
            if (c[i] == c[i - 1]){
                if (third_count == 1 && first_char == c[i]) continue;
                third_count++;
                first_char = c[i];

                if(third_count == 2) third_req = TRUE;
            }
        }
    }
    return first_req & third_req;
}

