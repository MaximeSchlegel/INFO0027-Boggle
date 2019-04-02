#ifndef INFO0027_PROJECT_1_QUEUE_H
#define INFO0027_PROJECT_1_QUEUE_H

typedef struct Stack_P_ * Stack_P;

#include "../pair/pair_int_int.h"

struct Stack_P_ {
    int capacity;
    int top;
    Pair_II *array;
};

Stack_P Stack_P_create();
void Stack_P_add(Stack_P stack, Pair_II pair);
Pair_II Stack_P_pop(Stack_P stack);
void Stack_P_free(Stack_P stack);

#endif //INFO0027_PROJECT_1_QUEUE_H
