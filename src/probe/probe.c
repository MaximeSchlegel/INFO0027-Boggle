//#include <stdlib.h>
//#include <string.h>
//#include "probe.h"
//
//Pair_II Pair_II_create(int first, int second) {
//    Pair_II pair = malloc(sizeof(Pair_II *));
//    pair->first = first;
//    pair->second = second;
//    return pair;
//}
//
//Pair_II Pair_II_free(Pair_II pair) {
//    free(pair);
//}
//
//Probe Probe_create(int x, int y, char * prefix, TreeNode node) {
//    Probe probe = malloc(sizeof(Probe *));
//
//    probe->size = 10;
//    probe->len = 1;
//
//    probe->currentPosition = Pair_II_create(x, y);
//
//    probe->currentNode = node;
//
//    probe->prefix = malloc(sizeof(char) * strlen(prefix));
//    strcpy(probe->prefix, prefix);
//
//    probe->path = malloc(sizeof(Pair_II *) * probe->size);
//    probe->path[0] = probe->currentPosition;
//
//    return probe;
//}
//
////Probe Probe_move(Probe oldProbe, int dx, int dy, char * newChar){
////    TreeNode newNode;
////    if ((newNode = HashTable_CN_find(oldProbe->currentNode->children, newChar)) == NOTFOUNDNODE) {
////        return NOTFOUNDPROBE;
////    }
////
////    Probe newProbe = malloc(sizeof(Probe *));
////
////    if (oldProbe->len == oldProbe->size) {
////        newProbe->size = oldProbe->size + 10;
////    } else {
////        newProbe->size = oldProbe->size;
////    }
////    newProbe->len = oldProbe->len + 1;
////
////    int x = oldProbe->currentPosition->first, y = oldProbe->currentPosition->second;
////    newProbe->currentPosition = Pair_II_create(x + dx, y + dy);
////
////    newProbe->currentNode = newNode;
////
////    int len = strlen(oldProbe->prefix);
////    newProbe->prefix = malloc(sizeof(char) * (len + strlen(newChar)));
////    strcpy(newProbe->prefix, oldProbe->prefix);
////    strcat(newProbe->prefix, newChar);
////
////    newProbe->path = malloc(sizeof(Pair_II *) * newProbe->size);
////    for (int i = 0; i < oldProbe->size; i++) {
////        newProbe.size
////    }
////}