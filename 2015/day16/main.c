#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 500

typedef struct {
    int id;
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} aunt_t;


void problem1(FILE *f);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/16/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    problem1(f);
}

aunt_t aunt_init(is_real_aunt){
    aunt_t aunt;
    aunt.id = 0;
    if (is_real_aunt){
        aunt.children = 3;
        aunt.cats = 7;
        aunt.samoyeds = 2;
        aunt.pomeranians = 3;
        aunt.akitas = 0;
        aunt.vizslas = 0;
        aunt.goldfish = 5;
        aunt.trees = 3;
        aunt.cars = 2;
        aunt.perfumes = 1;
    }
    else{
        aunt.children = -1;
        aunt.cats = -1;
        aunt.samoyeds = -1;
        aunt.pomeranians = -1;
        aunt.akitas = -1;
        aunt.vizslas = -1;
        aunt.goldfish = -1;
        aunt.trees = -1;
        aunt.cars = -1;
        aunt.perfumes = -1;
    }
    return aunt;
}

void aunt_set_field(aunt_t* aunt, char *field, int val){
    if (strcmp(field, "children") == 0){
        aunt->children = val;
    }
    else if (strcmp(field, "cats") == 0){
        aunt->cats = val;
    }
    else if (strcmp(field, "samoyeds") == 0){
        aunt->samoyeds = val;
    }
    else if (strcmp(field, "pomeranians") == 0){
        aunt->pomeranians = val;
    }
    else if (strcmp(field, "akitas") == 0){
        aunt->akitas = val;
    }
    else if (strcmp(field, "vizslas") == 0){
        aunt->vizslas = val;
    }
    else if (strcmp(field, "goldfish") == 0){
        aunt->goldfish = val;
    }
    else if (strcmp(field, "trees") == 0){
        aunt->trees = val;
    }
    else if (strcmp(field, "cars") == 0){
        aunt->cars = val;
    }
    else if (strcmp(field, "perfumes") == 0){
        aunt->perfumes = val;
    }
    else{
        printf("ERROR: Field %s does not exist\n", field);
    }
}

int is_possible_aunt(aunt_t real_aunt, aunt_t possible_aunt){
    if (real_aunt.children != possible_aunt.children && possible_aunt.children != -1) return FALSE;
    if (real_aunt.cats >= possible_aunt.cats && possible_aunt.cats != -1) return FALSE;
    if (real_aunt.samoyeds != possible_aunt.samoyeds && possible_aunt.samoyeds != -1) return FALSE;
    if (real_aunt.pomeranians <= possible_aunt.pomeranians && possible_aunt.pomeranians != -1) return FALSE;
    if (real_aunt.akitas != possible_aunt.akitas && possible_aunt.akitas != -1) return FALSE;
    if (real_aunt.vizslas != possible_aunt.vizslas && possible_aunt.vizslas != -1) return FALSE;
    if (real_aunt.goldfish <= possible_aunt.goldfish && possible_aunt.goldfish != -1) return FALSE;
    if (real_aunt.trees >= possible_aunt.trees && possible_aunt.trees != -1) return FALSE;
    if (real_aunt.cars != possible_aunt.cars && possible_aunt.cars != -1) return FALSE;
    if (real_aunt.perfumes != possible_aunt.perfumes && possible_aunt.perfumes != -1) return FALSE;
    return TRUE;
}

void problem1(FILE *f){
    ssize_t read;
    size_t len;

    char *line = NULL, *token = NULL;
    char *field = NULL;
    aunt_t real_aunt = aunt_init(TRUE);
    int idx = 0;

    while((read = getline(&line, &len, f)) != EOF){
        aunt_t possible_aunt = aunt_init(FALSE);
        line[strcspn(line, "\n")] = '\0';

        strtok(line, " ");
        token = strtok(NULL, ":");
        possible_aunt.id = atoi(token);

        for(int i = 0; i < 3; i++){
            token = strtok(NULL, ": ");
            field = (char*) calloc(strlen(token) + 1, sizeof(char));
            strncpy(field, token, strlen(token));

            token = strtok(NULL, ",");
            aunt_set_field(&possible_aunt, field, atoi(token));
        }

        if (is_possible_aunt(real_aunt, possible_aunt)){
            printf("%d\n", possible_aunt.id);
            return;
        }
    }
}