#ifndef INFO0027_PROJECT_1_QUEUE_H
#define INFO0027_PROJECT_1_QUEUE_H

typedef struct Pair_II_ * Pair_II;
typedef struct Probe_ * Probe;
typedef struct Stack_P_ * Stack_P;

#include "../tree/tree.h"

struct Pair_II_ {
    int first;
    int second;
};

struct Probe_ {
    Pair_II currentPosition;
    TreeNode currentNode;
    TreeNode * Path;
    char * prefix;
};

struct Stack_P_ {
    int capacity;
    int top;
    Probe * array;

};

Stack_P Stack_P_create(int capacity);
void Stack_P_append(Stack_P stack, Probe probe);
Probe Stack_P_pop(Stack_P stack);
int Stack_P_isEmpty(Stack_P stack);
void Stack_P_free(Stack_P stack);

#endif //INFO0027_PROJECT_1_QUEUE_H
