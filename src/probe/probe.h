#ifndef INFO0027_PROJECT_1_PROBE_H
#define INFO0027_PROJECT_1_PROBE_H


#define NOTFOUNDPROBE NULL
typedef struct Pair_II_ * Pair_II;
typedef struct Probe_ * Probe;

#include "../tree/tree.h"


struct Pair_II_ {
    int first;
    int second;
};

struct Probe_ {
    int size, len;
    Pair_II currentPosition;
    TreeNode currentNode;
    Pair_II *path;
    char *prefix;
};


Probe Probe_create(int width, int height, char * prefix, TreeNode node);
Probe Probe_move(Probe probe, int dwidth, int dheight, char newChar);

#endif //INFO0027_PROJECT_1_PROBE_H
