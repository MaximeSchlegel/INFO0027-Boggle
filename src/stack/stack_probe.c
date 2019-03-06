#include "stack_probe.h"
#include <stdlib.h>
#include <string.h>

Pair_II Pair_II_create(int first, int second) {
    Pair_II pair = malloc(sizeof(Pair_II *));
    pair->first = first;
    pair->second = second;
    return pair;
}

Pair_II Pair_II_free(Pair_II pair) {
    free(pair);
}

Probe Probe_create(int x, int y, char * prefix, TreeNode node) {
    Probe probe = malloc(sizeof(Probe *));
    probe->currentPosition = Pair_II_create(x, y);
    probe->currentNode = node;
    probe->prefix = malloc(sizeof(char) * 10);
    strcpy(probe->prefix, prefix);
    probe->Path = malloc(sizeof(Probe *) * 10);
}

Stack_P Stack_P_create(int capacity) {
    Stack_P stack = malloc(sizeof(Stack_P *));
    stack->capacity = capacity;
    stack->top = 0;
    stack->array = malloc(sizeof(Probe) * capacity);
    return stack;
}