#include "stack_probe.h"
#include <stdlib.h>
#include <string.h>

Stack_P Stack_P_create() {
    Stack_P stack = malloc(sizeof(Stack_P *));
    stack->capacity = 5;
    stack->top = 0;
    stack->array = malloc(sizeof(Probe) * 5);
    for(int i = 0; i < 5; i++) {
        stack->array[i] = NULL;
    }
    return stack;
}

void Stack_P_add(Stack_P stack, Probe probe ) {
    if (stack->top == stack->capacity - 1) {
        Probe * arrayTmp;
        arrayTmp = malloc(sizeof(Probe) * stack->capacity * 2);
        for(int i = 0; i < stack->capacity; i++) {
            arrayTmp[i] = stack->array[i];
        }
        for(int i = stack->capacity; i < stack->capacity * 2; i++) {
            arrayTmp[i] = NULL;
        }
        stack->capacity *= 2;
    }
    stack->array[stack->top] = probe;
    stack->top++;
}

Probe Stack_P_pop(Stack_P stack) {
    stack->top--;
    Probe tmp = stack->array[stack->top];
    stack->array[stack->top] = NULL;
    return tmp;
}

