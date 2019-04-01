#ifndef INFO0027_PROJECT_1_QUEUE_H
#define INFO0027_PROJECT_1_QUEUE_H

typedef struct Stack_P_ * Stack_P;

#include "../probe/probe.h"

struct Stack_P_ {
    int capacity;
    int top;
    Probe * array;

};

Stack_P Stack_P_create();
void Stack_P_add(Stack_P stack, Probe probe);
Probe Stack_P_pop(Stack_P stack);
int Stack_P_isEmpty(Stack_P stack);
void Stack_P_free(Stack_P stack);

#endif //INFO0027_PROJECT_1_QUEUE_H
