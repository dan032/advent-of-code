#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define LINE_COUNT 4

typedef struct {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
    int amount;
} ingredient_t;

void problem1(FILE *f);

int main(int argc, char *argv[]){

	char *path = "/Users/dan2/advent-of-code/2015/15/input.txt";
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		printf("File not found\n");
		return 1;
	}

    problem1(f);
}

void problem1(FILE *f){
    ssize_t read;
    size_t len;
    char *line = NULL, *token = NULL;
    ingredient_t ingredients[LINE_COUNT];
    int idx = 0;

    while((read = getline(&line, &len, f)) != EOF){
        line[strcspn(line, "\n")] = '\0';
        token = strtok(line, " ");
        strtok(NULL, " ");

        ingredient_t ingredient;
        token = strtok(NULL, ",");
        ingredient.capacity = atoi(token);
        strtok(NULL, " ");

        token = strtok(NULL, ",");
        ingredient.durability = atoi(token);
        strtok(NULL, " ");

        token = strtok(NULL, ",");
        ingredient.flavor = atoi(token);
        strtok(NULL, " ");

        token = strtok(NULL, ",");
        ingredient.texture = atoi(token);
        strtok(NULL, " ");

        token = strtok(NULL, "");
        ingredient.calories = atoi(token);
        ingredient.amount = 25;

        ingredients[idx++] = ingredient;
        // printf("%d %d %d %d %d\n", ingredient.capacity, ingredient.durability, ingredient.flavor, ingredient.texture, ingredient.calories);
    }

    for(int i = 0; i < 30; i++){
        int cap = 0;
        int dur = 0;
        int flavor = 0;
        int texture = 0;

        for(int j = 0; j < LINE_COUNT; j++){
            if (j == 0) ingredients[j].amount++;
            if (j == 1) ingredients[j].amount++;
            if (j == 2) ingredients[j].amount--;
            else ingredients[j].amount--;

            cap += (ingredients[j].capacity * ingredients[j].amount);
            dur += (ingredients[j].durability * ingredients[j].amount);
            flavor += (ingredients[j].flavor * ingredients[j].amount);
            texture += (ingredients[j].texture * ingredients[j].amount);
        }

        printf("Cap: %d, Dur: %d, Flav: %d, Text: %d\t", cap, dur, flavor, texture);
        printf("%d\n\n", cap * dur * flavor * texture);
    }
}