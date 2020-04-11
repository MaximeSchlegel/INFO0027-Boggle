#include "stack_pair.h"
#include "../pair/pair_int_int.h"
#include <stdlib.h>
#include <string.h>

Stack_P Stack_P_create(void) {
    Stack_P stack = malloc(sizeof(Stack_P *));
    stack->capacity = 5;
    stack->top = 0;
    stack->array = malloc(sizeof(Pair_II) * 5);
    for(int i = 0; i < 5; i++) {
        stack->array[i] = NULL;
    }
    return stack;
}

void Stack_P_add(Stack_P stack, Pair_II probe ) {
    if (stack->top == stack->capacity - 1) {
        Pair_II *arrayTmp;
        arrayTmp = malloc(sizeof(Pair_II) * stack->capacity * 2);
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

Pair_II Stack_P_pop(Stack_P stack) {
    stack->top--;
    Pair_II tmp = stack->array[stack->top];
    stack->array[stack->top] = NULL;
    return tmp;
}

void Stack_P_free(Stack_P stack) {
    for (int i = 0; i < stack->top; i++) {
        if (stack->array[i]) {
            Pair_II_free(stack->array[i]);
        }
    }
    free(stack);
}

