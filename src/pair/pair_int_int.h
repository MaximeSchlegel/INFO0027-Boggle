#ifndef INFO0027_PROJECT_1_PAIR_INT_INT_H
#define INFO0027_PROJECT_1_PAIR_INT_INT_H

typedef struct Pair_II_ * Pair_II;

struct Pair_II_ {
    int first;
    int second;
};


Pair_II Pair_II_create(int first, int second);
void Pair_II_free(Pair_II pair);

#endif //INFO0027_PROJECT_1_PAIR_INT_INT_H
