#include "stack.h"

Stack_t *stack__create(){
    Stack_t *stack = (Stack_t*) calloc(1, sizeof(Stack_t));
    stack->head = node__create('\0');
    stack->size = 0;
    return stack;
}

int stack__empty(Stack_t *stack){
    stack->size == 0;
}

void stack__push(Stack_t* stack, char c){
    node__push_front(&(stack->head), c);
    stack->size++;
}

char stack__top(Stack_t* stack){
    return node__head_val(stack->head);
}
int stack__pop(Stack_t* stack){
    if stack__empty(stack) return FALSE;
    node__pop_front(&(stack->head));
    stack->size--;
    return TRUE
}

void stack__free(Stack_t* stack){
    node__free(stack->head);
    free(stack);
}
