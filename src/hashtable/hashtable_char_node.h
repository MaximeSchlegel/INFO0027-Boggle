#ifndef INFO0027_PROJECT_1_HASHTABLE_CHAR_NODE_H
#define INFO0027_PROJECT_1_HASHTABLE_CHAR_NODE_H

#define NOTFOUNDNODE NULL
typedef struct Bucket_CN_ * Bucket_CN;
typedef struct HashTable_CN_ * HashTable_CN;

#include "../tree/tree.h"


struct Bucket_CN_ {
    char key;
    TreeNode value;
};

struct HashTable_CN_ {
    int size;
    int isEmpty;
    Bucket_CN * elements;
};


HashTable_CN HashTable_CN_create(int size);
int HashTable_CN_isEmpty(HashTable_CN table);
void HashTable_CN_add(HashTable_CN table, char key, TreeNode value);
int HashTable_CN_exist(HashTable_CN table, char key);
TreeNode HashTable_CN_find(HashTable_CN table, char key);
void HashTable_CN_free(HashTable_CN table);

#endif //INFO0027_PROJECT_1_HASHTABLE_CHAR_NODE_H
