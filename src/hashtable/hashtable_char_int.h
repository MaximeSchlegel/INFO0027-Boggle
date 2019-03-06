#ifndef INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H
#define INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H

#define NOTFOUNDINT -999
typedef struct Bucket_CI_ * Bucket_CI;
typedef struct HashTable_CI_ * HashTable_CI;


struct Bucket_CI_ {
    char key;
    int value;
};

struct HashTable_CI_ {
    int size;
    int isEmpty;
    Bucket_CI * elements;
};


HashTable_CI HashTable_CI_create(int size);
void HashTable_CI_add(HashTable_CI table, char key, int value);
int HashTable_CI_isEmpty(HashTable_CI table);
int HashTable_CI_exist(HashTable_CI table, char key);
int HashTable_CI_find(HashTable_CI table, char key);
void HashTable_CI_free(HashTable_CI table);

#endif //INFO0027_PROJECT_1_HASHTABLE_CHAR_INT_H
