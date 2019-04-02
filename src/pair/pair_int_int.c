#include "pair_int_int.h"
#include <malloc.h>

Pair_II Pair_II_create(int first, int second) {
    Pair_II pair = malloc(sizeof(Pair_II *));
    pair->first = first;
    pair->second = second;
    return pair;
}

void Pair_II_free(Pair_II pair) {
    free(pair);
}